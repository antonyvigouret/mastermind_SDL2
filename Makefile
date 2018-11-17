prog: master_SDL.o master.o
	gcc master_SDL.o master.o -o prog -lSDL2 
	
master_texte.o: master_SDL.c master.h
	gcc -c master_SDL.c 

master.o: master.c master.h
	gcc -c master.c

clean:
	rm *.o prog