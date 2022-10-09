#include <iostream>
#include <fstream>
#include <string>
#include "inc/myData.h"

int main(int argc, char** argv)
{
    std::ifstream in_file;
    std::ofstream out_file;
    std::string inFile, outFile, Input;
    int obs, dim;
    double fitness = 0;

    if(argc != 3) {
       std::cout << "Usage for " << argv[0] << ":" << std::endl;
       std::cout << argv[0] << " <InputFileName> <OutputFileName>" << std::endl;
       exit(0);
    }
    inFile = argv[1];
    outFile = argv[2];

    std::cout << "Enter the number of observations and the number of variables: ";
    std::cin >> obs >> dim;

    in_file.open(inFile);
    if (in_file.fail())
    {
        std::cout << "Error openning the file " << inFile << " \n";
        exit(1);
    }

    out_file.open(outFile);
    if (out_file.fail())
    {
        std::cout << "Error openning the file " << outFile << " \n";
        exit(1);
    }

    // Usage examples
    myData data1;               // Default Constructor
    myData data2(obs, dim, 0);  // Alternate Constructor
    myData data3(data2);        // Copy Constructor
    myData data4(obs, dim, 0);  // Alternate Constructor

    data1 = data4;              // Assignment Operator
    data1 = myData(30, 2, 0);
    data3 = myData(10, 2, -4);
    std::cout << "data1==data2 " << (data1==data2) << std::endl;   // Equality
    std::cout << "data1!=data2 " << (data1!=data2) << std::endl;   // Inequality

    myData data4 = data1+data3; // Addition Operator
    std::cout << data4;

    in_file >> data2;           // Stream Extraction Operator

    data2.summary();            // Summary Function

    // Performing Clustering
    fitness = data2.kMeans_clustering(2, 100, 0.001);
    std::cout << "K-Means Cluster with 2 clusters produced a fitness of " << fitness;
    std::cout << std::endl;
    data2.cluster_summary();

    data2[0] = 5;   // Brackets Operator
    std::cout << data2[0] << std::endl;

    // Stream Insertion Operator
    out_file << data2;

    in_file.close();
    out_file.close();
    return 0;
}
