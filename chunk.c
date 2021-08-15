#include "chunk_helper_functions.h"
#include "chunk_include.h"

/* Flags which will be defined and used throughout the program */
#define CHAR_SET 0x1
#define WORD_SET 0x2
#define LINE_SET 0x4
#define SUFFIX_SET 0x10
#define PREFIX_SET 0x20
#define SET_FILE 0x40
#define OPTION_DEBUG 0x80 // This flag will make sure ONLY one option is set (if the option is set then OPTION_DEBUG will be set)

int main (int argc, char * argv[]) 
{
    int error_check; // used to check functions for possible errors
    char flags = 0; // FLAGS for setting options
    int input_fd; 
    char *suffix;
    char *prefix;
    int size; 

    if (argc > 9) 
    {
        errno = EINVAL;
        perror("too many arguments");
        return 22;
    }
    
    // check to see if there is a valid number of arguments (each option if called must be set with a required option if not then issue an error.
    error_check = argc - 1;
    if (error_check % 2 != 0) 
    {
        errno = EINVAL;
        perror("invalid number of arguments: ");
        return 22;
    }
    
    /* Reads arguments and options & sets flags */
    if (argc > 2) 
    {
        int index;
        for (index = 1; index < argc; index++) 
        {
            if (strcmp(argv[index], "-f") == 0)
            { 
                input_fd = open(argv[index + 1], O_RDONLY);
                if (input_fd < 0) 
                {
                    perror("open");
                    return 2;
                }
                flags = flags | SET_FILE;
                index++;
            }
            else if (strcmp(argv[index], "-l") == 0)
            {
                // error checking so multiple options cannot be inputted
                // if option has not been set yet, set flag.
                if ((flags & OPTION_DEBUG) == 0) 
                {
                    flags = flags | OPTION_DEBUG;
                }
                // flag has already been set, so return error.
                else 
                {
                    errno = EINVAL;
                    perror("Too many options: ");
                    return 22;
                }
                error_check = checkOption(argv[index + 1]);
                // option is not a valid integer argument
                if (error_check == 2) 
                {
                    errno = EINVAL;
                    perror("option argument must be valid integer value");
                    return 22;
                }
                // option has been all 0's.
                if (error_check == 1)
                {
                    errno = EINVAL;
                    perror("option argument cannot be 0.");
                    return 22;
                }
                size = atoi(argv[index + 1]);
                flags = flags | LINE_SET;
                index++;
            } 
            else if (strcmp(argv[index], "-w") == 0)
            {
                // error checking for multiple options cannot be inputted.
                // if option has not been set, set flag.
                if ((flags & OPTION_DEBUG) == 0)
                {
                    flags = flags | OPTION_DEBUG;
                }
                // flag has already been set, so return error.
                else
                {
                    errno = EINVAL;
                    perror("Too many options: ");
                    return 22;
                }
                
                error_check = checkOption(argv[index + 1]);
                //option is not a valid integer argument,
                if (error_check == 2) 
                {
                    errno = EINVAL;
                    perror("option argument must be valid integer value");
                    return 22;
                }
                //option has been all 0's
                if (error_check == 1)
                {
                    errno = EINVAL;
                    perror("option argument cannot be 0.");
                    return 22;
                }
                size = atoi(argv[index + 1]);
                flags = flags | WORD_SET;
                index++;
            }
            else if (strcmp(argv[index], "-c") == 0)
            {   
                // error checking for multiple options so they cannot be inputted.
                // if option has not been set, set flag
                if ((flags & OPTION_DEBUG) == 0)
                {
                    flags = flags | OPTION_DEBUG;
                }
                // flag has already been set, so return error.
                else
                {
                    errno = EINVAL;
                    perror("Too many options: ");
                    return 22;
                }
                
                error_check = checkOption(argv[index + 1]);
                // option is not a valid integer argument.
                if (error_check == 2) 
                {
                    errno = EINVAL;
                    perror("option argument must be valid integer value");
                    return 22;
                }
                // option has been all 0's.
                if (error_check == 1)
                {
                    errno = EINVAL;
                    perror("option argument cannot be 0.");
                    return 22;
                }
                size = atoi(argv[index + 1]);
                flags = flags | CHAR_SET;
                index++;
            }
            else if (strcmp(argv[index], "-s") == 0)
            {
                suffix = argv[index + 1];
                // check to make sure suffix is only 2 characters.
                if (strlen(suffix) != 2)
                {
                    errno = EINVAL;
                    perror("suffix can only be 2 characters or 2 integers");
                    return 22;
                } 
                
                //check to see if both suffix values are either both characters or both numeric values
                if (checkSuffix(suffix) < 0)
                {
                    errno = EINVAL;
                    perror("suffix must either both be numeric values or both be alphabet characters");
                    return 22;
                }
                
                flags = flags | SUFFIX_SET;
                index++;
            }
            else if (strcmp(argv[index], "-p") == 0)
            {
                prefix = argv[index + 1];
                flags = flags | PREFIX_SET;
                index++;
            }
            // any other option written (which is not permitted)
            else 
            {
                errno = EINVAL;
                perror("Improper argument for chunk: ");
                //print message for user to help understand how to put proper argument.
                printf("Valid options for chunk\n");
                printf("[options] -f \'file\' [prefix] [suffix]\n");
                printf("[options] [prefix] [suffix] < \'file\'\n");
                return 22;
            }
        }
    }

    //if option is not set change flag to LINE_SET & size to 1000
    if ((flags & OPTION_DEBUG) == 0)
    {
        flags = flags | LINE_SET;
        size = 1000;
    }

    //if suffix is not set then set default suffix of "aa"
    if ((flags & SUFFIX_SET) == 0)
    {
        char defaultsuffix[4] = {'a','a','\0'}; //DEFAULT for suffix.
        suffix = defaultsuffix;
    }

    // if prefix is not set then set prefix to "x"
    if ((flags & PREFIX_SET) == 0)
    {
        char defaultprefix[2] = {'x','\0'}; //DEFAULT for prefix
        prefix = defaultprefix;
    }

    //if file has not been set then set to stdin
    if ((flags & SET_FILE) == 0)
    {
        input_fd = STDIN_FILENO; // DEFAULT for input
        // check if STDIN is terminal or not (whether it is empty or contains file)
        if (isatty(input_fd))
        {
            errno = ENOENT;
            perror("No input file read: ");
            return 2;
        }
    }
   
    // Flags will determine which count to use (word, character, or line).
    // Will write only characters 
    if (flags & CHAR_SET)
    {
        error_check = split_chars(input_fd, prefix, suffix, size);
        if (error_check == 5) 
        {
            errno = EIO;
            perror("Buffer interrupt: ");
            return 5;
        }
        if (error_check == 17)
        {
            errno = EEXIST;
            perror("Chunk file already exists: ");
            return 17;
        }
        if (error_check == 2)
        {
            errno = ENOENT;
            perror("File does not exist: ");
            return 2;
        }
    }

    //Will write only words
    else if (flags & WORD_SET)
    {
        error_check = split_words(input_fd, prefix, suffix, size);
        if (error_check == 5) 
        {
            errno = EIO;
            perror("Buffer interrupt: ");
            return 5;
        }
        if (error_check == 17)
        {
            errno = EEXIST;
            perror("Chunk file already exists: ");
            return 17;
        }
        if (error_check == 2)
        {
            errno = ENOENT;
            perror("File does not exist: ");
            return 2;
        }
    }
   
    // will write only lines.
    else if ((flags & LINE_SET))
    {
        error_check = split_lines(input_fd, prefix, suffix, size);
        if (error_check == 5) 
        {
            errno = EIO;
            perror("Buffer interrupt: ");
            return 5;
        }
        if (error_check == 17)
        {
            errno = EEXIST;
            perror("Chunk file already exists: ");
            return 17;
        }
        if (error_check == 2)
        {
            errno = ENOENT;
            perror("File does not exist: ");
            return 2;
        }
    } 
    // Extra condition in case of any potential errors set with flags within program.
    else 
    {
        errno = ENOEXEC;
        perror("Invalid option call");
        return 8;
    }

    return 0;
       
}
