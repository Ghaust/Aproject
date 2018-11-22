CC = gcc
CFLAGS = -Wall -g
EXEC = PLAY

Lancement : $(EXEC) clean


dispFunc.o : dispFunc.c dispFunc.h list.h matrix.h tank.h
			$(CC) -c $(CFLAGS) dispFunc.c 

matrix.o : matrix.c matrix.h list.h
			$(CC) -c $(CFLAGS) matrix.c

list.o : list.c list.h tank.h
			$(CC) -c $(CFLAGS) list.c

tank.o : tank.c tank.h obus.h
			$(CC) -c $(CFLAGS) tank.c

obus.o : obus.c obus.h dispFunc.h
			$(CC) -c $(CFLAGS) obus.c

main.o : main.c headers.h obus.h tank.h 
		$(CC) -c $(CFLAGS) main.c 

$(EXEC) : dispFunc.o matrix.o obus.o list.o tank.o main.o 
		 $(CC) -o $@ $^ -lm

Execution : 
		./$(EXEC)

clean : 
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
