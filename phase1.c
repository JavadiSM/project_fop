//Seyed Mohammadreza Javadi 402 105 868
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <limits.h>
#define t puts("so far so good");
#define BLACK 0
#define RED 4
#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define MAGENTA 5
#define CYAN 3
#define WHITE 7
void SetColor(int ForgC);
char* getFullDirectory();

int checkline(char *line) {
    int i = 0;
    char ch;
    while ((ch = line[i]) != '\0') {
        if (ch != '\n' && ch != '\t' && ch != ' ') {
            return 0;
        }
        i++;
    }
    return 1;  //Null space!!
}
void diff(char* file1, char* file2, int lineStart1, int lineEnd1, int lineStart2, int lineEnd2) {
    FILE* fp1 = fopen(file1, "r");
    FILE* fp2 = fopen(file2, "r");
    if (fp1 == NULL || fp2 == NULL) {
        printf("Unable to open the files. Make sure the file paths are correct.\n");
        return;
    }
    char line1[256];
    char line2[256];
    int lineNumber1 = 1;
    int lineNumber2 = 1;
    for(int i=0;i<lineStart1-1;i++){
        fgets(line1,255,fp1);
    }
    for(int i=0;i<lineStart2-1;i++){
        fgets(line2,255,fp2);
    }
    for(int i=lineStart1-1,j=lineStart2-1;i<lineEnd1&&j<lineEnd2;i++,j++){
        if(i<lineEnd1) fgets(line1,255,fp1);
        if(j<lineEnd2) fgets(line2,255,fp2);
        while(checkline(line1)){
            if(i<lineEnd1) {
                fgets(line1,255,fp1);
                i++;
            }
            else{
                i=lineEnd1;
                break;
            }
        }
        while(checkline(line2)){
            if(j<lineEnd2) {
                fgets(line2,255,fp2);
                j++;
            }
            else{
                j=lineEnd2;
                break;
            }
        }
        if(strcmp(line1,line2)!=0){
            printf("<<<<<<<<<<\n");
            SetColor(RED);
            printf("%s %d\n",file1, i+1);
            SetColor(CYAN);
            printf("%s\n",line1);
            SetColor(RED);
            printf("%s %d\n",file2, j+1);
            SetColor(GREEN);
            printf("%s\n",line2);
            SetColor(WHITE);
            printf(">>>>>>>>>>\n");
        }
    }
    fclose(fp1);
    fclose(fp2);
}
char* getAbsolutePath(const char* fileName) {
    char* absolutePath = malloc(PATH_MAX * sizeof(char));
    if (_fullpath(absolutePath, fileName, PATH_MAX) != NULL) {
        return absolutePath;
    } else {
        free(absolutePath);
        return NULL;
    }
}
int searchJAVADFolder() {
    char currentDir[256];
    char parentDir[256];
    char *originalDir = getFullDirectory();
    getcwd(currentDir, sizeof(currentDir)); 
    int dfgsdfg = 0;
    while (dfgsdfg < 20) {
        dfgsdfg++;
        DIR *dir = opendir(currentDir);
        struct dirent *dirEntry;
        if (dir) {
            while ((dirEntry = readdir(dir)) != NULL) {
                if (strcmp(dirEntry->d_name, "JAVAD") == 0) {
                    closedir(dir);
                    chdir(originalDir);
                    return 1;
                }
            }
            closedir(dir);
        }
        if (strcmp(currentDir, "/") == 0 || strcmp(currentDir, "\\") == 0)
            break;
        else {
            strcpy(parentDir, currentDir);
            strcat(parentDir, "/..");
            chdir(parentDir);
            getcwd(currentDir, sizeof(currentDir));
        }
    }
    chdir(originalDir);
    return 0; //not found
}
char* getFullDirectory() {
    char* fullPath = (char*)malloc(MAX_PATH * sizeof(char));
    if (fullPath == NULL) {
        return NULL;
    }
    DWORD pathLen = GetModuleFileNameA(NULL, fullPath, MAX_PATH);
    if (pathLen == 0) {
        free(fullPath);
        return NULL;
    }
    char* lastSlash = strrchr(fullPath, '\\');
    if (lastSlash == NULL) {
        free(fullPath);
        return NULL;
    }
    *(lastSlash + 1) = '\0';
    return fullPath;
}
void SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
void printFileContent(const char* address) {
    FILE* file = fopen(address, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}
int compareFiles(char* addfile1, char* addfile2) {
    int ch1, ch2;
    FILE* file1=fopen(addfile1,"r");
    FILE* file2=fopen(addfile2,"r");
    while (((ch1 = fgetc(file1)) != EOF) && ((ch2 = fgetc(file2)) != EOF)) {
        if (ch1 != ch2)
            return 0;
    }
    if (ch1 == EOF && ch2 == EOF)
        return 1;  // Files are same
    return 0;  // Files are different
}
unsigned long hash_function(char *str){
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
char *antihash(unsigned long hash){
    int i = 0;
    char *str = malloc(sizeof(char) * 72);
    while (hash != 0) {
        str[i] = hash % 128;
        hash = hash / 128;
        i++;
    }
    str[i] = '\0';
    return str;
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
        if (ch == EOF)
            break; 
        if (ch == '\n') 
            count++; 
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
    FILE *fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\name.txt", "w");
    fprintf(fp,"%s",argv[4]);
    fclose(fp);
    system("attrib +h C:\\Users\\Asus\\Desktop\\neogit\\name.txt");
}
void config_email(int argc,char *argv[]){
    FILE *fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\global_email.txt", "w");
    fprintf(fp,"%s",argv[4]);
    fclose(fp);
    system("attrib +h C:\\Users\\Asus\\Desktop\\neogit\\global_email.txt");
}
void config_local_name(int argc,char *argv[]){
    FILE *fp=fopen("name.txt", "w");
    fprintf(fp,"%s",argv[3]);
    fclose(fp);
    system("attrib +h name.txt");
}
void config_local_email(int argc,char *argv[]){
    FILE *fp=fopen("email.txt", "w");
    fprintf(fp,"%s",argv[3]);
    fclose(fp);
    system("attrib +h email.txt");
}
void add_file(int argc, char *argv[],int i) {
    FILE *sdfsd=fopen("JAVAD\\added.txt","r");
    if (sdfsd== NULL) {
        printf("\ano repository found\nError opening the file.\n");
        fclose(sdfsd);
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
    
    if(searchWordInFile("JAVAD\\added.txt",argv[i])){
        return;
    }
    fprintf(fp,"%s\n",argv[i]);
    FILE * last=fopen("JAVAD\\lastadd.txt", "a");
    fprintf(last,"%s\n",argv[i]);
    fclose(last);
    fclose(fp);
}
void show_added(int argc,char *argv[]){
    system("dir /B > \"JAVAD\\current.txt\"");
    FILE *fp_add = fopen("JAVAD\\added.txt", "r");
    FILE *fp_cur = fopen("JAVAD\\current.txt", "r");
    if (fp_add== NULL||fp_cur== NULL) {
        printf("\ano repository found\nError opening the file.\n");
        return;
    }
    int n=countLinesInFile("JAVAD\\current.txt");
    char *hey=(char *)malloc(100);
    SetColor(RED);
    puts("unstaged ones:\n");
    for(int i=0;i<n;i++){
        fgets(hey,100,fp_cur);
        if(!searchWordInFile("JAVAD\\added.txt",hey)){
            puts(hey);
        }
    }
    SetColor(GREEN);
    fgets(hey,100,fp_add);
    puts("staged ones:\n");
    while(fgets(hey,100,fp_add)!=NULL){
        puts(hey);
    }
    SetColor(WHITE);
    fclose(fp_add);
    fclose(fp_cur);
}

void reset(int argc,char * argv[],int counter){
    system("dir /B > \"JAVAD\\current.txt\"");
    FILE *stg = fopen("JAVAD\\added.txt", "r");
    FILE *tempstg = fopen("JAVAD\\addedtemp.txt", "w");
    FILE *unstg = fopen("JAVAD\\unstaged.txt", "a");
    FILE * last=fopen("JAVAD\\lastun.txt", "a");
    fprintf(last,"%s\n",argv[counter]);
    fclose(last);
    fprintf(unstg,"%s",argv[counter]);
    char *ch=malloc(100);

    while(fgets(ch,100,stg)!=NULL){
        if(strncmp(ch,argv[counter],strlen(argv[counter]))==0){
            ;
        }
        else{
            fprintf(tempstg,"%s",ch);
        }
    }
    fclose(stg);
    fclose(tempstg);
    fclose(unstg);
    system("del JAVAD\\added.txt");
    system("rename JAVAD\\addedtemp.txt added.txt");
}
void appendTimeToFile(const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    time_t currentTime;
    time(&currentTime);
    struct tm* timeInfo = localtime(&currentTime);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%c", timeInfo);
    fprintf(file, "Time : %s\n", timeStr);
    fclose(file);
}
void commit(int argc,char *argv[]){
    char sys[500];
    FILE *fp=fopen("email.txt", "r");
    if(fp==NULL){
        fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\global_email.txt", "r");
        if (fp==NULL) {puts("no email entered use config \a"); return;}
        }
    FILE *name=fopen("name.txt", "r");
    if(name==NULL){
        name=fopen("C:\\Users\\Asus\\Desktop\\neogit\\name.txt", "r");
        if (name==NULL) {puts("no name entered use config \a"); return;}
        }
    sprintf(sys,"mkdir JAVAD\\commits\\%lu",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"echo %lu >JAVAD\\commits\\%lu\\commit.txt",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"JAVAD\\commits\\%lu\\commit.txt",hash_function(argv[3]));
    char *zaman=malloc(1000);
    FILE * com=fopen(sys,"a");
    fgets(sys,300,fp);
    fprintf(com,"email: %s\n",sys);
    fgets(sys,300,name);
    fprintf(com,"name: %s\n",sys);
    FILE *branch=fopen("JAVAD\\curhead.txt","r");
    fgets(sys,300,branch);
    fprintf(com,"branch: %s\n",sys);
    fclose(branch);
    fprintf(com,"msg: %s\n",argv[3]);
    sprintf(sys,"time /t > JAVAD\\commits\\%lu\\t.txt",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"date /t > JAVAD\\commits\\%lu\\d.txt",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"mkdir JAVAD\\commits\\%lu\\files",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"copy JAVAD\\staged JAVAD\\commits\\%lu\\files",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"copy JAVAD\\added.txt JAVAD\\commits\\%lu",hash_function(argv[3]));
    system(sys);
    system("dir /B >JAVAD\\current.txt");
    sprintf(sys,"copy JAVAD\\current.txt JAVAD\\commits\\%lu",hash_function(argv[3]));
    system(sys);
    sprintf(sys,"JAVAD\\current.txt JAVAD\\commits\\%lu",hash_function(argv[3]));
    system(sys);
    fclose(fp);
    fclose(name);
    fclose(com);
    sprintf(sys,"copy JAVAD\\curhead.txt JAVAD\\commits\\%lu\\curhead.txt",hash_function(argv[3]));
    system(sys);
    FILE * chand=fopen("JAVAD\\commits.txt","a");
    fprintf(chand,"%lu\n",hash_function(argv[3]));
    system("dir /B > \"JAVAD\\current.txt\" ");
    system("echo  >\"JAVAD\\unstaged.txt\"");
    system("echo  >\"JAVAD\\lastadd.txt\"");
    system("rmdir /Q /S JAVAD\\unstaged");
    system("mkdir JAVAD\\unstaged");
    fclose(chand);
}
int stringToNumber(const char* str) {
    int num = 0;
    while (*str != '\0') {
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}

int isafter(char *input, const char *filename) {
    FILE *file;
    char file_date[20];
    file = fopen(filename, "r");
    if (file == NULL) {
    printf("Failed to open the file.\n");
    return -1;
    }
    fgets(file_date, sizeof(file_date), file);
    fclose(file);
    // Convert input and file_date using sscanf
    struct tm tm_input, tm_file;
    if (sscanf(input, "%3s %d/%d/%d", tm_input.tm_wday, &tm_input.tm_mon, &tm_input.tm_mday, &tm_input.tm_year) != 4 ||
    sscanf(file_date, "%3s %d/%d/%d", tm_file.tm_wday, &tm_file.tm_mon, &tm_file.tm_mday, &tm_file.tm_year) != 4) {
    printf("Error converting time strings.\n");
    return -1;
    }

    tm_input.tm_mon -= 1; // Adjust month to be 0-indexed (0-11)
    tm_file.tm_mon -= 1;

    // Convert struct tm to time_t
    time_t time_input = mktime(&tm_input);
    time_t time_file = mktime(&tm_file);

    if (time_input < time_file) {
    return 1; // before
    } else if (time_input > time_file) {
    return 0; // after
    } else {
    return -1; // same
}
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main(int argc , char *argv[]){
    if (argc<2){
        printf("\ano command was entered!");
        return 1;
    }
    if(searchWordInFile("alias.txt",argv[1])){
        char h[100];
        sprintf(h,"%s.txt",argv[1]);
        FILE *fp=fopen(h,"r");
        char sys[400];
        fgets(sys,399,fp);
        sys[strcspn(sys,"\n")]='\0';
        puts(sys);
        system(sys);
        return 0;
    }
    else if(searchWordInFile("C:\\Users\\Asus\\Desktop\\neogit\\alias.txt",argv[1])){
        char temp[200];
        sprintf(temp,"C:\\Users\\Asus\\Desktop\\neogit\\%s.txt",argv[1]);
        FILE *fp=fopen(temp,"r");
        char sys[400];
        fgets(sys,399,fp);
        size_t len = strlen(sys);
        if (len > 0 && sys[len - 1] == '\n') {
            sys[len - 1] = '\0';
        } system(sys);
    }

    if(strcmp(argv[1],"config")==0){
        if (argc<4){
            printf("\atoo few arg\n\tthe correct order of command is:\n\t\tjavadi config --global(optional) user.(name/email) \"\" ");
            return 1;
        }
        else if(strncmp(argv[2],"alias",5)==0){
            char mm[200];
            sprintf(mm,"%s.txt\0",argv[3]);
            FILE *fp=fopen(mm,"w");
            char sys[500];
            FILE* tt=fopen("alias.txt","a");
            fprintf(tt,"%s",argv[3]);
            sprintf(sys,"attrib +h %s",mm);
            system(sys);
            fprintf(fp,"%s",argv[4]);
            fclose(fp);
            fclose(tt);
            return 0;
        }
        else if (strcmp(argv[2],"--global")==0){
            if(strncmp(argv[3],"alias",5)==0){
                char mm[200];
                sprintf(mm,"C:\\Users\\Asus\\Desktop\\neogit\\%s.txt",argv[4]);
                FILE *fp[2];
                fp[0]=fopen(mm,"w");
                fp[1]=fopen("C:\\Users\\Asus\\Desktop\\neogit\\alias.txt","a");
                fprintf(fp[0],"%s",argv[5]);
                fprintf(fp[1],"%s",argv[4]);
                fclose(fp[0]);
                fclose(fp[1]);
                return 0;
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
    else if(strcmp(argv[1],"init")==0){
        if(argc!=2){printf("\awhat???"); return 1;}
        if(searchJAVADFolder()){puts("there is already a repository!"); return 0;}
        system("if exist JAVAD (echo there is already a repository!) else (mkdir JAVAD && attrib +h JAVAD &&mkdir JAVAD\\staged &&mkdir JAVAD\\unstaged && mkdir JAVAD\\commits&& echo repository has been created && dir /B > \"JAVAD\\current.txt\" && echo  >\"JAVAD\\added.txt\" && echo  >alias.txt && attrib +h alias.txt && echo  >\"JAVAD\\unstaged.txt\" && echo  >\"JAVAD\\lastadd.txt\" && echo  >\"JAVAD\\comshort.txt\" && echo >\"JAVAD\\commits.txt\"  && echo master >\"JAVAD\\curhead.txt\" &&echo master >\"JAVAD\\branchlist.txt\" && echo master >branchlist.txt && attrib +h branchlist.txt && echo > \"JAVAD\\tags.txt\" )");
        return 0;
    }
    if(!searchJAVADFolder()){
        puts("no repository found\a\a!");
        return 0;
    }

    if(strcmp(argv[1],"add")==0){
        FILE *sdfsd=fopen("JAVAD\\added.txt","r");
        if (sdfsd== NULL) {
            printf("\ano repository found\nError opening the file.\n");
            fclose(sdfsd);
            return 1;
        }
        fclose(sdfsd);
        if(argc==2){printf("\aadd what dude?"); return 1;}
        if(strcmp(argv[2],"-n")==0){
            if(argc!=4){printf("\ahow many dude!"); return 1;}
            show_added(argc,argv);
            return 0;
        }
        FILE * lastadded=fopen("JAVAD\\lastadd.txt", "w");
        fprintf(lastadded,"");
        fclose(lastadded);
        if(strcmp(argv[2],"-redo")==0){
            int n=countLinesInFile("JAVAD\\unstaged.txt")-1;
            FILE *ha=fopen("JAVAD\\unstaged.txt","r");
            char *yy[1];
            yy[0]=(char *)malloc(200);
            fgets(yy[0],180,ha);
            for(int i=0;i<n;i++){
                fgets(yy[0],180,ha);
                yy[0][strcspn(yy[0],"\n")]='\0';
                add_file(argc,yy,0);
                char *tmp=malloc(200);
                sprintf(tmp,"copy JAVAD\\unstaged\\%s JAVAD\\staged\\%s",yy,yy);
                system(tmp);
            }
            fclose(ha);
            return 0;
        }
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
    else if(strcmp(argv[1],"status")==0){
        if(argc!=2){puts("\a huh?");}
        char  sys[1000],temp[100],copa[100],kk[100];
        FILE*fp=fopen("JAVAD\\commits.txt","r");
        int cc=countLinesInFile("JAVAD\\commits.txt");
        for(int i=0;i<cc;i++){
            fgets(temp,99,fp);
        }
        fclose(fp);
        temp[strcspn(temp,"\n")]='\0';
        sprintf(sys,"JAVAD\\commits\\%s\\added.txt",temp);
        FILE * p=fopen(sys,"r");
        FILE *add=fopen("JAVAD\\added.txt","r");
        int n=countLinesInFile("JAVAD\\added.txt");
        fgets(copa,100,add);
        char pp[100];
        for(int i=0;i<n-1;i++){
            fgets(copa,100,add);
            copa[strcspn(copa,"\n")]='\0';
            sprintf(kk,"JAVAD\\commits\\%s\\files\\%s",temp,copa);
            if(searchWordInFile(sys,copa)){
                if(compareFiles(kk,copa)){
                    continue;
                }
                printf("%s +M\n",copa);
                continue;
            }
            printf("%s +A\n",copa);
        }
    }
    else if(strcmp(argv[1],"reset")==0){
        if(argc==2){printf("\atoo few args"); return 1;}
        if(strcmp(argv[2],"-undo")==0){
            FILE * last=fopen("JAVAD\\lastun.txt", "w");
            fprintf(last,"");
            fclose(last);
            FILE * las=fopen("JAVAD\\lastadd.txt","r");
            char * coppa[1];
            coppa[0]=malloc(100);
            char *tmp=malloc(400);
            while(fgets(coppa[0],100,las)!=NULL){
                sprintf(tmp,"copy JAVAD\\staged\\%s JAVAD\\unstaged\\%s",coppa[0],coppa[0]);
                system(tmp);
                sprintf(tmp,"del JAVAD\\staged\\%s",coppa[0]);
                system(tmp);
                reset(argc,coppa,0);
            }
            fclose(las);
            FILE * lst=fopen("JAVAD\\lastadd.txt", "w");
            fprintf(lst,"");
            fclose(lst);
            return 0;
        }
        FILE * last=fopen("JAVAD\\lastun.txt", "w");
        fprintf(last,"");
        fclose(last);
        if(strcmp(argv[2],"-f")==0){
            for(int i=3;i<argc;i++){
                // add_file(argc,argv,i);
                char *tmp=malloc(200);
                sprintf(tmp,"copy JAVAD\\staged\\%s JAVAD\\unstaged\\%s",argv[i],argv[i]);
                system(tmp);
                sprintf(tmp,"del JAVAD\\staged\\%s",argv[i]);
                system(tmp);
                reset(argc,argv,i);
            }
            return 0;
        }
        for(int i=2;i<argc;i++){
            char *tmp=malloc(200);
            sprintf(tmp,"copy JAVAD\\staged\\%s JAVAD\\unstaged\\%s",argv[i],argv[i]);
            system(tmp);
            sprintf(tmp,"del JAVAD\\staged\\%s",argv[i]);
            system(tmp);
            reset(argc,argv,i);
        }
        return 0;
    }
    else if(strcmp(argv[1],"log")==0){
        if(argc==2){
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS------------------------");
            for(int i=0;i<n-1;i++){
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS------------------------");
            }
            SetColor(WHITE);
            return 0;
        }
        /////
        if(strcmp(argv[2],"-n")==0){
            if(argc==3){puts("how manyyyyyy \a\a"); return 1;}
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            for(int i=0;i<n-1;i++){
                if(i==stringToNumber(argv[3])){
                    break;
                }
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            }
            SetColor(WHITE);
            return 0;
        }//////////////////////////////////////////
        if(strcmp(argv[2],"-branch")==0){
            if(argc==3){puts("branch name? \a\a"); return 1;}
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            char IDK[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            int controler=0;
            for(int i=0;i<n-1;i++){
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                sprintf(IDK,"branch: %s",argv[3]);
                if(searchWordInFile(str,IDK)==0){
                    controler++;
                    continue; 
                }
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            }
            if(controler==n-1){
                puts("branch not found!!\a");
            }
            SetColor(WHITE);
            return 0;
        }
        if(strcmp(argv[2],"-author")==0){
            if(argc==3){puts("name? \a\a"); return 1;}
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            char IDK[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            int controler=0;
            for(int i=0;i<n-1;i++){
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                sprintf(IDK,"name: %s",argv[3]);
                if(searchWordInFile(str,IDK)==0){
                    controler++;
                    continue; 
                }
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            }
            if(controler==n-1){
                puts("name not found!!\a");
            }
            SetColor(WHITE);
            return 0;
        }
        if(strcmp(argv[2],"-since")==0){
            if(argc==3){puts("date? \a\a"); return 1;}
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            char IDK[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            int controler=0;
            for(int i=0;i<n-1;i++){
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                if(!isafter(argv[3],str)){
                    controler++;
                    continue; 
                }
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            }
            if(controler==n-1){
                puts("not found!!\a");
            }
            SetColor(WHITE);
            return 0;
        }
        if(strcmp(argv[2],"-before")==0){
            if(argc==3){puts("date? \a\a"); return 1;}
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            char IDK[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            int controler=0;
            for(int i=0;i<n-1;i++){
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                if(isafter(argv[3],str)){
                    controler++;
                    continue; 
                }
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            }
            if(controler==n-1){
                puts("not found!!\a");
            }
            SetColor(WHITE);
            return 0;
        }
        if(strcmp(argv[2],"-search")==0){
            if(argc==3){puts("word? \a\a"); return 1;}
            char steadfist[countLinesInFile("JAVAD\\commits.txt")-1][100];
            char str[100];
            FILE *fp=fopen("JAVAD\\commits.txt","r");
            fgets(str,100,fp);
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=n-2;i>-1;i--){
                fgets(steadfist[i],100,fp);
            }
            char logtime[100];
            char IDK[100];
            int hjh;
            FILE * tttt[n];
            FILE * dddd[n];
            SetColor(BLUE);
            int controler=0;
            for(int i=0;i<n-1;i++){
                int wasthere=0;
                hjh=strlen(steadfist[i]);
                steadfist[i][hjh-1]='\0';
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                for(int z=3;z<argc;z++){
                    if(searchWordInFile(str,argv[z])){
                        wasthere++;
                        controler++;
                        break; 
                    }
                }
                if(wasthere==0) continue;
                sprintf(str,"JAVAD\\commits\\%s\\t.txt",steadfist[i]);
                tttt[i]=fopen(str,"r");
                sprintf(str,"JAVAD\\commits\\%s\\d.txt",steadfist[i]);
                dddd[i]=fopen(str,"r");
                SetColor(RED);
                printf("%s\n",steadfist[i]);
                fgets(logtime,100,tttt[i]);
                printf("time :%s",logtime);
                fclose(tttt[i]);
                fgets(logtime,100,dddd[i]);
                printf("date :%s",logtime);
                fclose(dddd[i]);
                if(i%2==0) SetColor(MAGENTA);
                else SetColor(YELLOW);
                sprintf(str,"JAVAD\\commits\\%s\\commit.txt",steadfist[i]);
                printFileContent(str);
                sprintf(str,"JAVAD\\commits\\%s\\added.txt",steadfist[i]);
                int k=countLinesInFile(str)-1;
                printf("how many were added: %d\n\n",k);
                SetColor(BLUE);
                puts("JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS----JAVADI-PRESENTS");
            }
            if(controler==0){
                puts("not found!!\a");
            }
            SetColor(WHITE);
            return 0;
        }
    }
    else if(strcmp(argv[1],"branch")==0){
        if(argc==2){printFileContent("branchlist.txt"); return 0;}
        FILE *br=fopen("branchlist.txt","a");
        system("attrib -h branchlist.txt");
        FILE *ii=fopen("JAVAD\\curhead.txt","r");
        if(searchWordInFile("branchlist.txt",argv[2])){ puts("there is already a branch with that name\a ");}
        fprintf(br,"%s\n",argv[2]);
        char sys[100];
        char curh[100];
        sprintf(sys,"xcopy /e /i JAVAD %s",argv[2]);
        system(sys);
        fgets(curh,100,ii);
        int n=strlen(curh);
        curh[strcspn(curh," ")]='\0';
        fclose(br);
        fclose(ii);
        sprintf(sys,"%s\\curhead.txt",argv[2]);
        FILE * haha=fopen(sys,"w");
        fprintf(haha,"%s",argv[2]);
        fclose(haha);
    }
    else if(strcmp(argv[1],"checkout")==0){
        if(strcmp("HEAD-n",argv[2])==0){
            if(countLinesInFile("JAVAD\\commits.txt")==1){puts("no commit"); return 0;}
            if(countLinesInFile("JAVAD\\commits.txt")-stringToNumber(argv[3])<2){puts("no commit there before the head"); return 0;}
            char  sys[1000];
            char temp[100];
            FILE*fp=fopen("JAVAD\\commits.txt","r");
            int cc=countLinesInFile("JAVAD\\commits.txt")-stringToNumber(argv[3]);
            for(int i=0;i<cc;i++){
                fgets(temp,99,fp);
            }
            temp[strcspn(temp,"\n")]='\0';
            system("rmdir /Q /S JAVAD\\unstaged");
            system("rmdir /Q /S JAVAD\\staged");
            system("mkdir JAVAD\\unstaged");
            system("mkdir JAVAD\\staged");
            puts(temp);
            sprintf(sys,"copy /Y JAVAD\\commits\\%s\\files .",temp);
            system(sys);
            sprintf(sys,"copy /Y JAVAD\\commits\\%s\\curhead.txt JAVAD\\curhead.txt",temp);
            system(sys);
            return 0;
        }
        if(strcmp("HEAD",argv[2])==0){
            if(countLinesInFile("JAVAD\\commits.txt")==1){puts("no commit"); return 0;}
            char  sys[1000];
            char temp[100];
            FILE*fp=fopen("JAVAD\\commits.txt","r");
            int cc=countLinesInFile("JAVAD\\commits.txt");
            for(int i=0;i<cc;i++){
                fgets(temp,99,fp);
            }
            temp[strcspn(temp,"\n")]='\0';
            system("rmdir /Q /S JAVAD\\unstaged");
            system("rmdir /Q /S JAVAD\\staged");
            system("mkdir JAVAD\\unstaged");
            system("mkdir JAVAD\\staged");
            puts(temp);
            sprintf(sys,"copy /Y JAVAD\\commits\\%s\\files .",temp);
            system(sys);
            sprintf(sys,"copy /Y JAVAD\\commits\\%s\\curhead.txt JAVAD\\curhead.txt",temp);
            system(sys);
            // FILEinja
            return 0;
        }
        if(!searchWordInFile("branchlist.txt",argv[2])){
        // if(countLinesInFile("JAVAD\\added.txt")!=1){ puts("save changes and commit them before entering another commit!\a"); return 0;}
            if(searchWordInFile("JAVAD\\commits.txt",argv[2])){
                char  sys[1000];
                char temp[100];
                system("rmdir /Q /S JAVAD\\unstaged");
                system("rmdir /Q /S JAVAD\\staged");
                system("mkdir JAVAD\\unstaged");
                system("mkdir JAVAD\\staged");
                sprintf(sys,"copy /Y JAVAD\\commits\\%s\\files JAVAD\\staged",argv[2]);
                system(sys);
                sprintf(sys,"copy /Y JAVAD\\commits\\%s\\files .",argv[2]);
                system(sys);
                sprintf(sys,"copy /Y JAVAD\\commits\\%s\\added.txt JAVAD\\added.txt",argv[2]);
                system(sys);
                sprintf(sys,"copy /Y JAVAD\\commits\\%s\\curhead.txt JAVAD\\curhead.txt",argv[2]);
                system(sys);
                return 0;
            }
            puts("it was not branch nor commit sir\a");
            return 0;
        }
        // if(countLinesInFile("JAVAD\\added.txt")!=1){ puts("save changes and commit them before entering another branch!\a"); return 0;}
        char sys[1000];
        char temp[100];
        FILE * m=fopen("JAVAD\\curhead.txt","r");
        fgets(temp,99,m);
        fclose(m);
        int n=strlen(temp);
        temp[strcspn(temp,"\n")]='\0';
        temp[strcspn(temp," ")]='\0';
        system("attrib -h JAVAD");
        sprintf(sys,"rename JAVAD %s",temp);
        system(sys);
        sprintf(sys,"attrib +h %s",temp);
        system(sys);
        sprintf(sys,"attrib -h %s",argv[2]);
        system(sys);
        sprintf(sys,"rename %s JAVAD",argv[2]);
        system(sys);
        system("attrib +h JAVAD");
        return 0;
    }
    //cmd command:rename oldfilename.txt newfilename.txt
    else if(strcmp(argv[1],"commit")==0){
        if(strcmp(argv[2],"-m")!=0){
            strcpy(argv[3],argv[2]);
            if(searchWordInFile("JAVAD\\comsh.txt",argv[2])){

                return 0;
            }
            else{
                puts("no shortcut was found\a");
                return 1;
            }
        }
        if(strlen(argv[3])==0){
                puts("\ano msg was entered\a");
                return 1;
        }
        if(strlen(argv[3])>72){
            puts("too long, below 72 letters are permitted");
            return 0;
        }
        if(countLinesInFile("JAVAD\\added.txt")==1){
            puts("no file is staged");
            return 0;
        }
        commit(argc,argv);
        return 0;
    }
    else if(strcmp(argv[1],"diff")==0){
        if(strcmp(argv[2],"-c")==0){
            char add1[100],add2[100],file[100],addressfile1[500],addressfile2[500];
            FILE * fop=fopen("JAVAD\\commits.txt","r");
            if(fop==NULL) {puts("\ano commit yet"); fclose(fop); return 0;}
            fclose(fop);
            if(countLinesInFile("JAVAD\\commits.txt")<2){puts("not enough commit\a yet"); return 0;}
            sprintf(add1,"JAVAD\\commits\\%s\\added.txt",argv[3]);
            sprintf(add2,"JAVAD\\commits\\%s\\added.txt",argv[4]);
            FILE * y[2];
            y[0]=fopen(add1,"r");
            y[1]=fopen(add2,"r");
            fgets(file,99,y[0]);
            for (int i = 1; i < countLinesInFile(add1); i++){
                fgets(file,99,y[0]);
                int n=strlen(file);
                file[strcspn(file,"\n")]='\0';
                if(searchWordInFile(add2,file)){
                    sprintf(addressfile1,"JAVAD\\commits\\%s\\files\\%s",argv[3],file);
                    sprintf(addressfile2,"JAVAD\\commits\\%s\\files\\%s",argv[4],file);
                    diff(addressfile1,addressfile2,1,countLinesInFile(addressfile1),1,countLinesInFile(addressfile2));
                }
            }
            return 0;
        }
        if(argc!=11){puts("\awrong syntax"); return 0;}
        diff(argv[3],argv[4],stringToNumber(argv[6]),stringToNumber(argv[7]),stringToNumber(argv[9]),stringToNumber(argv[10]));
    }
    else if(strcmp(argv[1],"tag")==0){
        if(argc==2){printFileContent("JAVAD\\tags.txt"); return 0;}
        if(strcmp(argv[2],"show")==0){
            char a[100];
            sprintf(a,"JAVAD\\%s.txt",argv[3]);
            printFileContent(a);
            return 0;
        }
        FILE *tags=fopen("JAVAD\\tags.txt","a");
        if(searchWordInFile("JAVAD\\tags.txt",argv[3])&&(argc!=9&&strcmp(argv[6],"-f")!=0&&strcmp(argv[4],"-f")!=0)){
            puts("there is already a tag with that name\a");
            fclose(tags);
            return 0;
        }
        fprintf(tags,"%s\n",argv[3]);
        fclose(tags);
        char sakht[100];
        sprintf(sakht,"JAVAD\\%s.txt",argv[3]);
        FILE *tag=fopen(sakht,"w");
        fprintf(tag,"tag %s\n",argv[3]);
        FILE *fp=fopen("email.txt", "r");
        if(fp==NULL){
            fp=fopen("C:\\Users\\Asus\\Desktop\\neogit\\global_email.txt", "r");
            if (fp==NULL) {puts("no email entered use config \a"); return 0;}
            else    fgets(sakht,99,fp);
            }
        else fgets(sakht,99,fp);
        fprintf(tag,"Author: %s",sakht);
        FILE *name=fopen("name.txt", "r");
        if(name==NULL){
            name=fopen("C:\\Users\\Asus\\Desktop\\neogit\\name.txt", "r");
            if (name==NULL) {puts("no name entered use config \a"); return 0;}
            else    fgets(sakht,99,name);
        }
        else  fgets(sakht,99,name);
        fprintf(tag," %s\n",sakht);
        FILE *com;
        if(argc>6&&strcmp("-c",argv[6])==0){
            char in[200];
            sprintf(in,"JAVAD\\commits\\%s\\commit.txt",argv[7]);
            com=fopen(in,"r");
            fprintf(tag,"commit: %s\n",argv[7]);
        }
        else if(argc>4&&strcmp("-c",argv[4])==0){
            char in[200];
            sprintf(in,"JAVAD\\commits\\%s\\commit.txt",argv[5]);
            com=fopen(in,"r");
            fprintf(tag,"commit: %s\n",argv[5]);
        }
        else {
            char in[200];
            sprintf(in,"JAVAD\\commits.txt");
            com=fopen(in,"r");
            int n=countLinesInFile("JAVAD\\commits.txt");
            for(int i=0;i<n;i++){
                fgets(in,199,com);
            }
            fprintf(tag,"commit: %s",in);
        }
        if(argc>4&&strcmp("-m",argv[4])==0)
            fprintf(tag,"Message: %s\n",argv[5]);
        else
            fprintf(tag,"Message: NON\n");
        sprintf(sakht,"JAVAD\\%s.txt",argv[3]);
        fclose(com);
        fclose(tag);fclose(name);
        fclose(fp);
        appendTimeToFile(sakht);
    }
    else if(strcmp(argv[1],"merge")==0&&strcmp(argv[2],"-b")==0){
        char a[100],b[300],input[100];
        FILE * fop=fopen("branchlist.txt","r");
        if(fop==NULL) {fop=fopen("C:\\Users\\Asus\\Desktop\\neogit\\branchlist.txt","r");}
        fclose(fop);
        char head1[200],head2[200];
        FILE *ch=fopen("JAVAD\\curhead.txt","r");
        fgets(head1,39,ch);
        head1[strcspn(head1,"\n")]='\0';
        int flag=0;
        if(strcmp(argv[4],head1)==0){
            puts("can not change the branch you are now\a\a");
            fclose(ch);
            return 0;
        }
        if(strcmp(argv[3],head1)==0){
            sprintf(a,"JAVAD\\commits.txt");
            flag=1;
        }
        else sprintf(a,"%s\\commits.txt",argv[3]);
        fclose(ch);
        sprintf(b,"%s\\commits.txt",argv[4]);
        FILE *com=fopen(b,"r");
        FILE *ca=fopen(a,"r");
        char files[countLinesInFile(b)][150];
        int f=countLinesInFile(a);
        for(int i=0;i<f;i++){
            fgets(head2,99,ca);
            head2[strcspn(head2,"\n")]='\0';
        }
        int n=countLinesInFile(b);
        for(int i=0;i<n;i++){
            fgets(input,99,com);
            input[strcspn(input,"\n")]='\0';
        }
        fclose(com);
        sprintf(b,"%s\\commits\\%s\\added.txt",argv[4],input);
        char hash[100];
        strcpy(hash,input);
        FILE * added=fopen(b,"r");
        n=countLinesInFile(b);
        char diff1[200],diff2[200];
        for(int i=0;i<n;i++){
            fgets(input,99,com);
            input[strcspn(input,"\n")]='\0';
            if(searchWordInFile(a,input)&&!compareFiles(a,input)){
                puts(hash);
                sprintf(diff2,"%s\\commits\\%s\\files\\%s",argv[4],hash,input);
                if(flag==1) sprintf(diff1,"JAVAD\\commits\\%s\\files\\%s",head2,input);
                else sprintf(diff1,"%s\\commits\\%s\\files\\%s",argv[3],head2,input);
                diff(diff1,diff2,1,countLinesInFile(diff1),1,countLinesInFile(diff2));
                continue;
            }
            else {
                char sys[100];
                if(flag==1) {sprintf(sys,"copy /y  %s\\commits\\%s\\files\\%s JAVAD\\commits\\%s\\files\\%s  ",argv[4],hash,input,head2,input);
                system(sys);}
                else {sprintf(sys,"copy /y  %s\\commits\\%s\\files\\%s %s\\commits\\%s\\files\\%s  ",argv[4],hash,input,argv[3],head2,input);
                system(sys);}
            }
        }
        char s[100];
        sprintf(s,"rmdir /s /q %s",argv[4]);
        return 0;
    }
    return 0;
}