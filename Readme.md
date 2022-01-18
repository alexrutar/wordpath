# Wordpath
Find the shortest path between two four letter words, where two words are considered adjacent if one can be obtained from the other by changing a single letter.

## Installation
Simply clone the repository and build using `make`:
```
git clone https://github.com/alexrutar/wordpath
cd wordpath && make
```
This will probably work with most mildly modern versions of gcc.

## Basic usage
The main subcommand `search` determines the distance between words.
For example, to find the distance between the words "real" and "fake", run:
```
$ ./wordpath search real fake
real
heal
hell
hall
hale
hake
fake
```
If there is no path, the program returns an error:
```
$ ./wordpath search good evil
There is no path from "good" to "evil".
(return code 1)
```

## Other Functions
Get the adjacent words in the word list:
```
$ ./wordpath adjacent soup
coup
loup
soap
soul
sour
```
Get a word which has maximum distance from the given word:
```
$ ./wordpath farthest soup
axle
```
Get the isolated vertices (words with no neighbours):
```
$ ./wordpath isolated
...
```
Get the words which are the maximum (finite) distance apart in the graph (this is very slow):
```
$ ./wordpath diameter
...
Max distance 16, from "abut" to "inca".
```

## Customizing the word dictionary
The dictionary used is the file [four.txt](four.txt) which is extracted from the word list from the [Project Gutenburg Website](http://www.gutenberg.org/ebooks/673).
Note that this program will work with any word list - the words do not need to have exactly four letters.
Feel free to modify this source if there are words you do not agree with, or even use your own text source.
If you do make changes, ensure that you first delete the object file `graph`.

Note that the text file must be sorted alphabetically for the program to work.

