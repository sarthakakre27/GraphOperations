
#include<bits/stdc++.h>
using namespace std;

//forward declarations -->
class Graph;
class educatinalInstitute;

int found = 0;

/*-----------------------------------------------------LISTDATA CLASS-------------------------------------------------*/
class ListData
{
public:
    string idNum;
    int key;
    int index;
    int weight;
    ListData(int key, int Giveweight,int index,string GiveIDNum);
};


/*-----------------------------------------------------DATA CLASS-------------------------------------------------*/
class Data
{
public:
    int key;
    int index;
    int data;
    Graph* Gref;
    list<ListData > adjList;
    //personal data -->
    string fname;
    string lname;
    string idNum;//to be replaced with key
    list<educatinalInstitute> EducationList;
    list<string> hobbies;

    Data(int Givekey, Graph* GiveGref);
    Data(int Givekey,int Givedata,Graph* GiveGref);
    ~Data();
    bool addEdgeByKey(int key,int Giveweight, Graph &g);
    bool addEdgeByIDNum(string key,int Giveweight, Graph *g);

    bool addEdgeByIndex(int index,int Giveweight, Graph& g);
    bool deleteEdgeByKey(int Givekey);
    bool deleteEdgeByIndex(int index);
    void addData();
    bool getConnected();
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
    void addEdge(int selfkey,int tokey);
    void breadthFirstTraversal(int index);
    void dfsTraversalWrap();
    void dfsTraversal(int index,int* dfsvisited);
    //void dfsTraversalForAddEdgeWrap();
    void dfsTraversalForAddEdge(int index,int* dfsvisited);
    bool topologicalSort();
    void MSTprims();
    bool shortestPathFixedNode(int Giveindex);
    void AllPairShortestPath();
    void dfsSearchWrap(int Givedata);
    void dfsSearch(int Givedata,int index,int* dfsvisited);
    int dfsSearchWrapID(int givekey);
    int dfsSearchID(int Givekey,int index,int* dfsvisited);
    void breadthFirstSearch(int index,int Givedata);

    int breadthFirstSearchIDNum(int GiveIndex,string GiveIDNum);

    bool isCyclic();
    bool isCyclicUtil(int index,bool* visited,bool* recStack);


    void allPathsBetweenPairOfNodes(int index1, int index2);
    void allPathsBetweenPairOfNodesUtil(int index1, int index2,bool* visited,int* path,int& pathIndex);

    void findEducationMates(int index);

    void checkConnectionWrap();

    void showCompleteNetwork();
};

/*-----------------------------------------------------DATE CLASS-------------------------------------------------*/

class date
{

public:

    int day,month,year;
    date(int giveDay = 0,int giveMonth = 0,int giveYear = 0);
    void setDate();
    void setDateDefault();
    bool checkGreater(const date& checkdate);
};

/*----------------------EDUCATIONAL INSTITUTE CLASS---------------------------------------------------*/
class educatinalInstitute
{
public:
    string InstituteName;
    date startDate;
    date endDate;


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