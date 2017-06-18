#!/bin/bash

find . -type d ! -name '.' -exec chmod u+w '{}' \;
find . -type f ! -name '*txt' -exec chmod 700 '{}' \;
find . -type f -name '*.txt' -exec chmod u+r '{}' \;
