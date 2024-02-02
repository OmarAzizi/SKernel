#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define     BASE_BLOCK_ADDRESS          100 // address of base block in disk
#define     FILENAME_LENGTH             256 // max length allowed for a filename
#define     ERROR_CODE_NO_FILES_EXIST   -1
#define     EXIT_CODE_FILE_NOT_EXIST    0

/*
    The base block will contain a head and a tail.
    The head points at the first file created.
    The tail points at the last file created.
*/
typedef struct {
    int head, tail;
} base_block_t;

/*
    the files will be implemented similar to a singly linked list, 
    where a file points to the next created file
*/
typedef struct {
    char filename[FILENAME_LENGTH];
    int next_file_address; // address of the next file 
} metadata_t;

base_block_t* base_block; // contains the memory address of the base 
                          // block after loading it from the disk

void filesystem_init(); // will be called by the main kernel on startup
void create_file(char*, char*);
char** list_files();
char* read_file(char*);

// Auxiliary Functions
metadata_t* load_metadata(int); // used to load the metadata for a file 
                                // by passing its disk address (aka. base_block->tail)
int get_address_by_filename(char*);
int get_prev_file_address(int);
int get_files_number();

#endif
