/*
Student Name: FURKAN CANSEVER
Student Number: 2016400348
Project Number: 4
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "HelpStudents.h"

using namespace std;

HelpStudents::HelpStudents(int N, int M, int K, vector<pair<pair<int,int>,int>> ways) {
    this->N = N;
    this->M = M;
    this->K = K;
    this->adjacencyList = new list<pair<int,int>>[N+1];

    for (int i = 0; i < ways.size(); ++i) {
        addEdge(ways[i].first.first,ways[i].first.second,ways[i].second);
    }

}

void HelpStudents::addEdge(int u,int v,int w){
    adjacencyList[u].push_back(make_pair(v,w));
    adjacencyList[v].push_back(make_pair(u,w));
}
HelpStudents::~HelpStudents() {
    delete[] adjacencyList;
}

long long int maxEdge(int parent[], int j, int max, long long int key[]){
    if (parent[j] == -1){
        return max;
    } else{
        if(key[j] > max) {
            max = key[j];
        }
       return maxEdge(parent,parent[j],max,key);
    }
}


long long int HelpStudents::firstStudent() {

    typedef pair<long long int,int> p;

    priority_queue<p,vector<p>,greater<p>> pq;

    long long int dist[N+1];
    bool check[N+1];
    for (int j = 1; j <=N ; ++j) {
        dist[j] = INF;
        check[j] = false;
    }
    pq.push(make_pair(0,1));

    dist[1] = 0;

    while (!pq.empty()){

        pair<int,int> tmp = pq.top();
        pq.pop();

        int u = tmp.second;

        check[u] = true;

        list<pair<int,int>>:: iterator itr;
        for (itr = adjacencyList[u].begin(); itr != adjacencyList[u].end(); ++itr) {
            int v = (*itr).first;
            int w = (*itr).second;

            if ((dist[v] > dist[u] + w) && !check[v]){
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v],v));
            }
        }
    }

    return  dist[K];
}
long long int HelpStudents::secondStudent() {

    // PRIM'S ALGORITHM

    typedef pair<int,int> p;

    priority_queue<p,vector<p>,greater<p>> pq;

    int parent[N+1];
    bool check[N+1];
    long long int key[N+1];

    for (int j = 1; j <=N ; ++j) {
        check[j] = false;
        key[j] = INF;

    }

    key[1] = 0;
    parent[1] = -1;

    pq.push(make_pair(0,1));


    while (!pq.empty()){

        pair<int,int> tmp = pq.top();
        pq.pop();

        int u = tmp.second;

        check[u] = true;

        list<pair<int,int>>:: iterator itr;
        for (itr = adjacencyList[u].begin(); itr != adjacencyList[u].end(); ++itr) {
            int v = (*itr).first;
            int w = (*itr).second;

            if(!check[v] && w < key[v]){
                parent[v] = u,key[v] = w;
                pq.push(make_pair(key[v],v));
            }

        }
    }

    return maxEdge(parent,K,0,key);

}
long long int HelpStudents::thirdStudent() {
    
    //BFS

    list<int> queue;

    bool visited[N+1];
    long long int dist[N+1];

    for (int i = 1; i <= N ; ++i) {
        visited[i] = false;
        dist[i] = INF;
    }

    visited[1]  =true;
    dist[1] = 0;
    queue.push_back(1);


    while (!queue.empty()){
        int u = queue.front();
        queue.pop_front();
        list<pair<int,int>>:: iterator itr;
        for (itr = adjacencyList[u].begin(); itr != adjacencyList[u].end(); ++itr) {
            int v = (*itr).first;

            if(!visited[v]){
                visited[v] = true;
                dist[v] = dist[u] + 1;
                queue.push_back(v);

                if(v == K){
                    return dist[K];

                }
            }

        }

    }

    return  -1;
}
long long int HelpStudents::fourthStudent() {

    long long int result = 0;

    set<pair<int,int>> set;
    typedef pair<int,int> p;

    priority_queue<p,vector<p>,greater<p>> pq;

    pq.push(make_pair(0,1));

    while (!pq.empty()){
        pair<int,int> tmp = pq.top();
        pq.pop();

        int u = tmp.second;
        int weight = tmp.first;

        result += weight;

        if(u == K){
            return result;
        }

        long long int min = INF;
        long long int vertex = INF;
        list<pair<int,int>>:: iterator itr;
        for (itr = adjacencyList[u].begin(); itr != adjacencyList[u].end(); ++itr) {
            int v = (*itr).first;
            int w =  (*itr).second;

            if(set.count(make_pair(u,v)) == 0) {

                if (w < min) {
                    min = w;
                    vertex = v;

                } else if (w == min) {
                    if(v < vertex){
                        vertex = v;
                    }
                    min = w;
                }
            }
        }
        pq.push(make_pair(min,vertex));
        set.insert(make_pair(u,vertex));
        set.insert(make_pair(vertex,u));
    }

    return  -1;
}

long long int HelpStudents::fifthStudent() {

    typedef pair<pair<long long int,int>,int> p;

    priority_queue<p,vector<p>,greater<p>> pq;

    long long int distJ[N+1];
    long long int distNJ1[N+1];
    long long int distNJ2[N+1];

    for (int i = 1; i <= N; ++i) {
        distJ[i] = INF;
        distNJ1[i] = INF;
        distNJ2[i] = INF;
    }


    pq.push(make_pair(make_pair(0,1),1));

    distNJ1[1] = 0;

    while (!pq.empty()){
        pair<pair<int,int>,int> temp  = pq.top();
        pq.pop();

        int u = temp.second;

        list<pair<int,int>>:: iterator itr;
        for (itr = adjacencyList[u].begin(); itr != adjacencyList[u].end(); ++itr) {

            int v = (*itr).first;
            int w = (*itr).second;

            if (temp.first.second == 0){ // JUMP
                int dist = temp.first.first;

                if (dist<distNJ1[v]){
                    distNJ1[v] = dist;
                    pq.push(make_pair(make_pair(dist,1),v));
                }

            } else {
                if (temp.first.second == 1){
                    int dist = temp.first.first;
                    if (dist + w < distNJ2[v]){
                        distNJ2[v] = dist + w;
                        pq.push(make_pair(make_pair(dist+w,2),v));
                    }

                } else {
                    int dist = temp.first.first;
                    if (dist+w < distJ[v]){
                        distJ[v] = dist+w;
                        pq.push(make_pair(make_pair(dist+w,0),v));
                    }

                }
            }
        }
    }

    return std::min(std::min(distJ[K],distNJ1[K]),distNJ2[K]);

}

// YOU CAN ADD YOUR HELPER FUNCTIONS
