#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

int main(int argc,char **argv){

	FILE *orig;
	FILE *dest;
	orig = fopen("../../dicts/rhymeDict.csv","r+");
	dest = fopen("../../dicts/editedRhymeDict.csv","w");

	char *inputLine = malloc(sizeof(char)*512);
	char *last = malloc(sizeof(char)*512);
	
	fgets(last,512,orig);

	while(fgets(inputLine,512,orig)!= NULL){
		
		if(strcmp(inputLine,last) != 0){
			fputs(last,dest);	
		}
		strcpy(last,inputLine);
	}
	
	fclose(orig);
	fclose(dest);

}
