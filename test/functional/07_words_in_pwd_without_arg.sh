#!/bin/bash

output=$(grepc -v '[A-Za-z]{4,}' 2>&1)

if [[ "$output" == *"Is a directory"* ]]; then
  echo "xx pregc <PATTERN> w/o <FILE> argument => "\
  "Does contain 'Is a directory' :("
  echo "   output is: $output"
  exit 1
else
  echo "-- pregc <PATTERN> w/o <FILE> argument => "\
  "Does NOT contain 'Is a directory' ✓"
fi

exit 0
