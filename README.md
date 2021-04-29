# Grouped Grep

## Table of Contents

...


## What does it do? / Usage example

``gg '"[A-Za-z]{8,}"' ./src/*``

1. Performs ``grep`` with given regular expression recursively on given path of 
   directory or file.
2. Outputs amount of: total matches, scanned files, files containing matches.
3. Outputs a descending "hit list": all matching strings and their amount of 
   total occurrences. 

**Output e.g.:**

```
Found 978 matches in 83 out of 90 files.
There are 207 different matching strings:

................................................................................
................................................................................
...............................................

"vanilla"  - 91 occurrences.
"before"   - 86 occurrences.
"after"    - 56 occurrences.
"hello"    - 41 occurrences.
"MESSAGE"  - 36 occurrences.
"Cancel"   - 32 occurrences.
...
```



## Author and License

...


## Used third party applications

* grep
* wc
