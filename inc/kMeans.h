/*
Written by Musa Azeem
Completed:  
This program defines the kMeans object
This object contains n number of clusters (Clust objects), and can recieve a dataset to complete kMeans Clustering on it
Constructor Input Options are:
    none (default)
    number of coordinates, number of clusters, and a range to initalize clusters in
    another instance of kMeans to copy
Other Input:
    Assignment operator to assign object to another kMeans object
    kMeansClustering function:  
        an array of Points (with same dimensions as cluster centroids)
        size of the array
        maximum number of iterations to complete
        tolerance of kMeans Clustering
Functions that Output data:
    stream insertion operator prints the clusters' centroids to ostream
    kMeansClustering modifies memberships of Points given to it and returns the fitness of kMeans Clustering
    ClusterSummary prints the cluster data to stdout

*/
#ifndef KMEANS_H
#define KMEANS_H
#include "Point.h"
#include "Clust.h"
#include <iostream>

class kMeans{
    friend std::ostream & operator<<(std::ostream &lhs, const kMeans &rhs);

    public:
        kMeans();
        kMeans(const int _nvals, const int _nclust, const double range);
        kMeans(const kMeans &other);
        ~kMeans();
        const kMeans & operator=(const kMeans &rhs);
        double kMeansClustering(Point *data, const int size, const int maxIter, const double toler);
        void ClusterSummary() const;

    private:
        int nclust;
        Clust *clusters;
        int nvals;
        double fitness;

        void setMemberships(Point *data, const int size);
        void moveCentroids(Point *data, const int size);
        void calcFitness(const int size);
};

#endif