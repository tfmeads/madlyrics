#ifndef LYRICS_UTIL
#define LYRICS_UTIL

char *makeParseable(char *s);
char *toLower(char *s);
char *getPOS(char *s);
int isCorrectFormat(char c);
int getNumLines(char *fileName);
char **strToArr(char *s);
char *cleanStr(char *s);
void removeSpaces(char *s);
void printCharArr(char **arr);
int secondTokenStrcmp(char *a,char *b);
int isInFile(char *targ, char *filename);
char *removeUnderscores(char *str);
int isAlnum(char *str);

#endif
