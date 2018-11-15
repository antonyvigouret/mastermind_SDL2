prog: master_texte.o master.o
	gcc master_texte.o master.o -o prog -I ../../include -L ../../lib -lmingw32 -lSDL2main -lSDL2 -g -Wall -Wextra

master_texte.o: master_texte.c
	gcc -c master_texte.c 

master.o: master.c master.h
	gcc -c master.c

clean:
	rm *.o prog