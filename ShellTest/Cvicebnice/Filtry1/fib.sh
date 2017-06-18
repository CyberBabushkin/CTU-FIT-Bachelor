if [ $LIMIT -lt 1 ]; then exit 1; fi

echo 1
echo 1

let A=1
let B=1

while ([ $(($A+$B)) -le $LIMIT ]) 
do
echo $(($A+$B))
let tmp=$A
let A=$B
let B=$(($tmp+$B))
done
