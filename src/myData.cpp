/*
Written by Musa Azeem
Completed:  
Implements functions of myData class
*/
#include "../inc/myData.h"
#include <math.h>

myData::myData(): data(nullptr), size(0), nvals(0) {}
myData::myData(const long int nobserv, const int _nvals, const double val=0): size(nobserv), nvals(_nvals){
    /*
    Alternate Constructor
    Input:  long int: number of observations, int: number of values for each observation, double: value to populate object with
    Output: None
    */
    data = new Point[size];
    for(int i(0); i<size; i++){
        data[i] = Point(nvals, val, -1);
    }
}
myData::myData(const myData &other): size(other.size), nvals(other.nvals) {
    /*
    Copy Constructor
    Input:  myData: instance of object to copy
    Output: None
    */
    if(size != 0){ 
        data = new Point[size];
        for(int i(0); i<size; i++){
            data[i] = Point(other.data[i]);
        }
    }
    else{
        data = nullptr;
    }
}
myData::~myData(){
    /*
    Destructor
    Input:  None
    Output: None
    */
    delete [] data;
}

const myData & myData::operator=(const myData &rhs){
    /*
    assignment operator
    Input:  myData: instance of myData to copy
    Output: returns rhs for cascading
    */
    delete [] data;

    size = rhs.size;
    nvals = rhs.nvals;
    if(size != 0){ 
        data = new Point[size];
        for(int i(0); i<size; i++){
            data[i] = Point(rhs.data[i]);
        }
    }
    else{
        data = nullptr;
    }
    return(rhs); 
}

long int myData::get_size() const{return(size);}
int myData::get_nvals() const{return(nvals);}

void myData::summary() const{
    /*
    Prints summary of data and basic analysis to stdout
    Input:  None
    Output: Prints data to stdout
    */
    std::cout << "Number of points in each column: " << size << std::endl << std::endl;;
    for(int i(0); i<nvals; i++){
        std::cout << "Column " << i << std::endl;
        std::cout << "Minimum Value: " << get_min_value(i) << std::endl;
        std::cout << "Maximum Value: " << get_max_value(i) << std::endl;
        double mean(get_mean(i));
        std::cout << "Mean: " << mean << std::endl;
        std::cout << "Standard Deviation: " << get_stand_dev(i, mean) << std::endl;
        std::cout << std::endl;
    }
}
double myData::get_min_value(const int col) const{
    /*
    Finds the minimum value of a column of data
    Input:  int: column to calculate minimum value of
    Output: Minimum value of column
    */
    if(size==0){
        std::cout << "no data" << std::endl;
        exit(1);
    }
    double min(data[0][col]);    //get value at given column of first Point in data array
    for(int i(1); i<size; i++){
        double next(data[i][col]);
        if(next<min){
            min = next;
        }
    }
    return(min);
}
double myData::get_max_value(const int col) const{
    /*
    Finds the maximum value of a column of data
    Input:  int: column to calculate maximum value of
    Output: Maximum value of column
    */
    if(size==0){
        std::cout << "no data" << std::endl;
        exit(1);
    }
    double max(data[0][col]);    //get value at given column of first Point in data array
    for(int i(1); i<size; i++){
        double next(data[i][col]);
        if(next>max){
            max = next;
        }
    }
    return(max);
}
double myData::get_mean(const int col) const{
    /*
    Finds the mean value of a column of data
    Input:  int: column to calculate mean value of
    Output: Mean value of column
    */
    if(size==0){
        std::cout << "no data" << std::endl;
        exit(1);
    }
    double sum(0);
    for(int i(0); i<size; i++){
        sum += data[i][col];
    }
    return(sum/size);
}
double myData::get_stand_dev(const int col, const double mean) const{
    /*
    Finds the Standard Deviation value of a column of data
    Input:  int: column to calculate Standard Deviation value of
    Output: Standard Deviation value of column
    */
    if(size==0){
        std::cout << "no data" << std::endl;
        exit(1);
    }
    double sum(0);
    for(int i(0); i<size; i++){
        sum += pow((data[i][col]-mean), 2);
    }
    return(sqrt(sum/size));
}

