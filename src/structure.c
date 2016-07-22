#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "line.h"

structure *newStructure(){

	structure *s = (structure *) malloc(sizeof(structure));
	s->lines = (line **) malloc(sizeof(line *));
	s->lineCount = 0;
	s->lineCapacity = 1;

	return s;
}

void addLine(structure *s, line *l){
	
	int limit = s->lineCount;

	for(int i = 0;i <= limit; i++){
		
		if(i == s->lineCount){
			s->lines[i] = (line *) malloc(sizeof(line));
			s->lines[i] = l;
			s->lineCount++;
			if(s->lineCount == s->lineCapacity){
				s->lineCapacity*=2;
				s->lines = (line **) realloc(s->lines,sizeof(line*)*s->lineCapacity);
			}
		}
	}
}

