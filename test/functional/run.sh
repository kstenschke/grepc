#!/bin/bash

script_path=$(dirname $0)

"$script_path"/01_test_version_info.sh
"$script_path"/02_test_no_pattern.sh
"$script_path"/03_test_unknown_option.sh
"$script_path"/04_test_words_in_path.sh
"$script_path"/05_test_words_in_file.sh
