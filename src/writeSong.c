#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utilities.h"
#include "lyrics_io.h"

int main(int argc,char **argv){ //Given a struct file, writes a new song based on the POS, Word, and Rhyme data contained within by referencing the
				//POS lists in madlyrics/lists.


	FILE *fp = fopen(argv[1],"r");

	char **words = malloc(sizeof(char *) *256); //todo: make dynamic
	char **rhymes = malloc(sizeof(char *) *256);
	char *inputLine = malloc(sizeof(char)*512);

	while(fgets(inputLine,512,fp) != NULL){

		char **currentLine = malloc(sizeof(char *) *256);
		strToArr(inputLine,currentLine);

		int i = 0;

		while(currentLine[i] != NULL){

			char *entry[3]; //holds data from current word in POS_WORDID_RHYMEID
			strToArr(removeUnderscores(currentLine[i]),entry);

			if(words[atoi(entry[1])] == NULL) { //if word hasn't been logged yet
				words[atoi(entry[1])] = malloc(sizeof(char)*256);
				words[atoi(entry[1])] = getRandomWordFromList(entry[0]);
