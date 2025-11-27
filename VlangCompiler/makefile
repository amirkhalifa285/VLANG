# Makefile for Vlang Compiler on Windows (C++ version)
LEX     = flex
YACC    = bison
CXX     = g++
CXXFLAGS = -Wall -std=c++11

all: vlang.exe

vlang.exe: parser.tab.c lex.yy.c
	$(CXX) $(CXXFLAGS) -o $@ $^

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d $<

lex.yy.c: lexer.l
	$(LEX) $<

# 1) הפעלת המהדר -> output.cpp
generate: vlang.exe example.vlang
	vlang.exe < example.vlang
	@echo "✓ generated output.cpp"

# 2) קומפילציית C++ -> program.exe (שימו לב ל‑runtime.cpp)
compile-cpp: generate runtime.cpp
	$(CXX) $(CXXFLAGS) -o program.exe output.cpp runtime.cpp
	@echo "✓ compiled program.exe"

# 3) הרצה
run-cpp: compile-cpp
	program.exe

# שרשור נוח
test: run-cpp
clean:
	cmd /C "del /Q lex.yy.c parser.tab.c parser.tab.h vlang.exe output.cpp program.exe 2>nul || exit 0"
