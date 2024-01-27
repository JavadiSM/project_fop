#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
void SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
// Define the color codes
#define BLACK 0
#define RED 4
#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define MAGENTA 5
#define CYAN 3
#define WHITE 7
int compareFiles(FILE* file1, FILE* file2) {
    int ch1, ch2;
     
    // Check if both files exist
    if (file1 == NULL || file2 == NULL)
        return -1;
  
    // Read and compare each character one by one
    while (((ch1 = fgetc(file1)) != EOF) && ((ch2 = fgetc(file2)) != EOF)) {
        if (ch1 != ch2)
            return 0;  // Files are different
    }
  
    // Check if the end of both files is reached
    if (ch1 == EOF && ch2 == EOF)
        return 1;  // Files are same
  
    return 0;  // Files are different
}
int searchWordInFile(const char* filename, const char* word) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, word) != NULL) {
            fclose(file);
            return 1; // Word found
        }
    }

    fclose(file);
    return 0; // Word not found
}
int countLinesInFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return -1;
    }
    int count = 0;
    int ch = 0;
    while (1) {
        ch = fgetc(file);
        if (ch == EOF) {
            break; 
        }
        if (ch == '\n') {
            count++; 
        }
    }
    fclose(file);
    return count;
}
void revert(char *in){
    int n=strlen(in);
    char temp;
    if(n%2!=0){
        for(int i=0;i<=n/2;i++){
            temp=in[i];
            in[i]=in[n-1-i];
            in[n-1-i]=temp;
        }
    }
    else {
        for(int i=0;i<n/2;i++){
            temp=in[i];
            in[i]=in[n-1-i];
            in[n-1-i]=temp;
        }
    }
}
void config_name(int argc,char *argv[]){
    FILE *fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\global_name.txt", "w");
    fprintf(fp,"%s",argv[4]);
    fclose(fp);
}
void config_email(int argc,char *argv[]){
    FILE *fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\global_email.txt", "w");
    fprintf(fp,"%s",argv[4]);
    fclose(fp);
}
void config_local_name(int argc,char *argv[]){
    FILE *fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\name.txt", "w");
    fprintf(fp,"%s",argv[3]);
    fclose(fp);
}
void config_local_email(int argc,char *argv[]){
    FILE *fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\email.txt", "w");
    fprintf(fp,"%s",argv[3]);
    fclose(fp);
}
int finder(char *starting,char *ending){
    DIR *dir;
    FILE *g=fopen("\\JAVAD\\wildcard.txt","w");
    dir = opendir(".");
    struct dirent *ent;
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, starting) != NULL && strstr(ent->d_name, ending) != NULL) {
                fprintf(g,"%s\n", ent->d_name);
            }
        }
        closedir(dir);
        fclose(g);
        return 0;
    } else {
        perror("Unable to open directory.");
        fclose(g);
        return 1;
    }
}
void add_file(int argc, char *argv[],int i) {
    if(searchWordInFile("JAVAD\\added.txt",argv[i])){
        return;
    }
    system("dir /B > \"JAVAD\\current.txt\"");
    if(!searchWordInFile("JAVAD\\current.txt",argv[i])){
        puts("no such a file");
        return;
    }
    FILE *fp = fopen("JAVAD\\added.txt", "a");
    if (fp == NULL) {
        printf("\ano repository found\nError opening the file.\n");
        return;
    }
    fprintf(fp,"%s\n",argv[i]);
    fclose(fp);
}






////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
////////////////main////////////////main////////////////
int main(int argc , char *argv[]){
    if (argc<2){
        printf("\ano command was entered!");
        return 1;
    }


    else if(strcmp(argv[1],"config")==0){
        if (argc<4){
            printf("\atoo few arg\n\tthe correct order of command is:\n\t\tjavadi config --global(optional) user.(name/email) \"\" ");
            return 1;
        }
        else if(argc>5){
            printf("\atoo much arg\n\tthe correct order of command is:\n\t\tjavadi config --global(optional) user.(name/email) \"\" ");
            return 1;
        }
        else if (strcmp(argv[2],"--global")==0){
            if(argc==4){
                printf("\aERROR:you should specify whether name or email are to be modified!");
                return 1;
            }
            if(strcmp(argv[3],"user.name")==0){   config_name(argc,argv);   return 0;  }
            if(strcmp(argv[3],"user.email")==0){  config_email(argc,argv);  return 0;  }
            printf("\aERROR:you should specify whether name or email are to be modified!");
            return 1;
        }
        else if (strcmp(argv[2],"user.name")==0){
            if(argc==3){
                printf("\aERROR:you are supposed to enter a name!");
                return 1;
            }
            else{
                config_local_name(argc,argv);
                return 0;
            }
        }
        else if (strcmp(argv[2],"user.email")==0){
            if(argc==3){
                printf("\aERROR:you are supposed to enter an email!");
                return 1;
            }
            else{
                config_local_email(argc,argv);
                return 0;
            }
        }
        
    }
    else if(strcmp(argv[1],"add")==0){
        if(argc==2){printf("add what dude?"); return 1;}
        if(strcmp(argv[2],"-f")!=0){
            for(int i=2;i<argc;i++){
                add_file(argc,argv,i);
                char *tmp=malloc(200);
                sprintf(tmp,"copy %s JAVAD\\staged\\%s",argv[i],argv[i]);
                system(tmp);
            }
            return 0;
        }
        if(argc==3){printf("add what dude?"); return 1;}
        for(int i=3;i<argc;i++){
            add_file(argc,argv,i);
            char *tmp=malloc(200);
            sprintf(tmp,"copy %s JAVAD\\staged\\%s",argv[i],argv[i]);
            system(tmp);
        }
        return 0;
    }
    else if(0){

    }
    else if(strcmp(argv[1],"init")==0){
        system("if exist JAVAD (echo there is already a repository there!) else (mkdir JAVAD && attrib +h JAVAD &&mkdir JAVAD\\staged && mkdir JAVAD\\commits&& echo repository has been created && dir /B > \"JAVAD\\current.txt\" && echo >\"JAVAD\\added.txt\")");
    }
}