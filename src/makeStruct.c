#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utilities.h"
#include "lyrics_io.h"

int main(int argc,char **argv){ //Takes a .txt file of a song, feeds it into Parsey McParseFace, takes POS-tagged
				//text and creates a file outlining the song's structure and updates the POS lists
				//found in madlyrics/lists directory
				//WARNING: Do not run directly unless for testing purposes. Use the genStructs script.
	
	structure *s = newStructure();

	int numLines = getNumLines(argv[1]);

	readLinesToStructure(s,argv[1],numLines);

	parseLines(s,argv[1],numLines);
	
	findRhymeScheme(s,argv[1],numLines);

	int newEntries = updatePosLists(s);
	
	if(newEntries == 0){
		fprintf(stderr,"No new entries were added to POS lists.\n");
	}
	else{
		fprintf(stderr,"%i new entries were added to POS lists.\n",newEntries);
	}

	return 0; 
}

