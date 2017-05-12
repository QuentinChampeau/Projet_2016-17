FLAGMATH=-lpthread -lm
CCFLAGS = -std=gnu99 -O2

all:
	gcc -g $(CCFLAGS) avion.c -o avion.out $(FLAGMATH)
	gcc -g $(CCFLAGS) SGCA.c -o SGCA.out $(FLAGMATH)

clean:
	rm -f *.out *.o