#!/bin/bash

let numOfLines="$(cat file.in | wc -l)"

cat file.in | \
  awk -v numL=$numOfLines 'BEGIN{sum=0} { if (NR<numL-1) {sum+=$NF;}
if (NR==numL) {if ($NF!=sum) {print "WTF? " sum " != " $NF} else 
{print "Great!"} } }'
