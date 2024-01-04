#set noexpandtab

CC = gcc

CFLAGS = -O2 -lm -lSDL2 -lSDL2main 

all: attractor

attractor: attractor.o create_attractor.o predefined_attractors.o render_attractor.o matrix_math.o
	$(CC) $(CFLAGS) attractor.o create_attractor.o predefined_attractors.o render_attractor.o matrix_math.o -o attractor

attractor.o: attractor.c header.h
	$(CC) $(CFLAGS) -c attractor.c
	
create_attractor.o: create_attractor.c header.h
	$(CC) $(CFLAGS) -c create_attractor.c
	
predefined_attractors.o: predefined_attractors.c header.h
	$(CC) $(CFLAGS) -c predefined_attractors.c
		
render_attractor.o: render_attractor.c header.h
	$(CC) $(CFLAGS) -c render_attractor.c
	
matrix_math.o: matrix_math.c header.h
	$(CC) $(CFLAGS) -c matrix_math.c
	
clean:
	rm -f *.o attractor























