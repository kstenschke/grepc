#!/bin/bash

full_path=$(realpath "$0")
dir_path=$(dirname "$full_path")
output=$(grepc '[A-Za-z]{4,}' "$dir_path"/../data 2>&1)

for req_sub_str in '37 away' '25 Give' '18 give' '12 What' '8  your' \
'6  little' '2  dolor' '2  dolore' '2  Alice' '1  irure'; do
  if [[ "$output" == *"$req_sub_str"* ]]; then
    echo "-- pregc for words in path => Does contain '$req_sub_str' ✓"
    continue
  else
    echo "xx pregc for words in path => Does NOT contain '$req_sub_str' :("
    echo "   output is: $output"
    exit 1
  fi
done

exit 0
