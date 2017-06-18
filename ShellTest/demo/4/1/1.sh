#!/bin/bash

let A="$(ps -eo ruid | tail -n +2 | sort -n | uniq | wc -l)"
let B="$(ps -eo euid | tail -n +2 | sort -n | uniq | wc -l)"
let C="$(ps -eo rgid | tail -n +2 | sort -n | uniq | wc -l)"
let D="$(ps -eo egid | tail -n +2 | sort -n | uniq | wc -l)"

echo "$A;$B"
echo "$C;$D" 1>&2
