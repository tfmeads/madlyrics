#ifndef LINE_H
#define LINE_H
typedef struct lineObj
	{

		char *words; //holds words in line in order
		int wordCount; // word count
		char *pos; // parts of speech for each word, corresponding to words in 'words'


	} line;

extern line *newLine(char *s);

#endif
