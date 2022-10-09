# K-Means-Clustering
Simple k-means clustering analysis

Author: Musa Azeem
Date Completed: 11/10/21

This project defines a C++ class that performs K-Means-Clustering on a set of data

## Requirements
Unix operating system with C++ 17

## Directory Structure
```
.
├── LICENSE.md
├── README.md
├── main.cpp
├── makefile
├── res
│   └── TwoClass_TwentyPoints.csv
├── inc
│   ├── Clust.h
│   ├── Point.h
│   ├── kMeans.h
│   └── myData.h
└── src
    ├── Point.cpp
    ├── kMeans.cpp
    └── myData.cpp
```
## Usage

### Clone this repository
1. Open terminal
2. Clone the repository  
```
    git clone "https://github.com/Musa-Azeem/K-Means-Clustering"
```
3. Change directory to local project
```
    cd K-Means-Clustering
```  

### Commands
    clean repository:   make clean
    compile project:    make compile
    run project:        ./kmeans <Input File> <Output File>

### Input File Format
- Input file must be formatted in n rows of m decimal values, with each value 
separated by a blank space
- Each observation is one row, and each observation has a number of values
- Example input file is provided in the `res` directory


## Project Components

### myData Class
- This class serves as the user interface to perform K-Means clustering
on a set of data
- It is given a number of observations, a number of values per
observation, and a value to initialize object with
- An input file can later be provided to populate the object
- This class is defined in the files `inc/myData.h` and `src/myData.cpp`

### kMeans Class
- This class provides the primary functionality behind the K-Means clustering
- It is called within the myData class
- This class is defined in the files `inc/kMeans.h` and `src/kMeans.cpp`

### Point Class
- This class is used to represent n-dimension data points in the myData and
kMeans objects
- This class is defined in the files `inc/Point.h` and `src/Point.cpp`
### Main Method
- The main method defined in `main.cpp` showcases an example usage of the
myData class
- It receives an input and output filename as command line arguments, and
uses the myData class to perform K-Means Clustering on the set of data in
input file
- Also showcases the operations available in the myData class