# Basic Usage
Code used to generate the shortest path between two four letter words, where two words are considered
adjacent if they can be changed using a single letter difference. Build using `make` and run using
`./wordpath [start] [end]`. The dictionary used is the file "four.txt" which is extracted from the file "words.txt",
which was in turn downloaded from the [Project Gutenburg Website](http://www.gutenberg.org/ebooks/673). Feel free to modify
this source if there are words you do not agree with, or even use your own text source.  If you do make changes be sure
to rebuild with `make clean` and `make` before using. Note that the text file must be sorted alphabetically (you can use the bash
[sort](https://ss64.com/bash/sort.html) for example).

# Example Path
For example, a path might look like
```
$ ./wordpath pink blue
pink
pins
pius
plus
flus
flue
blue
```

# Other Functions
Feel free to read through the file misc.c for a list of other potentially cool functions that are not used by wordpath
(but nonetheless return some interesting information).

