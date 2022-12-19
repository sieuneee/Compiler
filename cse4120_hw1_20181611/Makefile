CC = gcc

CFLAGS = 

OBJS = main.o util.o lex.yy.o

TARGET = hw1_binary

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $(OBJS) -ll

main.o: main.c globals.h util.h scan.h parse.h analyze.h cgen.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

lex.yy.c: lex/tiny.l
	flex lex/tiny.l

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	-rm $(TARGET)
	-rm $(OBJS)
	-rm lex.yy.c

