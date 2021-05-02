#!/bin/bash

full_path=$(realpath "$0")
dir_path=$(dirname "$full_path")
output=$(grepc -v '[A-Za-z]{4,}' "$dir_path"/../data 2>&1)

for req_sub_str in 'Found 341 matches in 3 files.' \
'There are 183 different matching strings:'; do
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
