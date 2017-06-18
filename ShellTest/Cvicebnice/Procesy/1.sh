#!/bin/bash

ps -eo time,comm | awk '{if (NR!=1) {
  print $0
 }
}' 
