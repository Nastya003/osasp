#!/bin/bash

if [ $# -ne 2 ]
   then {
	echo "First parameter: name of source file"
	echo "Second parameter: name of exe file"
   } >&2
   elif [ ! -f $1 ]
   then echo "$2  isn't a file" >&2 
   else {
	gcc $1 -o $2 && ./$2
	}
fi
