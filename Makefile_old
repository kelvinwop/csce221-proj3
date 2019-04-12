output.out: driver.o Library.o Song.o Tree.o TitleCompare.o AlbumCompare.o ArtistCompare.o GenreCompare.o YearCompare.o
	g++ -Wall -g -std=c++11 driver.o Library.o Song.o Tree.o TitleCompare.o AlbumCompare.o ArtistCompare.o GenreCompare.o YearCompare.o -o output.out

Library.o: Library.cpp Library.h
	g++ -Wall -g -std=c++11 -c Library.cpp

Song.o: Song.cpp Song.h
	g++ -Wall -g -std=c++11 -c Song.cpp

TitleCompare.o: TitleCompare.cpp TitleCompare.h
	g++ -Wall -g -std=c++11 -c TitleCompare.cpp

Tree.o: Tree.cpp Tree.h TreeIterator.cpp
	g++ -Wall -g -std=c++11 -c Tree.cpp

TreeIterator.o: TreeIterator.cpp TreeIterator.h
	g++ -Wall -g -std=c++11 -c TreeIterator.cpp

AlbumCompare.o: AlbumCompare.cpp AlbumCompare.h
	g++ -Wall -g -std=c++11 -c AlbumCompare.cpp

ArtistCompare.o: ArtistCompare.cpp ArtistCompare.h
	g++ -Wall -g -std=c++11 -c ArtistCompare.cpp

GenreCompare.o: GenreCompare.cpp GenreCompare.h
	g++ -Wall -g -std=c++11 -c GenreCompare.cpp

YearCompare.o: YearCompare.cpp YearCompare.h
	g++ -Wall -g -std=c++11 -c YearCompare.cpp

driver.o: driver.cpp Library.h Song.h TitleCompare.h Tree.h AlbumCompare.h ArtistCompare.h GenreCompare.h YearCompare.h
	g++ -Wall -g -std=c++11 -c driver.cpp

clean:
	rm -rf *.o
	rm -f *.out

run:
	./output.out ${LIBRARYFILE}