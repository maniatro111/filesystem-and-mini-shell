#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "prelucrareinstr.h"
#include "functii fs.h"

void initializarefs(Directory **cap)
{
    //alocare de memorie pentru structura radacina si initializare variabile 
    Directory *radacina=malloc(sizeof(Directory));
    radacina->name=(char *)malloc(5*sizeof(char));
    strcpy(radacina->name,"/");
    radacina->parentDir=NULL;
    radacina->headfile=NULL;
    radacina->headirectory=NULL;
    *cap=radacina;
}
void stergerefs(Directory **cap,int *semafor){
    //dealocare memorie radacina si modificarea semaforului ce va duce la inchiderea buclei din main
    free((*cap)->name);
    free(*cap);
    *semafor=0;
}
void touch(char *numefis,Directory **dircur){
    //semafor in cazul in care exista deja un fisier cu numele respectiv
    int rez=1;
    //alocare memorie si initializare pt nod
    nod *elem=(nod *)malloc(sizeof(nod));
    elem->urm=NULL;
    elem->prev=NULL;
    //alocare memorie si initializare pt variabila de tip File
    File *aux=(File *)malloc(sizeof(File));
    aux->data=NULL;
    aux->size=0;
    //alocare memorie pentru numele fisierului
    aux->name=(char *)malloc((strlen(numefis)+10)*sizeof(char));
    strcpy(aux->name,numefis);
    aux->dir=*dircur;
    //"tai" numele fisierului din buffer si ajung la continutul fisierului
    numefis=strtok(NULL," ");
    //alocare memorie pentru continutul fisierului
    aux->data=(char *)malloc((strlen(numefis)+10)*sizeof(char));
    //salvare dimensiune 
    aux->size=strlen(numefis);
    strcpy(aux->data,numefis);
    //atribui campului data valorile din aux
    elem->data=aux;
    //creez un aux pentru a parcurge lista
    nod *aux2= (*dircur)->headfile;
    //in cazul in care lista este goala, capul devine elementul curent
    if(!(*dircur)->headfile)
    {
        (*dircur)->headfile=elem;
        //nu mai trebuie sa eliberez memoria deoarece nu exista un fisier cu respectivul nume
        rez=0;
    }
        //cazul in care elementul curent trebuie plasat inaintea capului listei  
    else if(strcmp(((File *)(aux2->data))->name,aux->name)>0)
    {
        rez=0;
        elem->urm=(*dircur)->headfile;
        elem->urm->prev=elem;
        (*dircur)->headfile=elem;
    }
    else
    {
        //parcurgem lista pana urmatorul element este NULL sau pana numele 
        //urmatorului fisier este "mai mare" decat al fisierului pe care trbuie sa il adaug 
        while(aux2->urm&&strcmp(((File*)(aux2->urm->data))->name,aux->name)<=0)aux2=aux2->urm;
        if(strcmp(((File*)(aux2->data))->name,aux->name))
        {
            rez=0;
            elem->urm=aux2->urm;
            //in cazul in care nodul nu este inserat la sfarsitul listei
            if(aux2->urm)elem->urm->prev=elem;
            aux2->urm=elem;
            elem->prev=aux2;
        }   
    }
    //eliberez tot ce am alocat, in cazul in care mai am deja un fisier cu acest nume
    if(rez)
    {
        free(aux->data);
        free(aux->name);
        free(aux);
        free(elem);
    }
}
void ls(Directory *dircur){
    //auxiliar pentru parcurgerea listei de fisiere
    nod *aux=dircur->headfile;
    //se parcuge mai intai lista de fisiere si se afiseaza numele fisierelor
    while(aux){
        if(aux->urm)printf("%s ",((File *)(aux->data))->name);
        else printf("%s",((File *)(aux->data))->name);
        aux=aux->urm;
    }
    //printarea unui spatiu delimitator intre lista de fisiere si cea de directoare
    if(aux!=dircur->headfile)printf(" ");
    //parcurgerea listei de directoare si afisarea numelor acestora
    aux=(*dircur).headirectory;
    while(aux)
    {
        if(aux->urm)printf("%s ",((Directory *)(aux->data))->name);
        else printf("%s",((Directory *)(aux->data))->name);
        aux=aux->urm;
    }
    printf("\n");
}
void mkdir(char *numefis,Directory **dircur){
    //semafor in cazul in care exista deja un director cu numele respectiv
    int rez=1;
    //alocare memorie si initializare pt nod
    nod *elem=(nod *)malloc(sizeof(nod));
    elem->urm=NULL;
    elem->prev=NULL;
    //alocare memorie si initializare pt variabila de tip Directory
    Directory *aux=(Directory *)malloc(sizeof(Directory));
    aux->headfile=NULL;
    aux->headirectory=NULL;
    aux->parentDir=*dircur;
    //alocare memorie pentru numele directorului
    aux->name=(char *)malloc((strlen(numefis)+2)*sizeof(char));
    strcpy(aux->name,numefis);
    elem->data=aux;
    //creez un aux pentru a parcurge lista de directoare
    nod *aux2= (*dircur)->headirectory;
    //in cazul in care lista este goala, capul devine elementul curent
    if(!(*dircur)->headirectory)
    {
        (*dircur)->headirectory=elem;
        //nu mai trebuie sa eliberez memoria deoarece nu exista un director cu respectivul nume
        rez=0;
    }
    //cazul in care elementul curent trebuie plasat inaintea capului listei
    else if(strcmp(((Directory *)(aux2->data))->name,aux->name)>0)
    {
        rez=0;
        elem->urm=(*dircur)->headirectory;
        elem->urm->prev=elem;
        (*dircur)->headirectory=elem;
    }
    else
    {
        //parcurgem lista pana urmatorul element este NULL sau pana numele 
        //urmatorului director este "mai mare" decat al directorului pe care trbuie sa il adaug
        while(aux2->urm&&strcmp(((Directory *)(aux2->urm->data))->name,aux->name)<=0)aux2=aux2->urm;
        if(strcmp(((Directory *)(aux2->data))->name,aux->name))
        {
            rez=0;
            elem->urm=aux2->urm;
            //in cazul in care nodul nu este inserat la sfarsitul listei
            if(aux2->urm)elem->urm->prev=elem;
            aux2->urm=elem;
            elem->prev=aux2;
        }
    }
    //eliberez tot ce am alocat, in cazul in care mai am deja un director cu acest nume
    if(rez){
        free(aux->name);
        free(aux);
        free(elem);
    }
}

