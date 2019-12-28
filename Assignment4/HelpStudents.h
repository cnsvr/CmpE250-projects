#ifndef CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#define CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <set>
#include <limits>
#include <queue>

using namespace std;

const long long int INF = numeric_limits<long long>::max();


class HelpStudents{

public:
    int N;
    int M;
    int K;
    list< pair<int,int> > *adjacencyList;
    HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways);
    void addEdge(int u,int v,int w);
    ~HelpStudents();
    long long int firstStudent();
    long long int secondStudent();
    long long int thirdStudent();
    long long int fourthStudent();
    long long int fifthStudent();


    // YOU CAN ADD YOUR HELPER FUNCTIONS AND MEMBER FIELDS

};

#endif //CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
