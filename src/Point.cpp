/*
Written by Musa Azeem
Completed:  11/10/21
This file implements functions of the Point class

Functions:
    Default Constructor:    initialize values to default
    Alternate Constructor:  initializes point with a value to fill all and a cluster membership
    Alternate Constructor:  initializes point with an array to fill values and a cluster membership
    Copy Constructor:       copy the values of another Point instance
    Destructor:             deallocates memory
    get_size:               return number of coordinates of point
    get_membership:         return id of the cluster point is assigned to
    get_centroid_distance:  return distance to centroid of cluster
    set_centroid_distance:  set the value of centroid_distance
    set_membership:         set membership of point
    access_membership:      returns a mutable value of the points membership
    distance:               return distance between this point and a another point
    operator[]:             get and set values of point with bracket operator
    operator==:             compare values of point with another instance
    operator!=:             compare values of point with another instance
    operator=:              assign point to the values of another instance
*/

#include "../inc/Point.h"
#include <math.h>

Point::Point(): size(0), coord(nullptr), membership(-1), centroid_distance(-1){}

Point::Point(const int num_of_coord, const double val, const int _membership)
    : size(num_of_coord), membership(_membership), centroid_distance(-1){
    /*
    Alternate Constructor
    sets size of point and all values to the given number
    sets membership of point to given id
    sets centroid_distance to -1 to indicate no value

    Parameters:
        size (int):         number of coordinates of point
        val (double):       value to populate object with
        _membership (int):  id of cluster

    */
    coord = new double[size];
    for(int i=0; i<size; i++){
        coord[i] = val;
    }
}

Point::Point(const int num_of_coord, const double *_coord, const int _membership)
    : size(num_of_coord), membership(_membership), centroid_distance(-1) {
    /*
    Alternate Constructor
    sets size of point and values to a given array
    sets membership of point to given id
    sets centroid_distance to -1 to indicate no value

    Parameters:
        size (int):         number of coordinates of point
        _coord (double*):   array of values to assign to point
        _membership (int):  id of cluster

    */

    coord = new double[size];
    for(int i=0; i<size; i++){
        coord[i] = _coord[i];
    }
}

Point::Point(const Point &other){
    /*
    Copy Constructor
    Parameters:
        other (Point):  another instance of a Point to copy
    */

    size = other.size;
    membership = other.membership;
    centroid_distance = other.centroid_distance;
    if(size==0){
        coord = nullptr;
    }
    else {
        coord = new double[size];
        for(int i=0; i<size; i++){
            coord[i] = other[i];
        }
    }
}

Point::~Point(){
    /*
    Destructor  - deallocates memory of data array
    */

    delete [] coord;
}

int Point::get_size() const{
    /*
    Getter for size, the number of coordinates of the Point

    Return:
        int: number of coordinates of the Point
    */

    return(size);
}

int Point::get_membership() const{
    /*
    Getter for membership of the Point
    Return:
        int: membership of the Point
    */

    return(membership);
}
double Point::get_centroid_distance() const{
    /*
    Getter for centroid distance from this Point to its centroid
    
    Return:
        double: Centroid distance of the Point
    */

    return(centroid_distance);
}

void Point::set_membership(const int _membership){
    /*
    Setter for Membership of the Point

    Parameters:
        _membership(int): membership to set Point to
    */

    if(_membership<0){
        std::cout << "Invalid Cluster ID" << std::endl;
        exit(1);
    }
    membership = _membership;
}
void Point::set_centroid_distance(const double _centroid_distance){
    /*
    Setter for Centroid Distance of the Point

    Parameters:
        _centroid_distance (double): Centroid Distacne to set Point to 
    */

    if(_centroid_distance<0){
        std::cout << "Invalid Distance" << std::endl;
        exit(1);
    }
    centroid_distance = _centroid_distance;
}
int & Point::access_membership(){
    /*
    Returns a mutable value of clusters membership

    Return:
        int&: returns memory location of Point's membership to be set by myData's operator[]   
    */

    return(membership);
}

