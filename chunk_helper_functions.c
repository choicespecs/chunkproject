#include "chunk_include.h"


/*
 * this function will check whether the option argument is a valid option. this will assess whether or not the options are valid numbers
 * and will also assess whether the user has typed in only 0's. if the user has put in some characters other than 0-9 it will return 2.
 * if the user has input all 0's in the required argument then it will return 1. else it will return 0 for successful operation.
 */
int checkOption(char * arg) 
{
    int index;
    int zero_counter = 0;
    for (index = 0; index < strlen(arg); index++) {
        if ((arg[index] < '0') || (arg[index] > '9')) 
            return 2;
        if (arg[index] == '0')
            zero_counter++;
    }

    if (zero_counter == strlen(arg))
        return 1;
    else 
        return 0;
}
/*
 * this function will check suffix and return either 0 or -1 depending on whether both characters within the function are either valid characters
 * or not. This method will check to see if both are either numeric values or alphabetic values
 */

int checkSuffix(char * suffix) {
    int index;
    int characterCheck = 0;
    int numberCheck = 0;
    //loop through the suffix.
    for (index = 0; index < 2; index++) 
    {
        // checks to see if the suffix is a alphabet character if it is then
        // increments the character check by 1.
        if (((int) suffix[index] >= 97) && ((int) suffix[index] < 123))
        {
            characterCheck++;
        }
        // checks to see if the suffix contains the numeric value of 0-9
        // if it does then increments the number check by 1.
        else if (((int) suffix[index] >= 48) && ((int) suffix[index] <= 57))
        {
            numberCheck++;
        }
    }
    // if both character checks have been fulfilled then charactercheck should be 2.
    if (characterCheck == 2) 
    {
        return 0;
    }
    // if both number checks have been fulfilled then numbercheck should be 2.
    else if (numberCheck == 2)
    {
        return 0;
    }
    // the suffix does not pass the check
    else 
    {
        return -1;
    }
}

            

/*
 * Will use the file_descriptor and the stat() function in c to determine the
 * file permissions. Afterwards, the function will read the permissions and output the 
 * appropriate integer value for all the permissions in octal through the use of 
 * strtol() function;
 *
 * will return the user permissions in int (strtol will convert the string to base 8 octal);
 */
static int generatePermissions(int file_descriptor)
{
    int user = 0;
    int group = 0;
    int other = 0;
    char userChar[2];
    char groupChar[2];
    char otherChar[2];
    char perm[5];
    struct stat buf;
    fstat(file_descriptor, &buf);
    
    // Checks OWNER read, write, execute permissions.
    if ( buf.st_mode & S_IRUSR)
    {   
        user = user + 4;
    }

    if (buf.st_mode & S_IWUSR)
    {
        user = user + 2;
    }

    if (buf.st_mode & S_IXUSR)
    {
        user++;
    }

    // Checks GROUP read, write, and execute permissions.
    if (buf.st_mode & S_IRGRP)
    {
        group = group + 4;
    }

    if (buf.st_mode & S_IWGRP)
    {
        group = group + 2;
    }

    if (buf.st_mode & S_IXGRP)
    {
        group++;
    }

    // Checks OTHER read, write, and execute permissions.
    if (buf.st_mode & S_IROTH)
    {
        other = other + 4;
    }
            
    if (buf.st_mode & S_IWOTH)
    {
        other = other + 2;
    }
       
    if (buf.st_mode & S_IXOTH)
    {
        other++;
    }

    // Creates all values into string using sprintf.
    sprintf(perm, "%d", 0);
    sprintf(userChar, "%d", user);
    sprintf(groupChar, "%d", group);
    sprintf(otherChar, "%d", other);

    // Combines the characters together
    strcat(perm, userChar);
    strcat(perm, groupChar);
    strcat(perm, otherChar);

    // Returns the octal value from string.
    return strtol(perm, NULL, 8);
}

/*
 * Will generate the fileName using a char* suffix and prefix. This function will also update
 * the suffix value after each iteration of this function. The ascii value of the suffix characters
 * should increase by one. The return value of this function will be the concat of the prefix and suffix.
 *
 * return will be char * which will combine the prefix and suffix together.
 */
