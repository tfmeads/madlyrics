makestructs:
	gcc src/makeStruct.c src/line.c src/structure.c src/utilities.c -o makeStruct -Wall

tstructs:
	./makeStruct corpora/test.txt

gen: 
	gcc src/generateStructs.c -o genStructs -Wall

genstructs:
	./genStructs

