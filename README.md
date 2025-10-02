# xv6 – Symbolic Links and Disk Usage  

This project was created as part of the **Operating Systems 2024** course with the goal of extending the **xv6 operating system** to support **symbolic links** and to implement a **disk usage utility**.  

---

## Implemented Changes  

### 1. Symbolic Links  
Symbolic links are special files that act as references to other files. To implement this functionality in xv6, several modifications were made:  
- **New file type** `T_SYMLINK` was added in `stat.h` to represent symbolic links.  
- **New system call** `symlink(dest, link)` was introduced to create symbolic links pointing to a target file path.  
- The `open()` system call was extended to properly handle symbolic links, following the path to the target file unless the `O_NOFOLLOW` flag is specified.  
- **Cycle detection** was added to prevent infinite loops when symbolic links form recursive references. This was achieved by limiting traversal depth and tracking visited links.  
- Modifications were made so that operations like `link` and `unlink` act on the symbolic link itself rather than on the target file.  

### 2. Disk Usage (`du`) and File System Enhancements  
To track disk space usage, the following updates were made:  
- A new field `blocks` was added to the `stat` structure to store the number of physical blocks allocated to a file. Metadata blocks are excluded from this count.  
- The `ls` program was updated to display the new `blocks` field.  
- A new user program `du` was implemented to recursively calculate and display disk usage for files and directories.  

### 3. User Programs  
Three user-space programs were implemented to demonstrate the new functionality:  
- **sln** – creates symbolic links, similar to the `ln -s` command in Unix/Linux.  
- **symlinkinfo** – displays information about symbolic links and their targets.  
- **du** – calculates and prints disk usage for specified files or directories.  

---

## Focus on System Integrity  
Special care was taken to ensure that these changes do not interfere with the existing functionality of xv6.  
- Executing old commands continues to work without modification.  
- Attempts to modify or write directly into symbolic links are blocked, preserving system stability.  
- Opening files with the `O_NOFOLLOW` flag ensures correct behavior when symbolic links should not be resolved.  

---

## Learning Outcomes  
Through this project, the following areas were explored and practiced:  
- Extending a file system with new data types (symbolic links).  
- Adding and modifying **system calls** in xv6.  
- Handling **edge cases** such as symbolic link cycles.  
- Measuring and reporting **disk usage** at the OS level.  
- Integrating new functionality in a way that preserves backward compatibility and performance.  

This assignment provided practical experience in **file system design, kernel development, and low-level systems programming** while demonstrating how symbolic links and disk usage utilities are implemented in real-world operating systems.  
