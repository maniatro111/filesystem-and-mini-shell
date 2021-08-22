#include "file.h"
void initializarefs(Directory **cap);
void stergerefs(Directory **cap,int *semafor);
void touch(char *numefis,Directory **dircur);
void ls(Directory *dircur);
void mkdir(char *numefis,Directory **dircur);
void pwd(Directory *dircur);
void traversare(Directory *dircur);
void cd(char *nume,Directory **dircur);
void tree(Directory *dircur,int n);
void rm(char *nume,Directory **dircur);
void rmdir(char *nume, Directory **dircur);
void stergere(nod **nodcur);
void find(Directory *dircur,int depth,int min, int max,char *contents);