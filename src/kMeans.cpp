/*
Written by Musa Azeem
Completed:  
Implements functions of kMeans class
*/
#include "kMeans.h"

using namespace std;

kMeans::kMeans(): nvals(0), nclust(0), clusters(nullptr), fitness(0) {}
kMeans::kMeans(const int _nvals, const int _nclust, const double range): nvals(_nvals), nclust(_nclust), fitness(0) {
    /*
    Alternate Constructor
    Input:  int: number of coordinates of data, int: number of clusters for analysis, double: value to initialize clusters near
    Output: None
    */
    clusters = new Clust[nclust];
    for(int i(0); i<nclust; i++){
        srand48(time(NULL));
        double random = drand48()*range;  //get semi-random number (use given value for range)
        clusters[i].centroid = Point(nvals, random, i); //initialize centroids
    }
}
kMeans::kMeans(const kMeans &other): nvals(other.nvals), nclust(other.nclust), fitness(other.fitness) {
    /*
    Copy Constructor
    Input:  kMeans: instance of kMeans to copy
    Output: None
    */
    if(nclust==0){
        clusters = nullptr;
    }
    else{
        clusters = new Clust[nclust];
        for(int i(0); i<nclust; i++){
            clusters[i] = Clust(other.clusters[i]);
        }
    }
}
kMeans::~kMeans(){
    /*
    Destructor - deallocates memory of Clust array
    Input:  None
    Output: None
    */
    delete [] clusters;
}
const kMeans & kMeans::operator=(const kMeans &rhs){
    /*
    Assignment operator - copies instance of kMeans object
    Input:  kMeans: instance of object to copy
    Output: kMeans: returns rhs for cascading

    */
    nvals = rhs.nvals;
    nclust = rhs.nclust;
    fitness = rhs.fitness;

    delete [] clusters;
    if(nclust==0){
        clusters = nullptr;
    }
    else{
        clusters = new Clust[nclust];
        for(int i(0); i<nclust; i++){
            clusters[i] = Clust(rhs.clusters[i]);
        }
    }
    return(rhs);
}
void kMeans::ClusterSummary() const{
    /*
    Prints information about clusters formed during kMeans Analysis
        requires kMeansClustering to be completed
    Input:  None
    Output: Prints cluster information to stdout
        fitness of analysis
        number of clusters used
        the center of each cluster's centroid
        number of members of each cluster
        average distance between the points and the centroid for each cluster
    */
    if(!clusters){
        cout << "kMeans Clustering has not been completed for this dataset" << endl;
        return;
    }
    cout << "Total fitness: " << fitness << endl;
    cout << "Numbers of Clusters: " << nclust << endl << endl;
    for(int i(0); i<nclust; i++){                        
        cout << "Cluster " << i << ": " << endl;
        cout << "Centroid: ";
        for(int j(0); j<nvals; j++){
            cout << clusters[i].centroid[j] << " ";
        }
        cout << endl << "Number of Members: " << clusters[i].nmembers << endl;
        cout << "Average Distance: " << clusters[i].totalDistance / clusters[i].nmembers << endl << endl;
    }
}

double kMeans::kMeansClustering(Point *data, const int size, const int maxIter, const double toler){
    /*
    Preforms kMeansClustering analysis on a given dataset of Point objects
        will not complete if the given data's points do not have the same dimensions of the clusters' centroids
        intially sets all points as members of first cluster
        main iteration continues until tolerance or maximum iteration is reached
        each iteration, setMemberships and moveCentroid are called to perform analysis
        after iteration completes, the total distance between each cluster and its points is calculated
            and each data point has the distance to its centroid calculated and saved
        finally, the fitness of the kMeansClustering analysis is calculated and returned

        Input:  Point*: array of point object to preform analysis on, int: size of dataset, int: maximum number of iterations, double: tolerance
        Ouptut: fitness of kMeans Clustering - sets memberships of data Points
    */
    if(data[0].getSize() != nvals){
        cout << "dataset is not of correct dimensions" << endl;
        exit(1);
    }
    clusters[0].nmembers = size;    //all points in data start with memberships to first cluster
    for(int i(0); i<size; i++){
        data[i].setMembership(0);
    }
    int iter(0);
    Point prevCentroids[nclust];
    bool cont(1);
    while(cont){
        for(int i(0); i<nclust; i++){
            prevCentroids[i] = Point(clusters[i].centroid); //save old centroid locations to check tolerance
        }

        setMemberships(data, size);   //call method to calc distances and set memberships
        moveCentroids(data, size);    //move centroids to mean of all points assigned to it

        cont = 0;
        for(int i(0); i<nclust; i++){
            if(clusters[i].centroid.distance(prevCentroids[i])>toler){
                //if difference between new and old centroid locations is not less than tolerance for each centroid, continue iteration
                cont = 1;
            }
        }
        if(iter>=maxIter){  //if max number of iterations   is reached, end iteration
            cont = 0;
        }
        iter++;
    }
    //clean up - set all points' centroidDistance and calculate the fitness (total distances of each cluster)
    double tempDist;
    for(int i(0); i<size; i++){
        for(int id(0); id<nclust; id++){                
            if(data[i].getMembership() == id){
                tempDist = data[i].distance(clusters[id].centroid);
                data[i].setCentroidDistance(tempDist);
                clusters[id].totalDistance += tempDist;
            }
        }
    }
    calcFitness(size);
    return(fitness);
}

