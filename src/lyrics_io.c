#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "structure.h"
#include "utilities.h"
#include "lyrics_io.h"

//Contains functions pertaining to file i/o


void readLinesToStructure(structure *s, char *filename, int numLines){ //reads untagged lines from file into structure object

	FILE *fp;

	numLines = getNumLines(filename);

	fp = fopen(filename,"r");
	fprintf(stderr,"Now parsing '%s'\n",filename);

	char *inputLine = malloc(sizeof(char)*256);

	while(fgets(inputLine,512,fp) != NULL){
		char *temp = malloc(sizeof(char)*512);
		strcpy(temp,inputLine);
		addLine(s,newLine(temp));
	}

	fclose(fp);
}

void parseLines(structure *s, char *filename, int numLines){ //tags untagged lines in structure object by feeding them into Parsey McParseFace

	FILE *fp;
	char *inputLine = malloc(sizeof(char)*512);
	int currLine = 1;

	for(int i = 0;i<s->lineCount;i++){
		if(s->lines[i]->words[0] != '\n'){
			char *parsed = makeParseable(toLower(s->lines[i]->words));
			fprintf(stderr,"Parsing line %d of %d...\n",currLine,numLines);
			currLine++;
			
			system(parsed);

			fp = fopen("tmp/output.txt","r"); //if you change the location or name in this file, make sure to also change the corresponding
			char *temp = malloc(sizeof(char)*512); //entry in models/syntaxnet/syntaxnet/models/parsey_mcparseface/context.pbtxt
			fgets(inputLine,512,fp);
			strcpy(temp,inputLine);

			s->lines[i]->pos = temp;
			fclose(fp);
		}
	}
}

void writeStructToFile(structure *s, char *filename, int numLines, char ***words, char ***rhymes){ //writes structure to .txt file in madlyrics/structs/

	char *path = malloc(sizeof(char)*128);
	strcpy(path,"structs/");
	filename += 8; //removes first 8 chars from filename, which is always "corpora/"
	strcat(path,filename);

	FILE *outputFile = fopen(path,"w");

	char *temp = malloc(sizeof(char)*128);

	char *str = malloc(sizeof(char)*128); //holds data for each word that will be printed to outfile
	int i = 0;
	
	while(s->lines[i] != NULL){

		char **curr = malloc(sizeof(char *)*64);
		strToArr(s->lines[i]->pos,curr);
		strcpy(str,"");

		int j = 0;
		while(curr[j] != NULL){
			removeNewlines(curr[j]);
			
			if(!ispunct(getPosFromTaggedString(curr[j])[0])){

			sprintf(temp,"%s_%d_%s ",getPosFromTaggedString(curr[j]),
						isInCharArr(*words,getWordFromTaggedString(curr[j])),
						(*rhymes)[isInCharArr(*words,getWordFromTaggedString(curr[j]))]
						); // format: POS_WORDID_RHYMEID
			strcat(str,temp);
			}
			else{
				strcat(str,(curr[j]));
				strcat(str," ");
			}
			
			j++;
		}
		removeNewlines(str);
			
		fprintf(outputFile,"%s\n",str);

		i++;
	}	

	

	fprintf(stderr,"Saved structure to structs/%s.\n",filename);
	fclose(outputFile);
}

void updatePosLists(structure *s){ //checks if each word/POS combination is present in POS lists found in madlyrics/lists, updates corresponding list
				   // if not present.

	char *path = malloc(sizeof(char)*128);
	char **wordsArr = malloc(sizeof(char *)*64);
	char *word = malloc(sizeof(char )*256);

	FILE *dest;
	int i = 0;
	int newEntries = 0;

	while(s->lines[i] != NULL){
		
		strToArr(removeUnderscores(s->lines[i]->pos),wordsArr); // evenly sized array with format (word) (pos)
		int l = 0;
		
		while(wordsArr[l] != NULL){
			strcpy(word,wordsArr[l]);
			if(isAlnum(word)){
				strcpy(path,"lists/");
				strcat(path,cleanStr(wordsArr[l+1]));
				strcat(path,".txt");
				if(!isInFile(word,path)){
					dest = fopen(path,"a");
					fprintf(dest,"%s\n",word);
					fclose(dest);
					newEntries++;
				}
			}
			l+=2;
		}
		i++;
	}

	if(newEntries > 0){
		fprintf(stderr,"Updated POS Lists with %i new terms.\n",newEntries);
	}
	else{
		fprintf(stderr,"No new terms were added to POS lists.\n");
	}
}

