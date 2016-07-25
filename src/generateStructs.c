#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc,char **argv){ //runs the makeStruct script on every file in madlyrics/corpora if there is no 
				//corresponding struct file in madlyrics/structs

	DIR           *d;
	struct dirent *dir;
	FILE *fp;
	char * path = malloc(sizeof(char)*512);	
	char *filename = malloc(sizeof(char)*512);
	
	if((d = opendir("corpora")) != NULL) {

		while((dir = readdir(d)) != NULL) {

			if(dir->d_name[0] != '.'){
				strcpy(path,"./makeStruct corpora/");
				strcpy(filename,"structs/");
				strcat(filename,dir->d_name);
				fp = fopen(filename,"r");
				if(fp == NULL){ // if struct file hasn't been generated yet
					strcat(path,dir->d_name);
					system(path);
				}
			
				else{
				fprintf(stderr,"Struct file '%s' already exists.\n",dir->d_name);
				}
			}
		}
		closedir(d);
	}
	else{
		perror("");
		return EXIT_FAILURE;
	}

	return 0;
}


