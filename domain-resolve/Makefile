CC = gcc
LIBS = -lcares
objects = main6.o
target = main6

all: $(objects)
	$(CC) -o $(target) $^ $(LIBS)
 
$(objects): %.o: %.c
	$(CC) -c $^ -o $@ $(LIBS)

clean:
	-rm -f *.o

