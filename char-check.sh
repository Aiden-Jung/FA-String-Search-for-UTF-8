#!/bin/bash

grep --color='auto' -n -P "[^\x00-\x7F]" /home/reseda/Public/algorithms/resources/eight-cousins.txt

file /home/reseda/Public/algorithms/resources/eight-cousins.txt
