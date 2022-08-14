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
    double fitness(0);

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

    myData data2(obs, dim, 0);

    //TESTING
    myData data1;               //3) Default
    myData data5(obs, dim, 0);  //4)    Alt
    //5
    myData data3(data2);        //6) copy
    data1 = data5;              //7) assignment
    data1 = myData(30, 2, 0);
    data3 = myData(10, 2, -4);
    std::cout << "data1==data2 " << (data1==data2) << std::endl;   //8) equality
    std::cout << "data1!=data2 " << (data1!=data2) << std::endl;   //9) inequality
    myData data4 = data1+data3; //10) addition
    std::cout << data4;
    //11    no setters because they would not be appropriate

    in_file >> data2;           //12) >>
    data2.summary();            //14) Summary
    fitness = data2.kMeans_clustering(2, 100, 0.001);    //15) kMeansClustering
    std::cout << "K-Means Cluster with 2 clusters produced a fitness of " << fitness;
    std::cout << std::endl;
    data2.cluster_summary();     //16) ClusterSummary

    //17 []
    data2[0] = 5;
    std::cout << data2[0] << std::endl;
    out_file << data2;      //13) <<

    in_file.close();
    out_file.close();
    return(0);
}
