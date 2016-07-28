#ifndef LYRICS_IO
#define LYRICS_IO

void readLinesToStructure(structure *s, char *filename, int numLines);
void parseLines(structure *s, char *filename, int numLines);
void writeStructToFile(structure *s, char *filename, int numLines,char ***words,char ***rhymes);
int updatePosLists(structure *s);
void findRhymeScheme(structure *s,char *filename,int numLines);
char *getRhymeId(char *str);
int structExists(char *filename);

#endif
