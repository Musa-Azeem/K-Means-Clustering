/*
Written by Musa Azeem
Completed:  
Implements functions of the Point class
*/
#include "Point.h"
#include <math.h>

using namespace std;

Point::Point(): size(0), coord(nullptr), membership(-1), centroidDistance(-1){}
Point::Point(const int numOfCoord, const double val, const int _membership): size(numOfCoord), membership(_membership), centroidDistance(-1){
    /*
    Alternate Constructor
    Input:  int: number of coordinates, double: value to populate object with, int: membership of Point
    Output: None
    */
    coord = new double[size];
    for(int i(0); i<size; i++){
        coord[i] = val;
    }
}
Point::Point(const int numOfCoord, const double *_coord, const int _membership): size(numOfCoord), membership(_membership), centroidDistance(-1) {
    /*
    Alternate Constructor
    Input:  int: number of coordinates, double*: array to populate object with, int: membership of Point
    Output: None
    */ 
    coord = new double[size];
    for(int i(0); i<size; i++){
        coord[i] = _coord[i];
    }
}
Point::Point(const Point &other){
    /*
    Copy Constructor
    Input:  Point: another instance of Point to copy
    Output: None
    */
    size = other.size;
    membership = other.membership;
    centroidDistance = other.centroidDistance;
    if(size==0){
        coord = nullptr;
    }
    else{
        coord = new double[size];
        for(int i(0); i<size; i++){
            coord[i] = other[i];
        }
    }
}
Point::~Point(){
    /*
    Destructor  - deallocated memory of data array
    Input:  None
    Output: None
    */
    delete [] coord;
}

int Point::getSize() const{
    /*
    Getter for size, the number of coordinates of the Point
    Input:  None
    Output: int: number of coordinates of the Point
    */
    return(size);
}
int Point::getMembership() const{
    /*
    Getter for memberhsip of the Point
    Input:  None
    Output: int: membership of the Point
    */
    return(membership);
}
double Point::getCentroidDistance() const{
    /*
    Getter for centroid distance from this Point to its centroid
    Input:  None
    Output: double: Centroid distance of the Point
    */
    return(centroidDistance);
}

void Point::setMembership(const int _membership){
    /*
    Setter for Memberhip of the Point
    Input: int: membership to set Point to 
    Output: None
    */
    if(_membership<0){
        cout << "Invalid Cluster ID" << endl;
        exit(1);
    }
    membership = _membership;
}
void Point::setCentroidDistance(const double _centroidDistance){
    /*
    Setter for Centroid Distance of the Point
    Input: double: Centroid Distacne to set Point to 
    Output: None
    */
    if(_centroidDistance<0){
        cout << "Invalid Distance" << endl;
        exit(1);
    }
    centroidDistance = _centroidDistance;
}
int & Point::accessMembership(){
    /*
    Input: None
    Output: int&: returns memory location of Point's membership to be set by myData's operator[]   
    */
    return(membership);
}

double Point::distance(const Point &other) const{
    /*
    Distance function - calculates the distance between the calling object and the argument object
    Does not complete if either objects have null data or if the objects are of different dimensions
    Input:  Point: instance of Point object to find distance to
    Output: Distance between the two Points
    */
    if(!other.coord){
        cout << "Argument Point Object data is Null" << endl;
        exit(1);
    }
    if(!coord){
        cout << "Calling Point Object data is Null" << endl;
        exit(1);   
    }
    if(size != other.size){
        cout << "Point objects are of difference dimensions" << endl;
        exit(1);
    }
    double sum(0);
    for(int i(0); i<size; i++){
        sum += (coord[i] - other[i]) * (coord[i] - other[i]);
    }
    return(sqrt(sum));
}

double Point::operator[](const int index) const{
    /*
    Brackets operator to get value of point at given index
    Input:  int: Index to get value
    Output: Value of object's array at given index
    */
    if(index < 0 || index >= size){
        cout << "Index Out of Range" << endl;
        exit(1);
    }
    return(coord[index]);
}

double & Point::operator[](const int index){
    /*
    Brackets operator to set value of point at given index
    Input:  int: Index to set value
    Output: Memory location of object's array at given index so it can be set
    */
    if(index < 0 || index >= size){
        cout << "Index Out of Range" << endl;
        exit(1);
    }
    return(coord[index]);
}

const Point & Point::operator=(const Point &rhs){
    /*
    Assignment operator - copies contents of rhs into this object
    Input:  Point: instance of Point object to copy
    Output: Point: argument object is returned for cascading
    */
    delete [] coord;
    size = rhs.size;
    membership = rhs.membership;
    centroidDistance = rhs.centroidDistance;
    if(size==0){
        coord = nullptr;
    }
    else{
        coord = new double[size];
        for(int i(0); i<size; i++){
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
    Input:  Point: instance of Point to compare calling object with
    Output: bool: 0 if not equal, 1 if equal    
    */
    if(size != rhs.getSize()){
        return(0);
    }
    for(int i(0); i<size; i++){
        if(coord[i] != rhs[i]){
            return(0);
        }    
    }
    return(1);
}
bool Point::operator!=(const Point &rhs) const{
    /*
    Inequality operator - checks if values of two Point object are inequal
        returns true if the dimensions of the objects are not the same
        or if any of the object's data are not equal
    Only checks coordinates, not the memberships of the points
    Input:  Point: instance of Point to compare calling object with
    Output: bool: 1 if not equal, 0 if equal    
    */
    return(!(*this==rhs));
}

ostream & operator<<(ostream &lhs, const Point &rhs){ 
    /*
    Stream insertion operator
    Prints coordinates of Point, and then the Points membership
    Input: Point: instance of Point to print
    Output: prints data to ostream, seperated by ','
    */
    if(!rhs.coord){
        return(lhs);
    }
    for(int i(0); i<rhs.getSize(); i++){
        lhs << rhs[i] << ",";
    }
    lhs << rhs.getMembership();
    return(lhs);
}
istream & operator>>(istream &lhs, Point &rhs){
    /*
    Stream extraction operator
    recieves n values from istream to populate object's array
    size of array must be set beforehand
    Input:  n double values, seperated by whitespace
    Output: None
    */
    for(int i(0); i<rhs.getSize(); i++){
        lhs >> rhs[i];
    }
    return(lhs);
}