double Point::distance(const Point &other) const{
    /*
    Distance function - calculates the distance between the calling object and the argument object
    Does not complete if either objects have null data or if the objects are of different dimensions

    Parameters:  
        other (Point):  instance of Point object to find distance to
    Return: 
        double: Distance between the two Points
    */

    if(!other.coord){
        std::cout << "Argument Point Object data is Null" << std::endl;
        exit(1);
    }
    if(!coord){
        std::cout << "Calling Point Object data is Null" << std::endl;
        exit(1);   
    }
    if(size != other.size){
        std::cout << "Point objects are of difference dimensions" << std::endl;
        exit(1);
    }

    double sum(0);
    for(int i=0; i<size; i++){
        sum += (coord[i] - other[i]) * (coord[i] - other[i]);
    }
    return(sqrt(sum));
}

double Point::operator[](const int index) const{
    /*
    Brackets operator to get value of point at given index

    Parameter:
        index (int):    index to get value at

    Return:
        double: value of point at given index
    */

    if(index < 0 || index >= size){
        std::cout << "Index Out of Range" << std::endl;
        exit(1);
    }
    return(coord[index]);
}

double & Point::operator[](const int index){
    /*
    Brackets operator to set value of point at given index

    Parameters:    
        index (int): Index to set value

    Return: 
        double&: Memory location of object's array at given index so it can be set
    */
    if(index < 0 || index >= size){
        std::cout << "Index Out of Range" << std::endl;
        exit(1);
    }
    return(coord[index]);
}

const Point & Point::operator=(const Point &rhs){
    /*
    Assignment operator - copies contents of rhs into this object

    Parameters:
        rhs (Point): instance of Point object to copy
    
    Returns: 
        Point: argument object is returned for cascading
    */

    delete [] coord;
    size = rhs.size;
    membership = rhs.membership;
    centroid_distance = rhs.centroid_distance;
    if(size==0){
        coord = nullptr;
    }
    else{
        coord = new double[size];
        for(int i=0; i<size; i++){
            coord[i] = rhs[i];
        }
    }
    return(rhs);
}
bool Point::operator==(const Point &rhs) const{
    /*
    Equality operator - checks if values of two Point object are equal
        returns false if the dimensions of the objects are not the same
        or if any of the object's data are not equal
    Only checks coordinates, not the memberships of the points

    Parameters:
        rhs (Point):    instance of Point to compare calling object with

    Return:
        bool: 0 if not equal, 1 if equal    
    */
    if(size != rhs.get_size()){
        return(0);
    }
    for(int i=0; i<size; i++){
        if(coord[i] != rhs[i]){
            return(0);
        }    
    }
    return 1;
}
bool Point::operator!=(const Point &rhs) const{
    /*
    Inequality operator - checks if values of two Point object are inequal
        returns true if the dimensions of the objects are not the same
        or if any of the object's data are not equal
    Only checks coordinates, not the memberships of the points

    Parameters:
        rhs (Point):    instance of Point to compare calling object with

    Return:
        bool: 1 if not equal, 0 if equal    
    */
    return(!(*this==rhs));
}

std::ostream & operator<<(std::ostream &lhs, const Point &rhs){ 
    /*
    Stream insertion operator
    Prints coordinates of Point, and then the Points membership

    Parameters:
        lhs (ostream):  out stream to print
        rhs (Point): instance of Point to print
    */

    if(!rhs.coord){
        return(lhs);
    }
    for(int i=0; i<rhs.get_size(); i++){
        lhs << rhs[i] << ",";
    }
    lhs << rhs.get_membership();
    return(lhs);
}

std::istream & operator>>(std::istream &lhs, Point &rhs){
    /*
    Stream extraction operator
    recieves n values from istream to populate object's array
    size of array must be set beforehand

    Paramters:
        lhs (istream):  input stream 
        rhs (Point):    instance of point to print

    Istream Input:  n double values, seperated by whitespace
    */

    for(int i=0; i<rhs.get_size(); i++){
        lhs >> rhs[i];
    }
    return(lhs);
}