
CC=gcc
OBJS=recommend.o list.o sort.o ascrobbler.o

all: recommend 

clean:
	rm *.o *~ recommend 

%.o: %.c
	$(CC) -c $<

recommend: $(OBJS)
	$(CC) -g -o recommend $(OBJS)