static char* generateFilename(char* prefix, char* suffix)
{
    char *suffixCopy;
    char *fileName;
    int maxCeiling = 0;
    int index;
    fileName = strdup(prefix);
    suffixCopy = strdup(suffix);
    fileName = strcat(fileName, suffixCopy);
    fileName = strcat(fileName, ".txt");
    
    // Loop through the suffix
    for (index = 1; index > -1; index--)
    {
        // if value within suffix is not a digit.
        if (isdigit(suffix[index]) == 0)
        {
            // if suffix[1] is in between 'a' - 'y' = increment to next value 
            if ((index == 1) && (((int) suffix[index]) >= 97) && (((int) suffix[index]) <= 121))
            {
                int a = ++suffix[index];
                char b = a;
                suffixCopy[index] = b;
            } 
            // if suffix[1] is 'z' and suffix[0] is not 'z' then change to 'a' and increment maxCeiling = 1 to change the suffix[0];
            else if ((index == 1) && (suffix[index] == 'z') && (suffix[0] != 'z'))
            {
                ++maxCeiling;
                int a = 97;
                suffix[index] = a;
                char b = a;
                suffixCopy[index] = b;
            }
            // if maxCeiling has already been set from index[1] change the value for suffix[0] to the next value.
            else if ((index == 0) && (maxCeiling == 1))
            {
                int a = ++suffix[index];
                char b = a;
                suffixCopy[index] = b;
            }
            // error catching in case there is a situation that the character is not within the ascii values
            else if ((((int) suffix[index]) < 97) && (((int) suffix[index]) > 122))
            {
                printf("invalid suffix given must be a lowercase char \'a\' - \'z\'\n");
                exit(0);
            }
        }
        // if value is a digit value
        else 
        {
            // if suffix[1] and is 9 and suffix[0] is not '9' change suffix[1] to 0 and increment the maxceiling to increment suffix[0]
            if ((index == 1) && (suffix[index] == '9') && (suffix[0] != '9'))
            {
                ++maxCeiling;
                int a = 48;
                suffix[index] = a;
                char b = a;
                suffixCopy[index] = b;
            }
            // if suffix[1] is inbetween 0 - 8 increment the value by +1.
            else if ((index == 1) && (((int) suffix[1]) >= 48) && (((int) suffix[1]) < 57))
            {
                int a = ++suffix[index];
                char b = a;
                suffixCopy[index] = b;
            }
            // if maxceiling has been incremented then change the suffix[0] to increment by 1. 
            else if ((index == 0) && (maxCeiling == 1))
            {
                int a = ++suffix[index];
                char b = a;
                suffixCopy[index] = b;
            }
        }
    }
    
    return fileName;
}
/*
 * this function will take a fd, prefix, suffix, as well as the chunk size
 * and will split up the files accordingly based on characters. This file should read the input file 
 * character by character and output to a file which is created based upon the suffix and prefix given
 * in the arguments. Upon success, this function should return 0 else will return the appropriate error
 * call
 */
int split_chars(int input_fd, char* prefix, char* suffix, int chunk_size)
{
    int file_perm;
    off_t end;
    int char_count = 0;
    int output_fd;
    int return_num_bytes_read;
    //initialize buffer
    char * buffer = (char *) calloc(1, sizeof(char));
    if (buffer == NULL) 
    {
        return 5;
    }
    
    //create filename
    char * filename;
    filename = generateFilename(prefix, suffix);

    //check if filename already exists.
    if ((access(filename, F_OK)) == 0)
    {
        free(buffer);
        return 17;
    }

    //get file permissions from input_fd
    file_perm = generatePermissions(input_fd);
    umask(0); // reset mask
    output_fd = open(filename, O_WRONLY | O_CREAT, file_perm);
    if (output_fd < 0)
    {
        free(buffer);
        return 2;
    }
    // find the last location for the input_fd.
    end = lseek(input_fd, 0, SEEK_END);
    lseek(input_fd, 0, SEEK_SET);
    
    while ((return_num_bytes_read = read(input_fd, buffer, 1)) > 0)
    {
        write(output_fd, buffer, 1);
        char_count++;
        
        // chunk file by character count & the next character is not past the EOF
        if ((char_count == chunk_size) && ((lseek(input_fd, 1, SEEK_CUR)) != (end + 1)))
        {
            filename = generateFilename(prefix, suffix);
            
            //check if filename already exists if it does then exit.
            if ((access(filename, F_OK)) == 0)
            {
                free(buffer);
                return 17;
            }
            output_fd = open(filename, O_WRONLY | O_CREAT, file_perm);
            char_count = 0;
            lseek(input_fd, -1, SEEK_CUR); //move pointer back 1.
        }
    }
    free(buffer);
    close(input_fd);
    close(output_fd);
    return 0;
}

/*
 * this function will take a fd, prefix, suffix, as well as the chunk size
 * and will split up the files accordingly based on their words. This file should read the input file 
 * character by character but will split files based on word count which will output to a file 
 * which is created based upon the suffix and prefix given in the arguments. 
 * Upon success, this function should return 0 else will return the appropriate error call
 */
