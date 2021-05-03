#!/bin/bash

output=$(grepc -V 2>&1)
for req_sub_str in 'grepc' '0.0.2' 'License GPLv3+:' 'github.com/kstenschke'; do
  if [[ "$output" == *"$req_sub_str"* ]]; then
    echo "-- pregc -v => Does contain '$req_sub_str' ✓"
    continue
  else
    echo "xx pregc -v => Does NOT contain '$req_sub_str' :("
    echo "   output is: $output"
    exit 1
  fi
done


output=$(grepc --version 2>&1)
for req_sub_str in 'grepc' '0.0.2' 'License GPLv3+:' 'github.com/kstenschke'; do
  if [[ "$output" == *"$req_sub_str"* ]]; then
    echo "-- pregc --version => Does contain '$req_sub_str' ✓"
    continue
  else
    echo "xx pregc --version => Does NOT contain '$req_sub_str' :("
    echo "   output is: $output"
    exit 1
  fi
done

exit 0
