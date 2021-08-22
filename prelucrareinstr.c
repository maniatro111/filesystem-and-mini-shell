#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prelucrareinstr.h"
#include "file.h"
#include "functii fs.h"

void citireinstr(char **var){
    //se preia sirul de caractere din stdin
    fgets(*var,100,stdin);
    int lmax=strlen(*var);
    //elimin enter-ul de la sfarsitul fiecarei instructiuni pentru o prelucrare mai usoara
    if((*var)[lmax-1]=='\n')(*var)[lmax-1]='\0';
}
void stergereinstr(char **var){
    int i;
    //inlocuiesc fiecare caracter cu \0
    for(i=0;(*var)[i];i++)(*var)[i]='\0';
}
void analizareinstr(char *var,Directory **dircur){
    char *adr;
    //selectez primul cuvant din instructiune
    adr=strtok(var," ");
    //in cazul in care primul cuvant este touch, apeleaza fct touch(in adr ramanand doar numele si continutul fisierului) 
    if(!strcmp(adr,"touch"))
    {
        adr=strtok(NULL," ");
        touch(adr,dircur);
    }
    //in cazul in care primul cuvant este mkdir, apeleaza fct mkdir(in adr ramanand doar numele directorului)
    if(!strcmp(adr,"mkdir"))
    {
        adr=strtok(NULL," ");
        mkdir(adr,dircur);
    }
    //in cazul in care primul cuvant este ls, apeleaza fct ls
    if(!strcmp(adr,"ls"))ls(*dircur);
    //in cazul in care primul cuvant este pwd, apeleaza fct pwd
    if(!strcmp(adr,"pwd"))
    {
        pwd(*dircur);
        printf("\n");
    }
    //in cazul in care primul cuvant este cd, apeleaza fct cd(in adr ramanand doar numele directorului in care trebuie sa ma mut sau .. in cazul in care trebuie sa ma mut inapoi)
    if(!strcmp(adr,"cd"))
    {
        adr=strtok(NULL," ");
        cd(adr,dircur);
    }
    //in cazul in care primul cuvant este tree, apeleaza fct tree
    if(!strcmp(adr,"tree"))tree(*dircur,0);
    //in cazul in care primul cuvant este rm, apeleaza fct rm(in adr ramanand doar numele fisierului care trebuie sters)
    if(!strcmp(adr,"rm"))
    {
        adr=strtok(NULL," ");
        rm(adr,dircur);
    }
    //in cazul in care primul cuvant este rmdir, apeleaza fct rmdir(in adr ramanand doar numele directorului ce trebuie sters)
    if(!strcmp(adr,"rmdir"))
    {
        adr=strtok(NULL," ");
        rmdir(adr,dircur);
    }
    //in cazul in care primul cuvant este find, apeleaza fct find(in adr ramanand doar continutul fisierului/fisierelor)
    if(!strcmp(adr,"find"))
    {
        adr=strtok(NULL," ");
        //salvez adancimea
        int depth=atoi(adr);
        adr=strtok(NULL," ");
        //salvez lungimea minima
        int min=atoi(adr);
        adr=strtok(NULL," ");
        //salvez lungimea maxima
        int max=atoi(adr);
        adr=strtok(NULL," ");
        find(*dircur,depth,min,max,adr);
        printf("\n");
    }
}