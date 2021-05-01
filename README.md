# Grep Chart

## Synopsis

``grepc PATTERN [FILE]``  
``grepc -v PATTERN [FILE]``

PATTERN = an extended regular expression (ERE).  
FILE = a relative or absolute path to a file or directory.


## Description

**grepc** searches for PATTERN in each FILE. If no FILE is given, recursively 
searches the working directory.  
**grepc** prints all matches, sorted by- and including their amount of
occurrences. 


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
* [Used third party applications](#used-third-party-applications)
* [Author and License](#author-and-license)


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

``grepc '"[A-Za-z ]{10,}"' ./src/*``  

**Output e.g.:**

```
156 "White Christmas"
155 "Candle in the Wind"
154 "In the Summertime"
153 "I will always love you"
152 "Rock around the Clock"
151 "Its now or never"
150 "We are the world"
```


### Find floating numbers sorted by popularity  

Find floating numbers that have at least 14 decimal places.

``grepc -v '(\d\.\d+){16,}' ./src/*``

**Output e.g.:**

```
Found 177 matches in 83 out of 90 files.
There are 2 different matching strings:

91 3.14159265358979
86 2.71828182845904
```


## Build from source

``cmake CMakeLists.txt; make``


## Code Convention

The source code of **grepc** follows the Google C++ Style Guide, 
see: https://google.github.io/styleguide/cppguide.html  


## Changelog

See [CHANGELOG.md](CHANGELOG.md)

## Used third party applications

| Application                                                                                    | License                                                                      |
| ---------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------- |
| [GNU Grep](https://www.gnu.org/software/grep/)                                                 | [GNU General Public License](https://www.gnu.org/licenses/licenses.html#GPL) |
| [wc](https://www.gnu.org/software/coreutils/manual/html_node/wc-invocation.html#wc-invocation) | [GNU General Public License](https://www.gnu.org/licenses/licenses.html#GPL) |


## Author and License

**grepc** was written by Kay Stenschke and is licensed under the 
[GNU General Public License V3.0](https://www.gnu.org/licenses/licenses.html#GPL)  

```
Permissions of this strong copyleft license are conditioned on making available 
complete source code of licensed works and modifications, which include larger 
works using a licensed work, under the same license. Copyright and license 
notices must be preserved. Contributors provide an express grant of patent 
rights.
```

