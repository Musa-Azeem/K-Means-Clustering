/*
Written by Musa Azeem
Completed:  
This program defines the myData object, which holds a 2D array of data and can perform kMeans Clustering analysis on it
This objects contains:
    an array of Point objects to hold data
    size of dataset
    number of coordinates per data point
    kMeans object to perform kMeans Clustering on data
Constructor Input options are:
    None (default)
    number of observations, number of values per observation, and value to populate object
    another instance of myData to copy
Other input:
    assignment operator copies another instance of myData
    brackets operator can be used to assign the membership of a particular point
    stream extraction operator sets each data point to values from istream
Functions that output data:
    Summary prints the min, max, mean, and standard deviation of each column of data to stdout
    kMeansClustering performs kMeans Clustering on the data and returns the fitness
    ClusterSummary prints Cluster information to stdout
    string insertion operator prints the data points and centroids and their memberships to ostream
    brackets operator returns the membership of a particular point
*/
#ifndef MYDATA_H
#define MYDATA_H
#include "Point.h"
#include "kMeans.h"
#include <iostream>

class myData{
    friend std::istream & operator>>(std::istream &lhs, myData &rhs);
    friend std::ostream & operator<<(std::ostream &lhs, const myData &rhs);
    public:
        myData();
        myData(const long int nobserv, const int _nvals, const double val);
        myData(const myData &other);
        ~myData();

        long int getSize() const;
        int getNvals() const;
        int getNclust() const;
        
        double kMeansClustering(const int _nclust, const int maxIter, const double toler);
        void ClusterSummary() const;
        
        void Summary() const;
        double getMinValue(const int col) const;
        double getMaxValue(const int col) const;
        double getMean(const int col) const;
        double getStandDev(const int col, const double mean) const;

        const myData & operator=(const myData &other);
        bool operator==(const myData &other) const;         
        bool operator!=(const myData &other) const;        
        myData operator+(const myData &other) const;
        int operator[](const int index) const;
        int & operator[](const int index);

    private:
        Point *data;
        long int size;
        int nvals;
        kMeans kMeansClusters;
};

#endif