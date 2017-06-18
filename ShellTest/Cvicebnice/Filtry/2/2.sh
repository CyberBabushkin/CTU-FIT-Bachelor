#!/bin/bash

let counter=1

for i in $(cat ./s1);
do
  A="$A$i "
  Z="$(cat ./s2 | head -$counter | tail -1)"
  A="$A$Z "
  Z="$(cat ./s3 | head -$counter | tail -1)"
  A="$A$Z"
  A="$A""\n"
  let counter=$counter+1
done

printf "$A" | sort -t' ' -k3,3
