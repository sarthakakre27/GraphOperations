
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
    //int key;
    int index;
    int weight;
    ListData(string GiveIDNum, int Giveweight,int index);
};


/*-----------------------------------------------------DATA CLASS-------------------------------------------------*/
class Data
{
public:
    //int key;
    int index;
    //int data;
    Graph* Gref;
    list<ListData > adjList;
    //personal data -->
    string fname;
    string lname;
    string idNum;
    list<educatinalInstitute> EducationList;
    list<string> hobbies;

    Data(string Givekey, Graph* GiveGref);
    //Data(string Givekey,int Givedata,Graph* GiveGref);
    ~Data();
    //bool addEdgeByKey(int key,int Giveweight, Graph &g);//depriciated
    bool addEdgeByIDNum(string key,int Giveweight);

    bool addEdgeByIndex(int index,int Giveweight, Graph& g);
    bool deleteEdgeByKey(string Givekey);
    bool deleteEdgeByIndex(int index);
    void addData(string givekey);
    bool getConnected();

    void shortestPathToKnowSomeone();

    void listLatestConnectionsForMyNetwork();

    void findEducationMates();

};

/*-----------------------------------------------------GRAPH CLASS-------------------------------------------------*/

class Graph
{
//private:
public:
    vector<Data> Nodes;

    Graph();
    ~Graph();

    void addNodeWrap();

    bool addNode(string Givekey);
    //bool deleteNodeByKey(int Givekey);//depriciated

    void deleteNodeByKeyWrap();
    bool deleteNodeByKey(string Givekey);

    bool deleteNodeByIndex(int index);
    //change
    void addEdge(string selfkey,string tokey);
    //
    void breadthFirstTraversal(int index);

    void dfsTraversalWrap();
    void dfsTraversal(int index,int* dfsvisited);

    //void dfsTraversalForAddEdgeWrap();
    void dfsTraversalForAddEdge(int index,int* dfsvisited);

    bool topologicalSort();

    void MSTprims();

    void shortestPathToKnowEveryOne();
    bool shortestPathFixedNode(int Giveindex);

    void AllPairShortestPath();

    void dfsSearchWrap(string Givekey);
    void dfsSearch(string Givekey,int index,int* dfsvisited);

    //change
    int dfsSearchWrapID(string givekey);
    int dfsSearchID(string Givekey,int index,int* dfsvisited);
    //

    void breadthFirstSearch(int index,string Givekey);

    int breadthFirstSearchIDNum(int GiveIndex,string GiveIDNum);

    bool isCyclic();
    bool isCyclicUtil(int index,bool* visited,bool* recStack);


    void allPathsBetweenPairOfNodes(int index1, int index2);
    void allPathsBetweenPairOfNodesUtil(int index1, int index2,bool* visited,int* path,int& pathIndex);

    void findEducationMates(int index);

    void checkConnectionWrap();

    void showCompleteNetwork();
    
    void MaximumDegreeOfSeparation();

    void listPotentialGroupsOnHobbies();
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