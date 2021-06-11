
#include<bits/stdc++.h>
using namespace std;
class Graph;
class ListData
{
public:
    int key;
    int index;
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
    bool deleteEdgeByKey();
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
};