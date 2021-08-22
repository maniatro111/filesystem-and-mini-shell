#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "prelucrareinstr.h"
#include "functii fs.h"


int main()
{
    //initializare switch ce porneste bucla infinita
    int semafor=1;
    //initializare buffer
    char *buffer=(char *)malloc(100 *sizeof(char));
    //initializare root
    Directory *radacina=NULL;
    while(semafor){
        //citire instructiune
        citireinstr(&buffer);
        //in cazul in care instructiunea este create fs, apeleaza fct initializarefs
        if(!strcmp(buffer,"create fs"))initializarefs(&radacina);
        //in cazul in care instructiunea este delete fs, apeleaza fct stergerefs (modifica si valoarea semaforului pentru a incheia bucla infinita)
        if(!strcmp(buffer,"delete fs"))stergerefs(&radacina,&semafor);
        //pentru orice alt caz, se apeleaza fct analizareinstr 
        analizareinstr(buffer,&radacina);
        //golirea buffer-ului
        stergereinstr(&buffer);
    }
    //dealocare memorie pt buffer
    free(buffer);
    return 0;
}