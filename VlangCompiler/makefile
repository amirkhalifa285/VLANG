CC = gcc
CFLAGS = -w
TARGET = vlangc.exe

ifeq ($(OS),Windows_NT)
    RM = del /f
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

$(TARGET): y.tab.o lex.yy.o symTab.o
	$(CC) $(CFLAGS) -o $(TARGET) y.tab.o lex.yy.o symTab.o

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

symTab.o: symTab.c
	$(CC) $(CFLAGS) -c symTab.c

y.tab.c: vlang.y
	bison -y -d vlang.y

lex.yy.c: vlang.l
	flex vlang.l

clean:
	$(RM) vlangc$(EXE) *.o y.tab.c y.tab.h lex.yy.c

.PHONY: clean