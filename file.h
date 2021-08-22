#ifndef __FILE_H__
#define __FILE_H__

typedef struct nod {
    
    void *data;
    
    struct nod *urm;
    struct nod *prev;
} nod;

typedef struct Directory {
    // The name of the directory
    char *name;

    nod *headfile; // The list of files of the current directory

    nod *headirectory; // The list of directories of the current directory

    // The parent directory of the current directory (NULL for the root directory)
    struct Directory *parentDir;
} Directory;

// DO NOT MODIFY THIS STRUCTURE
typedef struct File {
    // The name of the file
    char *name;

    // The size of the file
    int size;

    // The content of the file
    char *data;

    // The directory in which the file is located
    Directory *dir;
} File;

#endif /* __FILE_H__ */
