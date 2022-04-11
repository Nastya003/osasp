#!/bin/bash

#$Min=$1
#$Max=$2
#$DirName=$3

if [ $# -ne 3 ] 
   then {
	echo "Parameters: min max name of directory"
   } >&2
elif [ ! -d $3 ] 
   then {
	echo "$3 isn't a directory"
   } >&2
else {
	find $3 -type f -size +$1c -size -$2c -printf "%s\t%p\n"| sort -n 
     }
fi
