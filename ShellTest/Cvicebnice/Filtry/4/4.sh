#!/bin/bash

comm -12 shell.denied  <(cat /etc/passwd | awk -F':' '{ print $7 }' | sort | uniq)
