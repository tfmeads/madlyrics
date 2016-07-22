#ifndef LYRICS_IO
#define LYRICS_IO

void readLinesToStructure(structure *s, char *filename, int numLines);
void parseLines(structure *s, char *filename, int numLines);
void writeStructToFile(structure *s, char *filename, int numLines);

#endif