void findRhymeScheme(structure *s, char *filename,int numLines){
	
	char **currentLine = malloc(sizeof(char *)*256);
	char **wordsArr = malloc(sizeof(char *)*256);

	int size = 0;
	int capacity = 256;

	int i = 0;

	while(s-> lines[i] != NULL){

		strToArr(removeUnderscores(s->lines[i]->pos),currentLine);
		
		int j = 0;

		while(currentLine[j] != NULL){
			if(isInCharArr(wordsArr,currentLine[j]) == -1 && !ispunct(currentLine[j][strlen(currentLine[j])-1])){
				wordsArr[size] = malloc(sizeof(char)*256);
				strcpy(wordsArr[size],currentLine[j]);
				size++;
			}
			if(size == capacity){
				wordsArr = realloc(wordsArr,sizeof(char *)*(capacity *2));
				capacity *= 2;
			}
			
			j += 2;
		}
		i++;
	}
	
	
	char **rhymeArr = malloc(sizeof(char *) * 256);
	char *curr = malloc(sizeof(char)*256);

	int k = 0;

	while(wordsArr[k] != NULL){
		rhymeArr[k] = malloc(sizeof(char)*256);
		strcpy(curr,getRhymeId(wordsArr[k]));
		
		if(strcmp(curr,"?") == 0 || isInCharArr(rhymeArr,curr) == -1 ){
			strcpy(rhymeArr[k],curr);
		}
		else{
			sprintf(curr, "%d", isInCharArr(rhymeArr,curr));
			strcpy(rhymeArr[k],curr);
		}
		removeSpaces(wordsArr[k]);	
		k++;
	}
	
	int z = 0;
	while(rhymeArr[z] != NULL){

		if(!isNumber(rhymeArr[z])){
			sprintf(rhymeArr[z],"%d",z); //if it's the first occurence of a rhyme, replace rhyme ID with index
		}
		removeSpaces(rhymeArr[z]);
		z++;
	}
	
	
	writeStructToFile(s,filename,numLines,&wordsArr,&rhymeArr);	


	
}
	


char *getRhymeId(char *str){ //gets rhyme ID from madlyrics/dicts/editedRhymeDict.csv that corresponds to given word

	FILE *fp = fopen("dicts/editedRhymeDict.csv","r");

	char **results = malloc(sizeof(char *)*32);
	int size = 0;
	char *temp = malloc(sizeof(char)*256);
	char *curr = malloc(sizeof(char)*256);

	while(fgets(temp, 128,fp) != NULL){
		if(strstr(temp,toUpper(str)) != NULL){ // if match is found
			strcpy(curr,getWordFromDictEntry(temp));
			if(strcmp(toUpper(str),curr) == 0){ //if word entry matches str exactly
				results[size] = malloc(sizeof(char)*256);
				strcpy(results[size],getRhymeIdFromDictEntry(temp));
				size++;
			}
		}
	}

	fclose(fp);
	
	//printCharArr(results);
	if(results[0] != NULL){
		return results[rand() % (sizeof(results) / sizeof(results[0]))]; //returns random entry in array
	}
	else{
		return "?";
	}

}	

int structExists(char *filename){

	char *temp = malloc(sizeof(char)*128);
	char *path = malloc(sizeof(char)*128);
	strcpy(temp,filename);
	strcpy(path,"structs/");
	temp+= 8; // removes first 8 characters, which is always 'corpora/'
	strcat(path,temp);
	fprintf(stderr,"%s\n",path);	
	FILE *fp = fopen(path,"r");

	if(fp == NULL){
		return 0;
	}
	else{
		return 1;
	}



//char *getRandomWordFromList(char *list){

//}




}
