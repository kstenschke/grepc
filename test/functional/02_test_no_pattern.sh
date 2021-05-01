#!/bin/bash

script_path=$(dirname $0)

output=$("$script_path"/../../bin/linux/grepc) >/dev/null 2>&1

if [ -z "${output##*No pattern given.*}" ]; then
  echo "✓ pregc w/o any argument prints 'No pattern given.'."
else
  echo "pregc -v output does NOT print 'No pattern given.'."
  exit 1
fi

exit 0