void kMeans::setMemberships(Point *data, const int size){
    /*
    Calculates the distance from every point to every centroid, and sets points' memberships to the closest centroid's cluster
    Starts by setting points' centroidDistance to their centroids, which would have been moved last iteration of analysis
    it then iteration through each point, calculating distances and setting the point's membership to the closet centroid's cluster
    Input:  Point*: array of Point objects, int: size of array
    Output: None - directly modifies data and clusters
    */
    //calculate distance between every point and each cluster
    //assign membership of each point to closest cluster
    double leastDist;
    double prevDist;
    double dist;
    int id;
    int prevMember;
    for(int i(0); i<size; i++){
        //loop through every data point
        id = data[i].getMembership();    //get membership of point
        data[i].setCentroidDistance(data[i].distance(clusters[id].centroid));  //set each points centroid distance to moved centroid
        leastDist = data[i].getCentroidDistance();   //initially set leastDist to distance to current centroid
        prevMember = id;     //save the old membership of point before changing it
        for(int j(0); j<nclust; j++){
            //loop through clusters - calculate distance of current point to each cluster and find least
            dist = data[i].distance(clusters[j].centroid);
            if(dist < leastDist){
                leastDist = dist;   //set leastDist to the distance to the nearest cluster
                id = j;             //if the distance to this cluster is less, set membership of point to it
            }
        }
        if(id != prevMember){   //change membership of point if there is a new shortest distance
            data[i].setMembership(id);
            clusters[id].nmembers++;    //incremenent counter of members for centroid
            clusters[prevMember].nmembers--; //decrement old centroid since it lost a member
        }
    }
}

void kMeans::moveCentroids(Point *data, const int size){
    /*
    Calculates the average of all points assigned to each cluster and move cluster's centroid to that location
    Input:  Point*: array of Point objects, int: size of array
    Output: None - directly modifies clusters
    */
    double means[nclust][nvals];    //hold mean of each coordinate of data points assigned to each cluster
    for(int i(0); i<nclust; i++){
        for(int j(0); j<nvals; j++){
            means[i][j]=0;
        }
    }
    for(int i(0); i<size; i++){ //loop through all points
        for(int id(0); id<nclust; id++){ //loop through cluster ids
            if(data[i].getMembership() == id){
                //if point is a member of this cluster, add its coordinates to array
                for(int j(0); j<nvals; j++){
                    means[id][j] += data[i][j];
                }
                //data[i].setCentroidDistance(data[i].distance(clusters[id].centroid));
            }
        }
    }
    for(int i(0); i<nclust; i++){   //loop through clusters to find means and assign new location
        for(int j(0); j<nvals; j++){
            if(clusters[i].nmembers!=0){
                means[i][j] = means[i][j] / clusters[i].nmembers;
                clusters[i].centroid[j] = means[i][j];
            }
        }
    }
}

void kMeans::calcFitness(const int size){
    /*
    Calculates fitness of kMeans Clustering
        calculates sum of all distances between points and their assigned centroid
        divides by the total number of points to get average
    Input:  int: size of dataset
    Output: None - sets class member fitness to calculated value
    */
    for(int i(0); i<nclust; i++){
        fitness += clusters[i].totalDistance;
    }
    fitness = fitness / size;
}

ostream & operator<<(ostream &lhs, const kMeans &rhs){
    /*
    Prints centroid data to ostream
    Input:  kMeans: object to print centroid of
    Output: Prints centroids to ostream
    */
    for(int i(0); i<rhs.nclust; i++){
        lhs << rhs.clusters[i].centroid << endl;
    }
    return(lhs);
}