#!/bin/bash

full_path=$(realpath "$0")
dir_path=$(dirname "$full_path")
output=$(grepc '[A-Za-z]{4,}' "$dir_path"/../data/give_it_away.txt 2>&1)

for req_sub_str in '37 away' '25 Give' '18 give' '12 What' '8  your'; do
  if [[ "$output" == *"$req_sub_str"* ]]; then
    echo "-- pregc for words in file => Does contain '$req_sub_str' ✓"
    continue
  else
    echo "xx pregc for words in file => Does NOT contain '$req_sub_str' :("
    echo "   output is: $output"
    exit 1
  fi
done

if [[ "$output" == *"2 Alice"* ]]; then
  echo "xx pregc for words in lorem_ipsum.txt => Does contain '2 Alice' :("
  echo "   output is: $output"
  exit 1
else
  echo "-- pregc for words in lorem_ipsum => Does NOT contain '2 Alice' ✓"
fi

exit 0
