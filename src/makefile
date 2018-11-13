CC = gcc
CFLAGS = -Wall -g
EXEC = PLAY

Lancement : $(EXEC) clean


dispFunc.o : dispFunc.c dispFunc.h headers.h matrix.h
			$(CC) -c $(CFLAGS) dispFunc.c 

matrix.o : matrix.c matrix.h tank.h
			$(CC) -c $(CFLAGS) matrix.c

list.o : list.c list.h tank.h
			$(CC) -c $(CFLAGS) list.c

tank.o : tank.c tank.h headers.h dispFunc.h
			$(CC) -c $(CFLAGS) tank.c

main.o : main.c headers.h dispFunc.h tank.h 
		$(CC) -c $(CFLAGS) main.c 

$(EXEC) : dispFunc.o matrix.o list.o tank.o main.o 
		 $(CC) -o $@ $^ -lm

Execution : 
		./$(EXEC)

clean : 
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
