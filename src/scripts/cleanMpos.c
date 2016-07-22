#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Removes all instances of 'Noun Phrase' entries in mpos dictionary.

int main(int argc,char **argv){

	FILE *orig;
	FILE *dest;
	orig = fopen("../../dicts/mpos/mobyposi.i","r+");
	dest = fopen("../../dicts/posDict.txt","w");

	char *inputLine = malloc(sizeof(char)*512);
	fgets(inputLine,512,orig);

	while(!feof(orig)){
		char *temp = malloc(sizeof(char)*512);
		strcpy(temp,inputLine);
		char id = temp[strlen(temp)-2];
		if(id != 'h') { //if given entry's POS is not 'h' 
			fputs(temp,dest);
		}
		fgets(inputLine,512,orig);
	}
	
	fclose(orig);
	fclose(dest);

}
