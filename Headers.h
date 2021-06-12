
#include<bits/stdc++.h>
using namespace std;
class Graph;
class ListData
{
public:
    int key;
    int index;
    int weight;
    ListData(int key,int index);
};

class Data
{
public:
    int key;
    int index;
    list<ListData > adjList;

    Data(int key);
    ~Data();
    bool addEdgeByKey(int key, Graph &g);
    bool addEdgeByIndex(int index, Graph& g);
    bool deleteEdgeByKey(int Givekey);
    bool deleteEdgeByIndex(int index);
};

class Graph
{
//private:
public:
    vector<Data> Nodes;

    Graph();
    ~Graph();
    bool addNode(int key);
    bool deleteNodeByKey(int key);
    bool deleteNodeByIndex(int index);
    void breadthFirstTraversal(int index);
    void dfsTraversalWrap();
    void dfsTraversal(int index,int* dfsvisited);
    bool topologicalSort();
    void MSTprims();
};

class myComparator
{
public:
    int operator() (const pair<pair<int,int>,int>& p1, const pair<pair<int,int>,int>& p2)
    {
        return p1.second > p2.second;
    }
};