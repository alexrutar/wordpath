# Wordpath

## Summary
Code used to generate the shortest path between two four letter words, where two words are considered adjacent if they can be changed using a single letter difference.
Build using `make` and run using `./wordpath search START END`.
The dictionary used is the file "four.txt" which is extracted from the file "words.txt", which was in turn downloaded from the [Project Gutenburg Website](http://www.gutenberg.org/ebooks/673).
Feel free to modify this source if there are words you do not agree with, or even use your own text source.
If you do make changes, make sure to delete the object file `graph`.

Note that the text file must be sorted alphabetically for the program to work.

### Example Path
For example, a path might look like
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
Max distance 16, from abut to inca
```
