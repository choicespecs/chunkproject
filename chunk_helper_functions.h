#ifndef CHUNK_HELPER_FUNCTIONS
#define CHUNK_HELPER_FUNCTIONS

extern int checkOption(char * arg);
extern int checkSuffix(char * suffix);
extern int split_chars(int input_fd, char * prefix, char * suffix, int chunk_size);
extern int split_words(int input_fd, char * prefix, char * suffix, int chunk_size);
extern int split_lines(int input_fd, char * prefix, char * suffix, int chunk_size);

#endif
