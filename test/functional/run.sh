#!/bin/bash

script_path=$(dirname $0)

"$script_path"/01_version_info.sh
"$script_path"/02_no_pattern.sh
"$script_path"/03_unknown_option.sh
"$script_path"/04_words_in_path.sh
"$script_path"/05_words_in_file.sh
"$script_path"/06_words_in_path_verbose.sh
"$script_path"/07_words_in_pwd_without_arg.sh
"$script_path"/08_words_with_min_occurrence_amount.sh
