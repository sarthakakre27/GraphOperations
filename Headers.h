
#include<bits/stdc++.h>
using namespace std;

class Graph;
int found = 0;

/*-----------------------------------------------------LISTDATA CLASS-------------------------------------------------*/
class ListData
{
public:
    int key;
    int index;
    int weight;
    ListData(int key, int Giveweight,int index);
};


/*-----------------------------------------------------DATA CLASS-------------------------------------------------*/
class Data
{
public:
    int key;
    int index;
    int data;
    list<ListData > adjList;

    Data(int Givekey);
    Data(int Givekey,int Givedata);
    ~Data();
    bool addEdgeByKey(int key,int Giveweight, Graph &g);
    bool addEdgeByIndex(int index,int Giveweight, Graph& g);
    bool deleteEdgeByKey(int Givekey);
    bool deleteEdgeByIndex(int index);
};

/*-----------------------------------------------------GRAPH CLASS-------------------------------------------------*/

class Graph
{
//private:
public:
    vector<Data> Nodes;

    Graph();
    ~Graph();
    bool addNode(int Givekey,int Givedata);
    bool deleteNodeByKey(int Givekey);
    bool deleteNodeByIndex(int index);
    void breadthFirstTraversal(int index);
    void dfsTraversalWrap();
    void dfsTraversal(int index,int* dfsvisited);
    bool topologicalSort();
    void MSTprims();
    bool shortestPathFixedNode(int Giveindex);
    void AllPairShortestPath();
    void dfsSearchWrap(int data);
    void dfsSearch(int Givedata,int index,int* dfsvisited);
    void breadthFirstSearch(int index,int Givedata);
    bool isCyclic();
    bool isCyclicUtil(int index,bool* visited,bool* recStack);
    void allPathsBetweenPairOfNodes(int index1, int index2);
    void allPathsBetweenPairOfNodesUtil(int index1, int index2,bool* visited,int* path,int& pathIndex);
};

/*-----------------------------------------------------DATE CLASS-------------------------------------------------*/

class date
{
    int day,month,year;

public:
    date(int giveDay = 0,int giveMonth = 0,int giveYear = 0);
    void setDate();
};

/*----------------------EDUCATIONAL INSTITUTE CLASS---------------------------------------------------*/
class educatinalInstitute
{
    string InstituteName;
    date startDate;
    date endDate;

public:
    educatinalInstitute(string giveInstituteName, date givestartDate, date giveendDate);

};

class myComparator
{
public:
    int operator() (const pair<pair<int,int>,int>& p1, const pair<pair<int,int>,int>& p2)
    {
        return p1.second > p2.second;
    }
};