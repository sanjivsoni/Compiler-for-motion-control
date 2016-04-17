parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexicalAnalyser.l parser.tab.h
	flex lexicalAnalyser.l

motionController: lex.yy.c parser.tab.c parser.tab.h maze.cpp
	g++ parser.tab.c lex.yy.c -w -ll -o motionController
