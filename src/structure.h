#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "line.h"

typedef struct structureObj
	{

		line **lines; //array of Line objects
		int lineCount;
		int lineCapacity;
	
	} structure;

extern structure *newStructure();
extern void addLine(structure *,line *);
#endif
