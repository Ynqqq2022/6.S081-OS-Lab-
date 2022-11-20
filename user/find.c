#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void fun(char* path,char *target){
    struct dirent de;
    int fd=open(path,0);
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum==0||!strcmp(de.name,".")||!strcmp(de.name,".."))
            continue;
        char *p =path+strlen(path);
        *p='/';
        strcpy(p+1,de.name);
        int fd1 = open(path,0);
        struct stat st;
        fstat(fd1, &st);
        close(fd1);     //must close file or may cause something wrong...
        //printf("=========%s========Type:%d %d %s\n",path,st.type,de.inum,de.name);

        if(st.type==T_DIR){
            fun(path,target);
        }else{
            if(!strcmp(target,de.name)){
                printf("%s\n",path);
            }
        }
        *p='\0';
    }
    close(fd);
}

int main(int args, char* argvs[]){
    if(args!=3){
        printf("args error\n");
        exit(1);
    }
    fun(argvs[1],argvs[2]);
    exit(0);
}