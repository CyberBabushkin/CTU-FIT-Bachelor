#!/bin/bash

mkdir tmpFolder
tar -cf pokus.tar /usr/bin/bashbug /usr/bin/perlbug /usr/share/man/man1/perlbug.1 /usr/share/man/man1/bashbug.1
cd tmpFolder && tar -xf ../pokus.tar && cd ..
find tmpFolder -type f -exec mv {} . \;
rm -rf tmpFolder
