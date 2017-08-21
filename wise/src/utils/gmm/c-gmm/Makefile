CC       := gcc
CFLAGS   := -ansi -Wall -pedantic -g
LIB_NAME := c-gmm.a
OBJS     := alloc_util.o clust_invert.o clust_util.o subcluster.o

#CFLAGS = -g -ansi -Wall -pedantic -O -fPIC
#LIB_NAME := libc-gmm.so
#gcc -g -shared -o $@ $^

$(LIB_NAME): $(OBJS)
	ar -r $@ $^

clean:
	rm -f *.o $(LIB_NAME)
