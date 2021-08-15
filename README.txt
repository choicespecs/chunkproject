
Project 2: Chunk

Created by:
Christopher Lee

1. Introduction
-------------------
This is a file which will "chunk" or separate files depending on the arguments given within the
command line. The file currently has functionality to separate files based on character, line, or
word count. There is also functionality to determine prefix and suffix for files. There are default
values given if options are not given. If no option is specified, the default value is set to 
chunk by 1000 lines. The default prefix is set to x and the default suffix is set to the character "aa"

2. Installation.
--------------------
This file will require the following files for installation.

    a) chunk.c
    b) chunk_helper_functions.c
    c) chunk_helper_functions.h
    d) chunk_include.h

A makefile has been provided to assist with the installation of the chunk file (as well as
included the functionality to remove all relevant files). The chunk.c file contains mainly
error checking for the functions utilized within chunk_helper_function file.

If any problems occur with the makefile compilation, you should be able to create an executable
using the following command with gcc:
    "gcc chunk.c chunk_helper_functions.c -o chunk"


3. Files / Methods
--------------------
The chunk file is separated only into two main files.

    a) chunk.c
    b) chunk_helper_functions.c

a) chunk.c
    this file is the driver for the file, and doesn't contain any methods itself. It will
    perform error checking throughout the reading and writing of the files that are read or written within chunk.

b) chunk_helper_functions.c
    
   i) static int generatePermissions(int file_descriptor)
   
   this is a helper function which is utilized within the all of the split functions. This function will gather
   the file permissions of the input file descriptor using the stat() function and using the information from the struct stat buf, st_mode.
   Using this function and gathering information from the struct stat buf. we can acquire the appropriate information about the exact permissions.
   the return value is the user permissions in int for the input file descriptor.

   ii) static char * generateFilename(char * prefix, char * suffix)
   
   this is another helper function to create a filename by combining the prefix and suffix given within the argument. This function however, will also increment the suffix values by 1 through each
   iteration. Therefore if the values are alphabetic as "aa" it will increase the values by one letter value to "zz". If the values are numeric. It will increase the values of each integer by 1 so 
   01 will be 02 to 03 and etc. the return value will be the combined char * of the prefix and suffix.

   iii) int split_chars(int input_fd, char* prefix, char* suffix, int chunk_size)
   
   this function will utilize the input_fd, prefix, and suffix, as well as the chunk_size to split the file appropriately. This function utilizes both the generatePermissions to gather the right file
   permissions and the generatefileName to create the filenames. Each character is incremented by 1 until the chunk_size and then the file is split until the end of the file or until there is no other
   characters to be read within the file.

    iv) int split_words(int input_fd, char* prefix, char * suffix, int chunk_size);

   this function will utilize the input_fd, prefix, and suffix, as well as the chunk_size to split the file appropriately. This function utilizes both the generatePermissions to gather the right file
   permissions and the generatefileName to create the filenames. Each character is incremented by 1 and the function will determine what can be considered words using the isgraph() function. These
   words are counted until the chunk_size and then the file is split until the end of the file or until there are no other characters that can be read.

    v) int split_lines(int input_fd, char * prefix, char * suffix, int chunk_size);

   this function will utilize the input_fd, prefix, and suffix, as well as the chunk_size to split the file appropriately. This function utilizes both the generatePermissions to gather the right file
   permissions and the generatefileName to create the filenames. Each character is incremented by 1 until a '\n' character has been found. Then the line count will be incremented. When the line count
   matches the chunk_size then the file is split until the end of the file or until there is no other characters to be read within the file.

   vi) int checkSuffix(char * suffix)

   this function will just be an error checker for the suffix which checks if the suffix is both numeric values (0-9) or both should be alphabet values ('a' - 'z'). if BOTH suffix values fulfills this
   condition then the function will return a 0 for success. If there is any other case or situation which this may not be valid then the return value will be -1 to indicate an error has occured.

    vii) int checkOption(char * arg) 

    this function will check whether the option argument is a vlaid option. This will assess whether the input are integers and will also assess whether the numbers inside are all 0's. This function will also assess whether the character count is 2 for the option is the character is not a integer value it will return 2. If the character length of the option is not 2 it will return 1 else it will return 0 on success.

4. References
----------------

comparing strings for cmd line arguments

//www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
https://www.programiz.com/c-programming/library-function/string.h/strcmp

Stat and File Permissions:

//man7.org/linux/man-pages/man2/lstat.2.html
https://linux.die.net/man/2/stat
//c-for-dummies.com/blog/?p=4101
https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html

converting string to long integer (converting string to base 8)

https://www.techonthenet.com/c_language/standard_library_functions/stdlib_h/strtol.php
https://pubs.opengroup.org/onlinepubs/009604599/functions/strtol.html

combining char* in c

https://linux.die.net/man/3/strcat
https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm
https://pubs.opengroup.org/onlinepubs/009695399/functions/strcat.html

bit flags and bitmasks

https://blog.podkalicki.com/bit-level-operations-bit-flags-and-bit-masks/
https://www.youtube.com/watch?v=6hnLMnid1M0

Access and checking if file exists

//linux.die.net/man/2/access
https://www.geeksforgeeks.org/access-command-in-linux-with-examples/

errno number and values

https://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Errors/unix_system_errors.html
https://man7.org/linux/man-pages/man3/errno.3.html

ascii table and values

https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html

Checking if STDIN is empty or not

https://fishshell.com/docs/current/cmds/isatty.html
//linux.die.net/man/3/isatty
https://rosettacode.org/wiki/Check_input_device_is_a_terminal


