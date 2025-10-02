# xv6 Symbolic Links and Disk Usage  

This project extends the **xv6 operating system** by adding support for **symbolic links** and a **disk usage utility**.  
Implemented functionality includes:  

- `symlink(dest, link)` system call for creating symbolic links  
- User programs:  
  - `sln` – create symbolic links (similar to `ln -s`)  
  - `symlinkinfo` – display information about symbolic links  
  - `du` – report disk usage for files and directories  
- Support for the `O_NOFOLLOW` flag in `open()`  
- Extension of the `stat` structure with a `blocks` field to track physical disk usage  

The new features were designed to integrate seamlessly with xv6 without breaking existing functionality or performance.  
