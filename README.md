# grepc - Grep Chart

## Synopsis

``grepc PATTERN [FILE]``
``grepc -v PATTERN [FILE]``

PATTERN = an extended regular expression (ERE).  
FILE = a relative or absolute path to a file or directory.


## Description

**grepc** searches for PATTERN in each FILE. If no FILE is given, recursively 
searches the working directory. **grepc** prints all matches, sorted by- 
and including their amount of occurrences. 


## Table of Contents

* [Synopsis](#synopsis)
* [Description](#description)
* [Table of Contents](#table-of-contents)
* [Options](#options)
  * [-v, --verbose](#-v---verbose)
  * [-V, --version](#-v---version)
* [Usage examples](#usage-examples)
  * [Find floating numbers sorted by popularity](#find-floating-numbers-and-their-popularity)
  * [Find floating numbers sorted by popularity](#find-floating-numbers-and-their-popularity)
* [Build from source](#build-from-source)
* [Code Convention](#code-convention)
* [Author and License](#author-and-license)
* [Used third party applications](#used-third-party-applications)


## Options

### -v, --verbose

Print verbosely, that is - print additionally to the grep chart, 
a results summary:

* amount of total matches
* amount of matching strings
* amount of files searched


### -V, --version

Print information about installed version of **grepc**, its license and 
author(s).


## Usage examples  

### Find strings wrapped in double quotes, sorted by popularity
  
Find strings that are enclosed in double quotes, with a minimum length of ten
characters:

``grepc -v '"[A-Za-z ]{10,}"' ./src/*``  

**Output e.g.:**

```
Found 1071 matches in 83 out of 195 files.
There are 7 different matching strings:

"White Christmas"  - 156 occurrences.
"Candle in the Wind"   - 155 occurrences.
"In the Summertime"  - 154 occurrences.
"I will always love you"  - 153 occurrences.
"Rock around the Clock"  - 152 occurrences.
"Its now or never"  - 151 occurrences.
"We are the world"  - 150 occurrences.
```


### Find floating numbers sorted by popularity  

Find floating numbers that have at least 14 decimal places.

``grepc -v '(\d\.\d+){16,}' ./src/*``

**Output e.g.:**

```
Found 177 matches in 83 out of 90 files.
There are 2 different matching strings:

3.14159265358979 - 91 occurrences.
2.71828182845904 - 86 occurrences.
```


## Build from source

...


## Code Convention

...


## Author and License

...


## Used third party applications

* grep
* wc
