#include<stdio.h>
#include<dirent.h>

int main(){
    DIR *dir = NULL;
    struct dirent* entry;
    if((dir = opendir("/home/wd/project")) == NULL){
        printf("opendir file！ \n");
        return 1;
    }else{
        while(entry = readdir(dir))
            printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}