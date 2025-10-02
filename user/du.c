#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}

int total = 0;
void
ls(char *path)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, O_NOFOLLOW)) < 0){
		fprintf(2, "ls: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "ls: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch(st.type){
	case T_FILE:
		printf("%s %d\n", fmtname(path), st.blocks);
		//total += st.blocks;
		break;
	case T_DIR:
		printf("%s %d\n", fmtname(path), st.blocks);
		total += st.blocks;
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf("ls: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);
		*p++ = '/';
		int dirCounter = 0;
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			dirCounter++;
			if (dirCounter < 2)
				continue;

			if(de.inum == 0)
				continue;
			memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			if(stat(buf, &st) < 0){
				printf("ls: cannot stat %s\n", buf);
				continue;
			}
			if (st.type == T_SYMLINK || st.type == T_FILE) {
				printf("%s %d\n", fmtname(buf), st.blocks);
				total += st.blocks;
			} else if (st.type == T_DIR && dirCounter > 2) {
				ls(buf);
			}
		}
		break;
	case T_SYMLINK:
		printf("%s %d\n", fmtname(path), st.blocks);
		//total += st.blocks;
		break;

	}
	close(fd);
}

int
main(int argc, char *argv[])
{
	int i;

	if(argc < 2){
		ls(".");
		printf("%s %d\n", fmtname("total"), total);
		exit();
	}
	for(i=1; i<argc; i++)
		ls(argv[i]);
	if (total != 0)
		printf("%s %d\n", fmtname("total"), total);
	exit();
}
