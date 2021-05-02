#!/bin/bash

output=$(grepc -x 2>&1)

if [ -z "${output##*Unknown option: -x*}" ]; then
  echo "-- pregc w/ unknown option => Prints corresponding message ✓"
else
  echo "xx pregc w/ unknown option => Does NOT print corresponding message :("
  echo "   output is: $output"
  exit 1
fi

exit 0
