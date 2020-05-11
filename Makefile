main:main.o compressor.o decompressor.o recorder.o visualization.o
	gcc main.o compressor.o decompressor.o recorder.o visualization.o
main.o:main.c
	gcc -c main.c
compressor.o:compressor.c compressor.h
	gcc -c compressor.c
decompressor.0:decompressor.c decompressor.h
	gcc -c decompressor.c
recorder.o:recorder.c recorder.h
	gcc -c recorder.c
visualization.o:visualization.c visualization.h
	gcc -c visualization.c
clean:
	-rm -rf *.o
	-rm -rf *.xls
	-rm -rf *txt

