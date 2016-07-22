makestructs:
	gcc src/makeStruct.c src/line.c src/structure.c src/lyrics_io.c src/utilities.c -o makeStruct -Wall

tstructs:
	./makeStruct corpora/test.txt

gen: 
	gcc src/generateStructs.c -o genStructs -Wall

genstructs:
	./genStructs

cleanstructs:
	cd structs && rm * && cd ../

cleanlists:
	cd lists && rm * && cd ../

clean:
	make cleanstructs && make cleanlists
