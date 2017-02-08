CC= gcc
CCFLAGS= 
all:	exec 
	
arbres.o:	arbres.c 	arbres.h
	$(CC) $(CCFLAGS) -c arbres.c
fichier.o:	fichier.c 	fichier.h 	arbres.h
	$(CC) $(CCFLAGS) -c fichier.c

codage.o:	codage.c 	codage.h 	fichier.h 	arbres.h
	$(CC) $(CCFLAGS) -c codage.c
main.o: 	main.c	codage.h 	fichier.h 	arbres.h
	$(CC) $(CCFLAGS) -c main.c
exec: main.o arbres.o fichier.o codage.o
	$(CC) $(CCFLAGS) -o projet main.o arbres.o fichier.o codage.o 
clean:
	rm *.o