void pwd(Directory *dircur){
    //daca parintele curent este root, scrie /
    if(!strcmp(dircur->name,"/"))printf("/");
    else traversare(dircur);
}
void traversare(Directory *dircur){
    //daca directorul parinte al folder-ului curent este root-ul, se afiseaza /numele directorului
    if(!strcmp(dircur->parentDir->name,"/"))printf("/%s",dircur->name);
    else{
        traversare(dircur->parentDir);
        printf("/%s",dircur->name);
    }
}
void cd(char *nume,Directory **dircur){
    //variabila ce semnaleaza daca directorul cu respectivul nume exista
    int gasit=0;
    //daca 'numele' directorului este .. muta-ma in directorul parinte
    if(!strcmp(nume,".."))(*dircur)=(*dircur)->parentDir;
    else{
        //aux pentru parcurgerea listei de directoare
        nod *aux=(*dircur)->headirectory;
        if(aux){
        while(aux->urm&&strcmp(nume,((Directory *)(aux->data))->name))aux=aux->urm;
        //daca numele directorului curent coincide cu numele directorului in care trebuie sa ma mut 
        if(!strcmp(nume,((Directory *)(aux->data))->name)){
            (*dircur)=((Directory *)(aux->data));
            gasit=1;
            }
        else gasit=0;
        }
        if(!gasit)printf("Cannot move to '%s': No such directory!\n",nume);
    }
}

