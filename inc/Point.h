/*
Written by Musa Azeem
Completed:  
Defines the Point object
This object represents a data point with:
    an n number of coordinates 
    Membership to a cluster 
    The distance from this point to the centroid of its cluster
The constructor input options are:
    None (default)
    Number of coordinates, a value to populate array with, and membership of Point
    Number of coordinates, a double array to populate object with, and membership of Point
    Another instance of Point to copy
Other input:
    Assignment operator to assign object to another Point object
    Stream extraction operator: recieves n values from istream to populate array
Functions that output data:
    distance:   calculates the distance between this object and another instance of Point
    stream insertion operator:  outputs values of array and then the membership of the point, seperated by ','
*/
#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point{
    friend std::ostream & operator<<(std::ostream &lhs, const Point &rhs);
    friend std::istream & operator>>(std::istream &lhs, Point &rhs);
    public:
        Point();
        Point(const int numOfCoord, const double val, const int _membership);
        Point(const int numOfCoord, const double *_coord, const int _membership);
        Point(const Point &other);
        ~Point();

        int getSize() const;
        int getMembership() const;
        double getCentroidDistance() const;

        void setCentroidDistance(const double _centroidDistance);
        void setMembership(const int _membership);
        int & accessMembership();

        double distance(const Point &other) const;

        double operator[](const int index) const;
        double & operator[](const int index);
        bool operator==(const Point &rhs) const;
        bool operator!=(const Point &rhs) const;
        const Point & operator=(const Point &rhs);
    private:
        double *coord;
        int size;
        int membership;
        double centroidDistance;
};

#endif