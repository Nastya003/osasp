#!/bin/bash
FileName=$1
DirName=$2
FileTipe=$3

if [ $# -ne 3 ]
   then {
	echo "First parameter: name of output file"
	echo "Second parameter: name of directory"
	echo "Third parameter: extantion of file"
   } >&2
   elif [ ! -d $DirName ]
   then echo "$2  isn't a directory" >&2 
   else {
   find $DirName -type f -name "*.$FileTipe" | sort -o $FileName
	echo "ok"
   }
fi
