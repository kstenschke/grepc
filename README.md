# Group-Grep (ggrep)

## Table of Contents

...


## Usage example / What does it do? 

``ggrep '(\d\.\d+){16,}' ./src/*``

1. Performs ``grep`` with given regular expression (in the above example: 
   float number that is at least 16 characters long) recursively on given path 
   of directory or file.
2. Outputs amounts of: total matches, files containing matches, files scanned.
3. Outputs a descending "hit list": all matching strings and their amount of 
   total occurrences. 

**Output e.g.:**

```
Found 177 matches in 83 out of 90 files.
There are 2 different matching strings:

..

3.14159265358979 - 91 occurrences.
2.71828182845904 - 86 occurrences.
```


``gg '"[A-Za-z_]{10,}"' ./src/*``

## Build from source

...


## Code Convention

...


## Author and License

...


## Used third party applications

* grep
* wc
