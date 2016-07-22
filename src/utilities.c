#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "utilities.h"

char *makeParseable(char *s){

	char *result = malloc(sizeof(char)*256);
	strcat(result,"cd ../models/syntaxnet && echo \"");
	strcat(result,s);
	result[strlen(result)-1] = 0; // remove '\n'
	strcat(result,"\" | syntaxnet/demo.sh 2> /dev/null");
	return result;
}

char *toLower(char *str){

	char *result = malloc(sizeof(char)*256);

	for(int i = 0; str[i]; i++){
		  result[i] = tolower(str[i]);
	}
	return result;
}

char *getPOS(char *s){ //gets the POS data from Parsey McParseFace output in Penn Treebank format

	int len = strlen(s);
	char *result = malloc(sizeof(char)*256);
	char cToStr[2];
	cToStr[1] = '\0';

	for(int i =0;i<len;i++){
		if(isCorrectFormat(s[i])){
			cToStr[0] = s[i];
			strcat(result,cToStr);
			if(s[i] == ','){ //before being processed by this function, the output from syntaxnet
				i +=2;   //for commas is ",_,". If I don't do this, the resulting structure file
					// will read ",," for commas which is unsightly
			}
	}
		}
	
	return result;
}

int isCorrectFormat(char c){
	return(isupper(c) || c == ' ' || c == ',' || c == '?' || c == '$');
}

int getNumLines(char *fileName){
	
	FILE *fp;
	fp = fopen(fileName,"r");

	int ch, result = -1;
	int nonNewLinesInLine = 0;

	do
	{
		ch = fgetc(fp);
		if(ch != '\n'){
			nonNewLinesInLine++;}
		if(ch == '\n'){ //if line is empty except for newline, don't count it because it's not parsed
			if(nonNewLinesInLine > 0){
			result++;}
		nonNewLinesInLine = 0;	
		}
		
		}
	while(ch != EOF);
	
	if(ch != '\n' && result != 0){
		result ++; }

	fclose(fp);
	return result;
	}

char *cleanStr(char *s){ //removes punctuation, newlines etc. from given string and makes it lowercase
	
	char *result = malloc(sizeof(char)*256);
	char cToStr[2];
	cToStr[1] = '\0';

	for(int i = 0;i<strlen(s);i++){
		if(isalpha(s[i]) || s[i] == ' ' || s[i] == '\'' || s[i] == '-' || s[i] == '$'){
			cToStr[0] = s[i];
			strcat(result,cToStr);
		}
	}
	return result;
}

void removeSpaces(char *s){

	char *i = s;
	char *j = s;
	while(*j !=0)
	{
		*i = *j++;
		if(*i != ' '){
			i++;}
	}
	*i = 0;
}

void printCharArr(char **arr){

	int i = 0;

	while(arr[i] != 0){
		fprintf(stderr,"%s,",arr[i]);
		i++;
	}
	fprintf(stderr,"\n");
}


char **strToArr(char *s){ //turns a char* into a char** comprised of every token from input string
	
	char *temp = malloc(sizeof(char)*256);
	strcpy(temp,s);
	char *next = malloc(sizeof(char)*256);
	char **result = (char **) malloc(sizeof(char *)*64);
	int count = 0;

	next = strtok(temp," ");

	while(next != NULL){
		result[count] = malloc(sizeof(char)*256);
		strcpy(result[count],next);
		count++;
		next = strtok(NULL," ");
	}

	return result;
}

int isInFile(char *targ, char *filename){

	FILE *fp;
	
	//fprintf(stderr,"Checking file '%s' for string '%s...\n",filename,targ);

	fp = fopen(filename,"r");
	
	if(fp == NULL){
		//fprintf(stderr,"Creating new file '%s'...\n",filename);
		fp = fopen(filename,"w");
		fclose(fp);
		fp = fopen(filename,"r");
	}
	char *inputLine = malloc(sizeof(char)*256);

	while(fgets(inputLine,512,fp) != NULL){
		//fprintf(stderr,"Comparing target '%s' to file entry '%s'...\n",targ,inputLine);
		if(strcmp(cleanStr(inputLine),targ) == 0){
			//fprintf(stderr,"Match!\n");
			return 1;
		}
	}

	fclose(fp);
	//fprintf(stderr,"No match found.\n");
	return 0;
}

char *removeUnderscores(char *str){ //I bet you can't guess what this function does
	
	char *result = malloc(sizeof(char)*256);
	char cToStr[2];
        cToStr[1] = '\0';	
	int i = 0;

	while(str[i] != 0){
		if(str[i] != '_'){
			cToStr[0] = str[i];
		}
		else{
			cToStr[0] = ' ';
		}
		strcat(result,cToStr);
		i++;
	}

	return result;
}

int isAlnum(char *str){ //returns true if string is alphanumeric, false otherwise

	int i = 0;

	while(str[i] != 0){
		if(!isalnum(str[i])){
			return 0;
		}
		i++;
	}
	return 1;
}


