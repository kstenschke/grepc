#!/bin/bash

full_path=$(realpath "$0")
dir_path=$(dirname "$full_path")
output=$(grepc -m=10 '[A-Za-z]{4,}' "$dir_path"/../data 2>&1)

for req_sub_str in '37 away' '25 Give' '18 give' '12 What'; do
  if [[ "$output" == *"$req_sub_str"* ]]; then
    echo "-- pregc for words w/ >= 10 occurrences => "\
      "Does contain ' $req_sub_str' ✓"

    continue
  else
    echo "xx pregc for words w/ >= 10 occurrences => "\
      "Doesn't contain '$req_sub_str' :("

    echo "   output is: $output"
    exit 1
  fi
done

if [[ "$output" == *"8  your"* ]]; then
  echo "xx pregc for words w/ >= 10 occurrences => "\
  "Does contain '8  your' :("
  echo "   output is: $output"
  exit 1
else
  echo "-- pregc for words w/ >= 10 occurrences => "\
  "Does NOT contain '8  your' ✓"
fi

exit 0
