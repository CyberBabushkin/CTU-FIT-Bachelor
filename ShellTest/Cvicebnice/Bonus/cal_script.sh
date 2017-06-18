#!/bin/bash

A="$(cal 1 2010)"

echo "$A" | awk '{if (NR>1) {
  for (i==1;i<8;i++) {
    array[i]=array[i]+$i;
    if (i!=7) array[i]=array[i]+" ";    
  }
} 
else 
{print $0} 
}

END {
for (i==1;i<8;i++) {
  print array[i];
}
}'
