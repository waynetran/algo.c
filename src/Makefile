CC = gcc
PWD = $(shell pwd)
CFLAGS = -g -c -Wall -std=c99 -I../lib/libds -I/usr/local/include -I$(PWD) -I$(PWD)/list
LDFLAGS= ../lib/libds/libds.a -lm -llog.c

OBJS = graph/node.o graph/edge.o graph/graph.o list/listnode.o list/list.o
SOURCES = $(OBJS:.o=.c)
HEADERS = $(OBJS:.o=.h)

TESTOBJS = main.o graph/node_test.o graph/graph_test.o list/list_test.o
TESTSOURCES = $(TESTOBJS:.o=.c)
TESTHEADERS = $(TESTSOBJS:.o=.h)

OUT = libalgo.c.a

RM = rm -f
MKDIR = mkdir -p

all: $(OUT) test

$(OUT): $(OBJS)
	ar rcs $@ $(OBJS)
	cp $(OUT) ../lib

test: $(OUT) $(TESTOBJS)
	$(CC) -o $@ $(TESTOBJS) $(OUT) $(LDFLAGS)
	mv test ../test

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) $(TESTOBJS) *~ "#*" test *.log

distclean: clean
	$(RM) $(OUT)

.PHONY: all clean
