#ifndef LYRICS_UTIL
#define LYRICS_UTIL

char *makeParseable(char *s);
char *toLower(char *s);
char *getPOS(char *s);
int isCorrectFormat(char c);
int getNumLines(char *fileName);
void strToArr(char *s, char **dest);
char *cleanStr(char *s);
void removeSpaces(char *s);
void printCharArr(char **arr);
int secondTokenStrcmp(char *a,char *b);
int isInFile(char *targ, char *filename);
char *removeUnderscores(char *str);
int isAlnum(char *str);
int isInCharArr(char **arr,char *str);
char *getWordFromDictEntry(char *str);
char *getRhymeIdFromDictEntry(char *str);
char *toUpper(char *s);
char *getWordFromTaggedString(char *str);
int isNumber(char *str);
char *arrToStr(char **arr);
char *getPosFromTaggedString(char *str);
void removeNewlines(char *s);

#endif
