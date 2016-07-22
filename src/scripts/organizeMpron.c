#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

int main(int argc,char **argv){

	FILE *orig;
	FILE *dest;
	orig = fopen("../../dicts/editedPronDict.txt","r+");
	//dest = fopen("../../dicts/editedPronDict.txt","w");
	
	char **arr = malloc(sizeof(char *)*64);
	int size = 0;
	int capacity = 64;

	char *inputLine = malloc(sizeof(char)*128);
	fgets(inputLine,128,orig);

	while(!feof(orig)){
		arr[size] = malloc(sizeof(char)*128);
		strcpy(arr[size],inputLine);
		size++;

		if(size == capacity){
			arr = realloc(arr,sizeof(char *)*(capacity*2));
			capacity*=2;
		}

		fgets(inputLine,128,orig);
	}
	int minIndex = 0;

	for(int i = 0; i<size ; i++){
		fprintf(stderr,"%i\n",i);
		minIndex = i;
		for(int j = i+1; j<size; j++){
			if(strcmp(arr[minIndex],arr[j]) > 0){ 
				minIndex = j;
			}
		}
		char *in = malloc(sizeof(char)*128);
		strcpy(in,arr[i]);
		strcpy(arr[i],arr[minIndex]);
		strcpy(arr[minIndex],in);
	}

	printCharArr(arr);

	fclose(orig);
	//fclose(dest);
	
	return(0);
}
