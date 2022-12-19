CC = gcc

CFLAGS = 

OBJS = main.o util.o lex.yy.o tiny.tab.o

TARGET = hw2_binary

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $(OBJS) -ll

main.o: main.c globals.h util.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

tiny.tab.o: tiny.tab.c tiny.tab.h
	$(CC) $(CFLAGS) -c tiny.tab.c

tiny.tab.c tiny.tab.h : yacc/tiny.y
	bison -d yacc/tiny.y

lex.yy.c: lex/tiny.l
	flex lex/tiny.l

lex.yy.o: lex.yy.c util.h globals.h
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	-rm $(TARGET)
	-rm $(OBJS)
	-rm lex.yy.c
	-rm tiny.tab.c
