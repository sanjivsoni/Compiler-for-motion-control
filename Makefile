parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexicalAnalyser.l parser.tab.h
	flex lexicalAnalyser.l

motionController: lex.yy.c parser.tab.c parser.tab.h
	g++ parser.tab.c lex.yy.c -ll -w -o motionController