void tree(Directory *dircur,int n){
    int i;
    //printeaza numarul de spatii in functie de nivelul pe care ma aflu
    for(i=0;i<n;i++)printf(" ");
    printf("%s\n",dircur->name);
    n=n+4;
    nod *aux=dircur->headfile;
    //parcurg si afisez lista de fisiere
    while(aux){
        for(i=1;i<=n;i++)printf(" ");
        printf("%s\n",((File *)(aux->data))->name);
        aux=aux->urm;
        }
    //parcurg lista de directoare si apelez functia tree pentru fiecare director
    aux=dircur->headirectory;
    while(aux){
        tree((Directory *)(aux->data),n);
        aux=aux->urm;}
}
void rm(char *nume,Directory **dircur){
    //variabila decizionala care semnaleaza daca exista fisierul cu acel nume
    int gasit=0;
    nod *aux=(*dircur)->headfile;
    //parcurgere lista fisiere
    while(aux){
        //daca numele fisierului curent coincide cu numele fisieului ce trebuie sters
        if(!strcmp(((File *)(aux->data))->name,nume))
        {
            gasit=1;
            //daca fisierul ce trebuie sters este capul listei
            if(!strcmp(((File *)(aux->data))->name,((File *)((*dircur)->headfile->data))->name))
                (*dircur)->headfile=(*dircur)->headfile->urm;
            //daca fisierul ce trebuie sters nu este ultimul nod
            if(aux->urm)
                aux->urm->prev=aux->prev;
            //daca fisierul ce trebuie sters nu este primul nod
            if(aux->prev)
                aux->prev->urm=aux->urm;
            //eliberarea tuturor alocarilor
            free(((File *)(aux->data))->data);
            free(((File *)(aux->data))->name);
            free(((File *)(aux->data)));
            free(aux);
            //iesire imediata din bucla pentru a evita o accesare incorecta a memoriei
            break;
        } 
        aux=aux->urm; 
    }
    if(!gasit)printf("Cannot remove '%s': No such file!\n",nume);
}
void rmdir(char *nume, Directory **dircur)
{
    //variabila decizionala care semnaleaza daca exista directorul cu acel nume
    int gasit=0;
    nod *aux=(*dircur)->headirectory;
    //parcurg lista de directoare
    while(aux){
        //daca numele directorului curent coincide cu numele directorului ce trebuie sters
        if(!strcmp(((Directory *)(aux->data))->name,nume))
        {
            gasit=1;
            //daca directorul ce trebuie sters este capul listei
            if(!strcmp(((Directory *)(aux->data))->name,((Directory *)((*dircur)->headirectory->data))->name))
                (*dircur)->headirectory=(*dircur)->headirectory->urm;
            //daca directorul ce trebuie sters nu este ultimul nod
            if(aux->urm)
                aux->urm->prev=aux->prev;
            //daca directorul ce trebuie sters nu este ultimul nod
            if(aux->prev)
                aux->prev->urm=aux->urm;
            //stergerea recursiva
            stergere(&aux);
            break;
        }
        aux=aux->urm;
    }
    if(!gasit)printf("Cannot remove '%s': No such directory!\n",nume);
}
//stergerea recursiva a fisierelor si directoarelor incepand de la nodul initial
void stergere(nod **nodcur)
{   
    Directory *var= (*nodcur)->data;
    //daca listele de fisiere si subdirectoare ale directorului din nodul 
    //curent este vida, eliberarea se face direct
    if(!var->headirectory&&!var->headfile)
    {
        free(var->name);
        free((*nodcur)->data);
        free((*nodcur));
    }
    else
    {
        //cat timp mai exista fisiere de sters,se sterg, de la cap la coada
        while(var->headfile)
        {
            nod *aux=var->headfile;
            var->headfile=var->headfile->urm;
            free(((File *)(aux->data))->data);
            free(((File *)(aux->data))->name);
            free(((File *)(aux->data)));
            free(aux);
        }
        //cat timp mai exista directoare de sters,se sterg, de la cap la coada apeland fct stergere
        while(var->headirectory)
        {
            nod *aux=var->headirectory;
            var->headirectory=var->headirectory->urm;
            stergere(&aux);
        }
        //se elibereaza directorul din care am plecat
        free(var->name);
        free((*nodcur)->data);
        free((*nodcur));
    }
    
}
void find(Directory *dircur,int depth,int min, int max,char *contents){
    //in cazul in care mai pot parcurge structura in adancime
    if(depth>-1)
    {
        //parcurg lista de fisiere a directorului in care ma aflu
        nod *aux=dircur->headfile;
        while(aux)
        {
            //salvez lungimea cuvintelor/cuvantului din interiorul fisierului
            int lung=strlen(((File *)(aux->data))->data);
            //in cazul in care se gaseste subsirul cautat in fisier 
            //si lungimea cuvantului/cuvintelor se afla in interval
            if(strstr(((File *)(aux->data))->data,contents)&&lung>=min&&lung<=max)printf("%s ",((File *)(aux->data))->name);
            aux=aux->urm;
        }
        //daca exista foldere in care putem intra
        if(dircur->headirectory)
        {
            //parcurg lista de directoare
            aux=dircur->headirectory;
            while(aux)
            {
                //aplic functia find cu depth-1 pentru a 
                //marca ca am coborat un nivel in structura
                find(((Directory *)(aux->data)),depth-1,min,max,contents);
                aux=aux->urm;
            }
        }
        
    }
}