/*
Written by Musa Azeem
Completed:  11/10/21
This file defines the Point class, which represents a multidementional data
    point with a cluster membership

Constructors:
    Default:    no arguments
    alternate:  takes a number of dimensions, a value to assign all values,
        and a cluster membership
    alternate:  takes a number of dimensions, an array to assign values to,
        and a cluster membership
    copy:   copies the values of another Point instance

Private Class Variables:
    coord (double *):   n-length array of values
    size (int):         number of dimensions of point (length of coord)
    membership (int):   id of cluster that point belongs to
    centroid_distance (double): distance of point to the centroid of its cluster

Public Functions:
    get_size                return number of coordinates of point
    get_membership          return id of the cluster point is assigned to
    get_centroid_distance   return distance to centroid of cluster
    set_centroid_distance   set the value of centroid_distance
    set_membership          set membership of point
    access_membership       returns a mutable value of the points membership
    distance                return distance between this point and a another point
    operator[]              get and set values of point with bracket operator
    operator==              compare values of point with another instance
    operator!=              compare values of point with another instance
    operator=               assign point to the values of another instance
*/

#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{
    friend std::ostream & operator<<(std::ostream &lhs, const Point &rhs);
    friend std::istream & operator>>(std::istream &lhs, Point &rhs);
    public:
        Point();
        Point(const int num_of_coord, const double val, const int _membership);
        Point(const int num_of_coord, const double *_coord, const int _membership);
        Point(const Point &other);
        ~Point();

        int get_size() const;
        int get_membership() const;
        double get_centroid_distance() const;

        void set_centroid_distance(const double _centroidDistance);
        void set_membership(const int _membership);
        int & access_membership();

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
        double centroid_distance;
};

#endif