int myData::operator[](const int index) const{
    /*
    brackets get operator - returns the membership of the Point at the given index
    Input:  int: index to get membership of
    Output: int: membership of point at given index
    */
    if(index<0 || index>=size){
        std::cout << "index out of range" << std::endl;
        exit(1);
    }
    return(data[index].get_membership());
}
int & myData::operator[](const int index){
    /*
    brackets set operator - returns the memory location of the membership of the Point at the given index to set
    Input:  int: index to set membership of
    Output: int&: memory address of membership of point at given index to set
    */
    if(index<0 || index>=size){
        std::cout << "index out of range" << std::endl;
        exit(1);
    }
    return(data[index].access_membership());
}
myData myData::operator+(const myData &rhs) const{
    /*
    Addition operator - concatonates two myData objects and returns new object
        will exit if the objects' Points are of different dimensions
    Input:  myData: instance of myData to concatonate
    Output: new myData object of the concatonated myData objects
    */
    if(nvals!=rhs.nvals){
        std::cout << "Objects are of different dimensions" << std::endl;
        exit(1);
    }
    int retSize(size+rhs.size);
    myData ret(retSize, nvals);
    for(int i(0); i<size; i++){
        ret.data[i] = Point(data[i]);
    }
    for(int i(size); i<retSize; i++){
        ret.data[i] = Point(rhs.data[i-size]);
    }
    return(ret);
}
bool myData::operator==(const myData &rhs) const{
    /*
    equality operator - checks if two myData objects are equal
        order of data must be preserved
        does not check membership of points
    Input:  myData: instance of myData to compare to
    Output: bool, 1 if equal, 0 if not
    */
    if(size != rhs.size || nvals != rhs.nvals){
        return(0);
    }
    for(int i(0); i<size; i++){
        if(data[i]!=rhs.data[i]){
            return(0);
        }    
    }
    return(1);
}
bool myData::operator!=(const myData &rhs) const{
    /*
    inequality operator - checks if two myData objects are inequal
        order of data is checked
        does not check membership of points
    Input:  myData: instance of myData to compare to
    Output: bool, 0 if equal, 1 if not
    */
    return(!(*this==rhs));
}

std::istream & operator>>(std::istream &lhs, myData &rhs){
    /*
    stream extraction operator - populates object with values from istream
        number of observations must be set beforehand
    Input:  myData: instance of object to populate with values
    Output: lhs for cascading
    */
    if(rhs.get_size()==0){
        std::cout << "Size not set" << std::endl;
        exit(1);
    }
    std::cout << "Enter " << rhs.get_size() << " observations of " << rhs.get_nvals() << " values:" << std::endl;
    for(int i(0); i<rhs.get_size(); i++){
        lhs >> rhs.data[i];
    }
    return(lhs);
}
std::ostream & operator<<(std::ostream &lhs, const myData &rhs){
    /*
    Prints data points and centroids to stdout, seperated by ','
    Prints data points and appends the cluster ID they were assigned to
    Prints Centroids and appends the cluster ID they belong to
    Input:  instance of myData and ostream to print it to
    Output: data of object is printed to ostream
    */
    for(int i(0); i<rhs.get_size(); i++){
        lhs << rhs.data[i] << std::endl;
    }
    lhs << std::endl;
    lhs << rhs.kMeans_clusters << std::endl;
    return(lhs);
}

void myData::cluster_summary() const{
    /*
    Calls kMeans cluster_summary function to print cluster data to stdout
    Input:  None
    Output: Prints cluster info to stdout
    */
    kMeans_clusters.cluster_summary();
}

double myData::kMeans_clustering(const int _nclust, const int maxIter, const double toler){
    /*
    calls kMeans kMeans_clustering function, passing in the object's data to perform kMeans Clustering on data
    Input:  int: number of clusters, int: maximum number of iterations, double: tolerance
    Output: double: fitness of kMeans Clustering Analysis
    */
    if(size==0){
        std::cout << "no data, cannot complete Kmeans Clustering" << std::endl;
        return(0);
    }
    kMeans_clusters = kMeans(nvals, _nclust, get_max_value(0));
    return(kMeans_clusters.kMeans_clustering(data, size, maxIter, toler));
}