/*
Written by Musa Azeem
Completed:  
This object represents a cluster of data with:
    A centroid, of type Point, the center of its assigned data points
    A count of how many members are assigned to it
    The total of the distances between the cluster's centroid and every data point assigned to it
This object implemented through the kMeans class, in which each cluster's ID is its index in the kMeans array
The Constructor Input Options are:
    None (default)
    Number of coordinates, a value to populate cluster's centroid with, and the membership of its centroid (id of this cluster)
    Another instance of the Clust object, to copy
Output:
    None
*/ 
#ifndef CLUST_H
#define CLUST_H
#include "Point.h"

struct Clust{
    Clust(): centroid(), nmembers(0), totalDistance(0) {}
    Clust(const int nvals, const double val, const int membership): 
        centroid(nvals, val, membership), nmembers(0), totalDistance(0) {}
    Clust(const Clust &other): centroid(other.centroid), nmembers(other.nmembers), totalDistance(other.totalDistance) {}
    Point centroid;
    int nmembers;
    double totalDistance;   //sum of all member points distances to the cluster's centroid
};

#endif