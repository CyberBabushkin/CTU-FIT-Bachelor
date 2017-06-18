cd ./tests

PROG="$1"

for IN_FILE in *_in.txt 
do
  MY_OUT="my_out.txt"
  OUT_FILE=`echo -n $IN_FILE | sed -e 's/in/out/'`
  "$PROG" < "$IN_FILE" > "$MY_OUT"
  diff "$MY_OUT" "$OUT_FILE"
  if ([ $? -eq 0 ]) then echo "OK: \"$IN_FILE\""; else echo "FAIL: \"$IN_FILE\""; fi
done
