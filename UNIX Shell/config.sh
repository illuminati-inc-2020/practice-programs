#! /bin/bash

echo "* Currently logged user is `who am i|cut -d ' ' -f1` and logname is `logname`"

echo -e "\n* Your shell is `tty`"

echo -e "\n* Your home directory : "
ls

echo -e "\n* Your operarting system type is `uname -o`"

echo -e "\n* Your current path setting is $PATH"

echo -e "\n* Your current working directory is `pwd`"

echo -e "\n* Currently logged number of users is `who|wc -l`"

echo -e "\n* About os : "
uname -a

echo -e "\n* Available shells : "
cat /etc/shells

echo -e "\n* Mouse settings : "

echo -e "\n* Computer cpu information : "
cat /proc/cpuinfo

echo -e "\n* Memory information : "
cat /proc/meminfo

echo -e "\n* Hard disk information : "

echo -e "\n* File System mounted : "
df -h
