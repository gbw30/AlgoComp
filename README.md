<H1> Suburban Scope </h1>
This program takes a data set of cities and prints a list of cities in the data set that have the attribute specified by the user. It also uses quick sort and merge sort and compares the time complexity of both algorithms to sort the data so that binary search can be used to retrieve the values for printing. Additionally, a random city data set generator is included in the repository. This program can be modified for different types of data.

<h2> Features </h2>

- Menu
- Print all cities in alphabetical order
- Print all cities with specified name
- Print all cities that start with certain character
- Print all cities in specified timeone
- Print all cities with exact specified population
- Print all cities under/over specified population
- Print all cities under/over specified latitute
- Print all cities under/over specified longitude
- Print all cities in specified state
- Print all cities under/over specified elevation
- Print all urban cities (poplation > 7 million) in alphabetical order
- Print all suburban cities (3 million < population < 7 million) in alphabetical order
- Print all rural cities (population < 3 million) in alphabetical order

<h3> Repository contents </h3>

- BinarySearch.h: binary search implementation
- City.h and City.cpp: City object
- MergeSort.h: merge sort implementation
- QuickSort.h: quick sort implementation
- datasetGen.h and datasetGen.cpp: program that generates random data set of cities
- main.cpp: main file with input parsing
- readerfile.h and readerfile.cpp: files to read data from csv files
- test.txt: smaller data set for testing
- test2.txt: larger data set (100 000 city objects) for testing
