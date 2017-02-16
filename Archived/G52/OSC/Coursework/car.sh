#!/bin/bash

base=$1
cFile=$base".c"
runFile=$base".run"
textFile=$base".txt"

#rm "$textFile"
#touch "$textFile"

gcc -pthread "$cFile" -o "$runFile"

./"$runFile" #>> "$textFile"

#less "$textFile"
