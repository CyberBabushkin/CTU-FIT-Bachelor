#/!bin/bash

local_dir="$(cat config | grep "local_dir=" | sed -E 's/local_dir=(.*)/\1/')"

echo "$local_dir"
