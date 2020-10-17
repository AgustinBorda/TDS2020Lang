#!/bin/bash

./compile_compiler.sh > /dev/null 2>&1
cd ..
for file in examples/*
do
	clear
	echo ""
	echo ""
	echo ""
	echo "Nombre archivo: $file"
	cat "$file"
	echo "Output:"
	./ctds "$file"
	echo ""
	echo ""
	read -n1 -r -p "[ENTER]Siguiente ejemplo" key
done

