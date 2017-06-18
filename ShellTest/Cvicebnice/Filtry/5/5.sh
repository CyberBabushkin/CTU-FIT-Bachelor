#!/bin/bash

cat /etc/passwd | awk -F':' '{ if (!/^#/) { print $7 } }' | sort | uniq | wc -l 
