#include <bits/stdc++.h>
using namespace std;
#include"Headers.h"

ListData::ListData(int key, int index)
    :key(key),index(index)
{
}



Data::Data(int key)
{
    this->key = key;
}

Data::~Data()
{
    this->adjList.clear();
}



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
    vector<Data>::iterator it;
    for(it = Nodes.begin(); it != Nodes.end(); it++)
    {
        if(it->key == key)
        {
            cout<<"Already Exists"<<endl;
            return false;
        }
    }
    //else push the node
    Nodes.push_back(Data(key));
    Nodes[Nodes.size() - 1].index = Nodes.size() - 1;
    return true;
}

bool Graph::deleteNodeByKey(int key)
{
    int found = 0;
    vector<Data>::iterator i;
    for (i = Nodes.begin(); i != Nodes.end(); i++)
    {
        if (i->key == key)
        {
            break;
        }
    
    }
    if (i != Nodes.end())//found index in the node vector
    {
        int index = i->index;
        vector<Data>::iterator vecIt;
        for(vecIt = Nodes.begin(); vecIt != Nodes.end(); vecIt++)
        {
            list<ListData>::iterator lIt,eraseptr;
            found = 0;
            for(lIt = vecIt->adjList.begin(); lIt != vecIt->adjList.end(); lIt++)
            {
                if(lIt->index > index)
                {
                    lIt->index--;
                }
                if(lIt->index == index)
                {
                    eraseptr = lIt;
                    found = 1;
                    //erase the incoming pointers to the node to be deleted
                }
            }
            if(found == 1)
                vecIt->adjList.erase(eraseptr);
        }
        //after erasing the the incoming pointers erase the node
        Nodes.erase(i);
        for (int i = index; i < Nodes.size(); i++)
        {
            Nodes[i].index = i;
        }
        return true;
    }
    return false;//key not found
}

bool Graph::deleteNodeByIndex(int index)
{
    int found = 0;
    if (index > Nodes.size() || index < 0)//invalid index
        return false;

    vector<Data>::iterator vecIt;
    for(vecIt = Nodes.begin(); vecIt != Nodes.end(); vecIt++)
    {
        list<ListData>::iterator lIt,eraseptr;
        found = 0;
        for(lIt = vecIt->adjList.begin(); lIt != vecIt->adjList.end(); lIt++)
        {
            if(lIt->index > index)
            {
                lIt->index--;
            }
            if(lIt->index == index)
            {
                eraseptr = lIt;
                found = 1;
                //erase the incoming pointers to the node to be deleted
            }
        }
        if(found == 1)
            vecIt->adjList.erase(eraseptr);
    }
    //after erasing the the incoming pointers erase the node
    vector<Data>::iterator i = Nodes.begin();
    Nodes.erase(i + index);
    for (int i = index; i < Nodes.size(); i++)
    {
        Nodes[i].index = i;
    }
    return true;
}

bool Data::addEdgeByKey(int Givekey, Graph &g)
{
    if (this->key == Givekey) //avoiding self loops
        return false;
    vector<Data>::iterator i, d1;
    //searching for the key
    for (i = g.Nodes.begin(); i != g.Nodes.end(); i++)
    {
        if (i->key == Givekey)
        {
            d1 = i;
            break;
        }
    }
    if (d1 == g.Nodes.end())//key not found
    {
        return false;
    }

    //else found -- check for existing edge
    list<ListData>::iterator it;
    for(it = g.Nodes[this->index].adjList.begin();it != g.Nodes[this->index].adjList.end(); it++)
    {
        if(it->index == d1->index)
        {
            return false;//already exists
        }
    }

    //else add an edge
    this->adjList.push_back(ListData(Givekey,d1->index));//found and pushed
    return true;
}

bool Data::addEdgeByIndex(int Giveindex, Graph& g)
{
    if(Giveindex > g.Nodes.size() || this->index == Giveindex || Giveindex < 0)//invalid index or self loop
        return false;//invalid index

    list<ListData>::iterator it;
    for(it = g.Nodes[this->index].adjList.begin(); it != g.Nodes[this->index].adjList.end(); it++)
    {
        if(it->index == Giveindex)
            return false;//already edge exists
    }

    g.Nodes[this->index].adjList.push_back(ListData(g.Nodes[Giveindex].key,Giveindex));//not found -- adding the edge
        return true;
    
}

bool Data::deleteEdgeByKey(int Givekey)
{
    list<ListData>::iterator it;
    for(it = this->adjList.begin(); it != this->adjList.end(); it++)//search for the key
    {
        if(it->key == Givekey)//key found
        {
            break;
        }
    }
    if(it != this->adjList.end())//erase if valid listnode found
    {
        this->adjList.erase(it);
        return true;
    }
    return false;
}

bool Data::deleteEdgeByIndex(int Giveindex)
{
    list<ListData>::iterator it;
    for(it = this->adjList.begin(); it != this->adjList.end(); it++)//search for the index
    {
        if(it->index == Giveindex)//index found
        {
            break;
        }
    }
    if(it != this->adjList.end())//erase if valid listnode found
    {
        this->adjList.erase(it);
        return true;
    }
    return false;
}

void Graph::breadthFirstTraversal(int index)
{
    if(index < 0 || index > sizeof(Nodes))
    {
        cout<<"invalid index"<<endl;
        return;//invalid index
    }

    bool* visited = new bool[this->Nodes.size()];
    memset(visited,false,sizeof(visited));

    list<int> queue;
    visited[index] = true;

    queue.push_back(index);

    list<ListData>::iterator it;
    while(!queue.empty())
    {
        index = queue.front();
        //later appropriate data should be printed
        cout<<index<<" ";
        queue.pop_front();

        for(it = Nodes[index].adjList.begin(); it != Nodes[index].adjList.end(); it++)
        {
            if(!visited[it->index])
            {
                visited[it->index] = true;
                queue.push_back(it->index);
            }
        }

    }
}

void Graph::dfsTraversal(int index)
{
    static int* dfsvisited = new int[sizeof(Nodes)];
    
}

int main()
{
    return 0;
}
