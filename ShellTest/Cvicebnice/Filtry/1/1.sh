for i in $(cat /etc/passwd | awk 'BEGIN {FS=":"} { if (!/^ *$/) {print $7}}' | sort | uniq);
do
  ls -l "$i" | awk '{ print $5 " " $9 }'
done
