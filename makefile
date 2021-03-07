OBJS	  = driver-class.o encode-string.o main.o print-values.o lex.yy.o parser.tab.o ast-symbol-table.o ast-tree-class.o scanner-token.o abstract-syntax-tree.o ast-node-classes.o
SOURCE	= driver-class.cpp encode-string.cpp main.cpp print-values.cpp lex.yy.cc parser.tab.cc ast-symbol-table.cpp ast-tree-class.cpp scanner-token.cpp abstract-syntax-tree.cpp
HEADER	= parser.tab.hh driver-class.hpp encode-string.hpp print-values.hpp scanner-token.hpp token-scanner-class.hpp location.hh stack.hh position.hh  
BISONFILES = location.hh position.hh lex.yy.cc stack.hh parser.tab.hh parser.tab.cc
OUT	    = c-
CC	    = g++
FLAGS	  = -g -c -Wall 
LFLAGS	=  

all: bison lexer $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
bison: parser.y
	bison parser.y -d -L c++ -t -v
lexer: scanner.flex
	flex $<
driver-class.o: driver-class.cpp
	$(CC) $(FLAGS) driver-class.cpp -std=c++14

encode-string.o: encode-string.cpp
	$(CC) $(FLAGS) encode-string.cpp -std=c++14

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14

print-values.o: print-values.cpp
	$(CC) $(FLAGS) print-values.cpp -std=c++14

lex.yy.o: lex.yy.cc
	$(CC) $(FLAGS) lex.yy.cc -std=c++14

parser.tab.o: parser.tab.cc
	$(CC) $(FLAGS) parser.tab.cc -std=c++14

ast-symbol-table.o: ast-symbol-table.cpp
	$(CC) $(FLAGS) ast-symbol-table.cpp -std=c++14

ast-tree-class.o: ast-tree-class.cpp
	$(CC) $(FLAGS) ast-tree-class.cpp -std=c++14
abstract-syntax-tree.o: abstract-syntax-tree.cpp
	$(CC) $(FLAGS) abstract-syntax-tree.cpp -std=c++14
ast-node-classes.o: ast-node-classes.cpp
	$(CC) $(FLAGS) ast-node-classes.cpp -std=c++14
scanner-token.o: scanner-token.cpp
	$(CC) $(FLAGS) scanner-token.cpp -std=c++14

clean:
	rm -f $(OBJS) $(BISONFILES) $(OUT)