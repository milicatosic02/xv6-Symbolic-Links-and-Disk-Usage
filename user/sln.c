#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


int
main(int argc, char *argv[])
{
	int i;

	if(argc < 3){
		printf("sln: too few arguments");
		exit();
	}
	symlink(argv[1], argv[2]);
	exit();
}
