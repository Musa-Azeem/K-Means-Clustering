#include <iostream>
#include <fstream>
#include <string>
#include "myData.h"

using namespace std;

int main(int argc, char** argv)
{
    ifstream in_file;
    ofstream out_file;
    string inFile, outFile, Input;
    int obs, dim;
    double fitness(0);

    if(argc != 3) {
       cout << "Usage for " << argv[0] << ":" << endl;
       cout << argv[0] << " <InputFileName> <OutputFileName>" << endl;
       exit(0);
    }
    inFile = argv[1];
    outFile = argv[2];

    cout << "Enter the number of observations and the number of variables: ";
    cin >> obs >> dim;

    in_file.open(inFile);
    if (in_file.fail())
    {
        cout << "Error openning the file " << inFile << " \n";
        exit(1);
    }

    out_file.open(outFile);
    if (out_file.fail())
    {
        cout << "Error openning the file " << outFile << " \n";
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
    cout << "data1==data2 " << (data1==data2) << endl;   //8) equality
    cout << "data1!=data2 " << (data1!=data2) << endl;   //9) inequality
    myData data4 = data1+data3; //10) addition
    cout << data4;
    //11    no setters because they would not be appropriate

    in_file >> data2;           //12) >>
    data2.Summary();            //14) Summary
    fitness = data2.kMeansClustering(2, 100, 0.001);    //15) kMeansClustering
    cout << "K-Means Cluster with 2 clusters produced a fitness of " << fitness;
    cout << endl;
    data2.ClusterSummary();     //16) ClusterSummary

    //17 []
    data2[0] = 5;
    cout << data2[0] << endl;
    out_file << data2;      //13) <<

    in_file.close();
    out_file.close();
    return(0);
}
