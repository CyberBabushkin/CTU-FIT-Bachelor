counter=0
counter1=0
text="void tiny (TDOCUMENT * doc) { doc = DocFormat( 1000000, 10000, \""

while ([ $counter -lt 100 ])
do
  let counter=$counter+1
  counter1=0
  while ([ $counter1 -lt 90 ])
  do
    let counter1=$counter1+1
    text="$text""a"
  done
  text="$text"" \n"
done

text="$text""\" ); }\n"
#printf "void tiny (TDOCUMENT * doc) { doc = DocFormat( 1000000, 10000, \"\" ); }"
printf "$text" > in\(small\).h
