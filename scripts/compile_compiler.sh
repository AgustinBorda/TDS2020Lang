#!/bin/bash

mkdir ../src/bin > /dev/null 2>&1
cd ../src/bin
flex ../lexical_analyzer.l
bison -d ../syntax_analyzer.y
cd ../..
gcc -o ctds src/bin/lex.yy.c src/bin/syntax_analyzer.tab.c src/src/*.c
