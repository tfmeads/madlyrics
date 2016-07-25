#ifndef LYRICS_IO
#define LYRICS_IO

void readLinesToStructure(structure *s, char *filename, int numLines);
void parseLines(structure *s, char *filename, int numLines);
void writeStructToFile(structure *s, char *filename, int numLines);
void updatePosLists(structure *s);
void findRhymeScheme(structure *s,char *filename);
char *getRhymeId(char *str);

#endif
