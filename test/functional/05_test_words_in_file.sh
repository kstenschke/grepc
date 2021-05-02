#!/bin/bash

full_path=$(realpath "$0")
dir_path=$(dirname "$full_path")
output=$(grepc '[A-Za-z]{5,}' "$dir_path"/../data/lorem_ipsum.txt 2>&1)

for req_sub_str in '4 dolor' '2 dolore' '1 occaecat'; do
  if [[ "$output" == *"$req_sub_str"* ]]; then
    echo "-- pregc for long words in file => Does contain '$req_sub_str' ✓"
    continue
  else
    echo "xx pregc for long words in file => Does NOT contain '$req_sub_str' :("
    echo "   output is: $output"
    exit 1
  fi
done

exit 0
