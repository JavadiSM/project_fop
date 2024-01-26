#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

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
    FILE *fp=fopen("name.txt", "w");
    fprintf(fp,"%s",argv[3]);
    fclose(fp);
}
void config_local_email(int argc,char *argv[]){
    FILE *fp=fopen("email.txt", "w");
    fprintf(fp,"%s",argv[3]);
    fclose(fp);
}









int main(int argc , char *argv[]){
    if (argc<2){
        printf("no command was entered!");
        return 1;
    }


    else if(strcmp(argv[1],"config")==0){
        if (argc<4){
            printf("the correct order of command is:\njavadi config --global(optional) user.(name/email) \"\" ");
        }
        else if (strcmp(argv[2],"--global")==0){
            if(strcmp(argv[3],"user.name")==0){   config_name(argc,argv);   return 0;  }
            if(strcmp(argv[3],"user.email")==0){  config_email(argc,argv);  return 0;  }
            printf("ERROR:you should specify whether name or email are to be modified!");
            return 1;
        }
        else if (strcmp(argv[2],"user.name")==0){
            if(argc==3){
                printf("ERROR:you are supposed to enter a name!");
                return 1;
            }
            else{
                config_local_name(argc,argv);
                return 0;
            }
        }
        else if (strcmp(argv[2],"user.email")==0){
            if(argc==3){
                printf("ERROR:you are supposed to enter an email!");
                return 1;
            }
            else{
                config_local_email(argc,argv);
                return 0;
            }
        }

    }




    else if(0){

    }
}