int split_words(int input_fd, char* prefix, char* suffix, int chunk_size)
{
    off_t end;
    int file_perm;
    int word_count = 0;
    int output_fd;
    int return_num_bytes_read;
    // create buffer
    char * buffer = (char *) calloc(1, sizeof(char));
    if (buffer == NULL)
    {
        return 5;
    }

    // create filename
    char * filename;
    filename = generateFilename(prefix,suffix);

    //if file from filename already exists error.
    if ((access(filename, F_OK)) == 0)
    {
        free(buffer);
        return 17;
    }

    // gather file permissions.
    file_perm = generatePermissions(input_fd);
    umask(0);
    output_fd = open(filename, O_WRONLY | O_CREAT, file_perm);
    if (output_fd < 0)
    {
        free(buffer);
        return 2;
    }

    //get the end value.
    end = lseek(input_fd, 0, SEEK_END);
    lseek(input_fd, 0, SEEK_SET);

   while ((return_num_bytes_read = read(input_fd, buffer, 1)) > 0)
   {
       // buffer is a 'graphic' character.
       if (isgraph(*buffer))
       {
           //loop through until the last character in buffer is not a 'graphic' character
           do 
           {
               write(output_fd, buffer, 1);
               read( input_fd, buffer, 1);

           } while(isgraph(*buffer));
           word_count++;
        
           // loop through all non graph characters until it the buffer is a 'graphic' character.
           do {
               write(output_fd, buffer, 1);
               return_num_bytes_read = read(input_fd, buffer, 1);
               // if the EOF has been reached then exit the function and while loop.
               if (return_num_bytes_read == 0) 
               {
                 free(buffer);
                 close(input_fd);
                 close(output_fd);
                 return 0;
               }
           } while(!isgraph(*buffer));
           lseek(input_fd, -1, SEEK_CUR); //move the buffer back one.

           // if word count matches the chunk size and the next byte is not past the last character create file.
           if ((word_count == chunk_size) && ((lseek(input_fd, 1, SEEK_CUR)) != (end + 1)))
           {
               filename = generateFilename(prefix,suffix);
               //check if filename already exists if it does then exit.
               if ((access(filename, F_OK)) == 0)
               {
                   free(buffer);
                   return 17;
               }

               output_fd = open(filename, O_WRONLY | O_CREAT, file_perm);
               word_count = 0;
               lseek(input_fd, -1, SEEK_CUR); // move buffer back 1
           }
       }

       // buffer is not a 'graphic' character
       else 
       {
           write(output_fd, buffer, 1);
       }
   }
   free(buffer);
   close(input_fd);
   close(output_fd);
   return 0;
}

/*
 * this function will take a fd, prefix, suffix, as well as the chunk size
 * and will split up the files accordingly based on their lines. This file should read the input file 
 * character by character and output to a file based on line count which is created based upon the suffix and prefix given
 * in the arguments. Upon success, this function should return 0 else will return the appropriate error
 * call
 */
int split_lines(int input_fd, char* prefix, char * suffix, int chunk_size)
{
    off_t end;
    int file_perm;
    int line_count = 0;
    int output_fd;
    int return_num_bytes_read;

    //create buffer
    char * buffer = (char *) calloc(1, sizeof(char));
    if (buffer == NULL)
    {
        return 5;
    }

    //create filename
    char * filename;
    filename = generateFilename(prefix, suffix);
    
    // checks if filename already exists or not.
    if ((access(filename, F_OK)) == 0)
    {
        free(buffer);
        return 17;
    }

    // generate file permissions from input fd.
    file_perm = generatePermissions(input_fd);
    umask(0); //reset umask
    output_fd = open(filename, O_RDWR | O_CREAT, file_perm);
    if (output_fd < 0)
    {
        free(buffer);
        return 2;
    }

    //get the last location within the file 
    end = lseek(input_fd, 0, SEEK_END);
    lseek(input_fd, 0, SEEK_SET);

    while ((return_num_bytes_read = read(input_fd, buffer, 1)) > 0)
    {
        //checks if the buffer is a new line and increments accordingly.
        if (*buffer == '\n')
        {
            line_count++;
        }
        write (output_fd, buffer, 1);

        // if line count matches the chunk size then create a new input file and the next character is not past the end of input_fd
        if ((line_count == chunk_size) && ((lseek(input_fd, 1, SEEK_CUR)) != (end + 1)))
        {
            filename = generateFilename(prefix, suffix);

            //check if filename already exists if it does then exit.
            if ((access(filename, F_OK)) == 0)
            {
                free(buffer);
                return 17;
            }
            output_fd = open(filename, O_RDWR | O_CREAT, file_perm);
            line_count = 0;
            lseek(input_fd, -1, SEEK_CUR);
        }
    }
    free(buffer);
    close(input_fd);
    close(output_fd);
    return 0;
}

