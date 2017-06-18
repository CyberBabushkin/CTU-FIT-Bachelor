#!/bin/bash

counter=0

for i in $(cat s1); 
do
  mkdir "$i" 2>/dev/null
  if ([ $? != 0 ]) 
  then
    let counter=$counter+1
  fi
done


echo $counter
