# xv6 – Symbolic Links and Disk Usage  

This project was developed as part of the **Operating Systems 2024** course.  
The goal was to extend the **xv6 operating system** with support for **symbolic links** and a utility for tracking **disk usage**.  

Symbolic links are special files that reference other files through their path.  
The project introduces a new system call `symlink(dest, link)` which creates a symbolic link, along with additional support in the `open()` system call through the `O_NOFOLLOW` flag. To complement this, the `stat` structure was extended with a `blocks` field to record the number of physical blocks used by files.  

Several user programs were implemented to demonstrate and test the new functionality:  
- **sln** – creates symbolic links (similar to `ln -s` in Linux)  
- **symlinkinfo** – displays symbolic link details and their targets  
- **du** – reports disk usage for files and directories, recursively  

A major focus of this project was ensuring that these new features integrate seamlessly into xv6 without breaking existing commands or affecting system stability. Additional considerations such as cycle detection for symbolic links and correct handling of system calls (e.g., `link`, `unlink`) were included to ensure robustness and reliability.  

This assignment provided practical experience with **file system design**, **system calls**, and **low-level OS development**, while reinforcing the importance of stability and backward compatibility when extending an operating system.  
