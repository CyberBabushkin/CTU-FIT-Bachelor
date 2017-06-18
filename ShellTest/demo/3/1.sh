#!/bin/bash

ip_piece="([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])"

ip_address=" $ip_piece\.$ip_piece\.$ip_piece\.$ip_piece( |\])"

#cat apache.log | awk -v ip_address="$ip_address" \
#' {if  (/\[error\]/) 
# print $13 
# else if (ip_address) 
# print $6
#}' | sed 's/\]//g' | sort | uniq -c | awk '{if(NR==1){max=$1}} {if($1>=max){print $2}}' |\
#sort -t'.' -n -k1,1 -k2,2 -k3,3 -k4,4

cat apache.log | grep -Eo "$ip_address" | sed 's/ //g' | sed 's/\]//g' |\
sort | uniq -c | sed 's/^ ?//g' | sort -rn -k1,1 | \
 awk '{if(NR==1){max=$1}} {if($1>=max){print $2}}' |\
sort -t'.' -n -k1,1 -k2,2 -k3,3 -k4,4
