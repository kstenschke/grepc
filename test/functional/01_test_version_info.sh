#!/bin/bash

script_path=$(dirname $0)

output=$("$script_path"/../../bin/linux/grepc -V)

for req_sub_str in 'grepc' '0.0.1' 'License GPLv3+:' 'github.com/kstenschke'; do
  if [ -z "${output##*$req_sub_str*}" ]; then
    continue
  else
    echo "pregc -v output does NOT contain '$req_sub_str'."
    exit 1
  fi
done

output=$("$script_path"/../../bin/linux/grepc --version)

for req_sub_str in 'grepc' '0.0.1' 'License GPLv3+:' 'github.com/kstenschke'; do
  if [ -z "${output##*$req_sub_str*}" ]; then
    continue
  else
    echo "pregc -v output does NOT contain '$req_sub_str'."
    exit 1
  fi
done

exit 0