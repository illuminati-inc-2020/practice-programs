# Assignment no. : 1
# Aim            : Write a shell script that have the capability in changing the extensions of group of files (e.g. from .TXT to .DOC extension). Source and terget extensions should passed as arguments.

#! /bin/bash

if [ $# -ne 2 ] ; then
	echo "Error : Argument missing";
	echo "Format : change_extension [source_extension] [target_extension]";
else
	for oldname in `ls *.$1`
	do
		newname=${oldname%%.$1}".$2"
		mv $oldname $newname;
	done
fi