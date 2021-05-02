#!/bin/bash

output=$(grepc 2>&1)

if [ -z "${output##*No pattern given.*}" ]; then
  echo "-- pregc w/o any argument => Prints 'No pattern given' ✓"
else
  echo "xx pregc -v => Does NOT print 'No pattern given.' :("
  echo "   output is: $output"
  exit 1
fi

exit 0
