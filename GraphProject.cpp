#include <bits/stdc++.h>
using namespace std;
class Graph;

class Data
{
public:
    int key;
    int index;
    list<int> adjList;

    Data(int key);
    ~Data();
    bool addEdgeByKey(int key, Graph &g);
    bool addEdgeByIndex(int index, Graph& g);
};

Data::Data(int key)
{
    this->key = key;
}

Data::~Data()
{
    this->adjList.clear();
}

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

Graph::Graph()
{
}

Graph::~Graph()
{
    for (int i = 0; i < Nodes.size(); i++)
    {
        Nodes[i].~Data();
    }
}

bool Graph::addNode(int key)
{
    try
    {
        Nodes.push_back(Data(key));
        Nodes[Nodes.size() - 1].index = Nodes.size() - 1;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool Graph::deleteNodeByKey(int key)
{
    vector<Data>::iterator i;
    for (i = Nodes.begin(); i != Nodes.end(); i++)
    {
        if (i->key == key)
        {
            break;
        }
    }
    if (i != Nodes.end())
    {
        int index = i->index;
        Nodes.erase(i);
        for (int i = index; i < Nodes.size(); i++)
        {
            Nodes[i].index = i;
        }
        return true;
    }
    return false;
}

bool Graph::deleteNodeByIndex(int index)
{
    if (index > Nodes.size())
        return false;

    vector<Data>::iterator i = Nodes.begin();
    Nodes.erase(i + index);
    for (int i = index; i < Nodes.size(); i++)
    {
        Nodes[i].index = i;
    }
    return true;
}

bool Data::addEdgeByKey(int key, Graph &g)
{
    if (this->key == key) //avoiding self loops
        return false;
    vector<Data>::iterator i, d1;
    //searching for the key
    for (i = g.Nodes.begin(); i != g.Nodes.end(); i++)
    {
        if (i->key == key)
        {
            d1 = i;
            break;
        }
    }
    if (d1 == g.Nodes.end())//key not found
    {
        return false;
    }

    list<int>::iterator it;
    for(it = g.Nodes[this->index].adjList.begin();it != g.Nodes[this->index].adjList.end(); it++)
    {
        if(*it == d1->index)
        {
            return false;//already exists
        }
    }

    //else adda an edge
    this->adjList.push_back(d1->index);//found and pushed
    return true;
}

bool Data::addEdgeByIndex(int index, Graph& g)
{
    if(index > g.Nodes.size() || this->index == index || index < 0)
        return false;//invalid index
    if(find(g.Nodes[this->index].adjList.begin(),g.Nodes[this->index].adjList.end(),index) != g.Nodes[this->index].adjList.end())
        return false;//already edge exists

    g.Nodes[this->index].adjList.push_back(index);
        return true;
    
}





int main()
{
    return 0;
}
