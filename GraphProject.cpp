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

bool Graph::addNode(int Givekey)
{
    vector<Data>::iterator it;
    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        if(it->key == Givekey)
        {
            cout<<"Already Exists"<<endl;
            return false;
        }
    }
    //else push the node
    Nodes.push_back(Data(Givekey));
    Nodes[this->Nodes.size() - 1].index = this->Nodes.size() - 1;
    return true;
}

bool Graph::deleteNodeByKey(int Givekey)
{
    int found = 0;
    vector<Data>::iterator i;
    for (i = this->Nodes.begin(); i != this->Nodes.end(); i++)
    {
        if (i->key == Givekey)
        {
            break;
        }
    
    }
    if (i != this->Nodes.end())//found index in the node vector
    {
        int Foundindex = i->index;
        vector<Data>::iterator vecIt;
        for(vecIt = this->Nodes.begin(); vecIt != this->Nodes.end(); vecIt++)
        {
            list<ListData>::iterator lIt,eraseptr;
            found = 0;
            for(lIt = vecIt->adjList.begin(); lIt != vecIt->adjList.end(); lIt++)
            {
                if(lIt->index > Foundindex)
                {
                    lIt->index--;
                }
                if(lIt->index == Foundindex)
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
        this->Nodes.erase(i);
        for (int i = Foundindex; i < this->Nodes.size(); i++)
        {
            this->Nodes[i].index = i;
        }
        return true;
    }
    return false;//key not found
}

bool Graph::deleteNodeByIndex(int index)
{
    int found = 0;
    if (index > this->Nodes.size() || index < 0)//invalid index
        return false;

    vector<Data>::iterator vecIt;
    for(vecIt = this->Nodes.begin(); vecIt != this->Nodes.end(); vecIt++)
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
    vector<Data>::iterator i = this->Nodes.begin();
    this->Nodes.erase(i + index);
    for (int i = index; i < this->Nodes.size(); i++)
    {
        this->Nodes[i].index = i;
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
    if(index < 0 || index > sizeof(this->Nodes))
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

        for(it = this->Nodes[index].adjList.begin(); it != this->Nodes[index].adjList.end(); it++)
        {
            if(!visited[it->index])
            {
                visited[it->index] = true;
                queue.push_back(it->index);
            }
        }

    }
}



void Graph::dfsTraversalWrap()
{
    static int* dfsvisited = new int[sizeof(this->Nodes)];
    memset(dfsvisited,false,sizeof(dfsvisited));

    for(auto it:this->Nodes)
    {
        if( !dfsvisited[it.index] )
        {
            this->dfsTraversal(it.index,dfsvisited);
        }
    }

}

void Graph::dfsTraversal(int index,int* dfsvisited)
{
    dfsvisited[index] = true;
    cout << "visiting node no." << index <<" ";

    list<ListData>::iterator it;
    for(it = this->Nodes[index].adjList.begin(); it != this->Nodes[index].adjList.end(); it++)
    {
        if( !dfsvisited[it->index])
        {
            this->dfsTraversal(it->index,dfsvisited);
        }
    }
}

bool Graph::topologicalSort()
{
    //predecessor array
    int* pred = new int[this->Nodes.size()];
    memset(pred,0,sizeof(pred));

    list<ListData>::iterator it;
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        for(it = this->Nodes[i].adjList.begin(); it != this->Nodes[i].adjList.end(); it++)
        {
            pred[it->index]++;
        }
    }

    for(int i = 0; i < this->Nodes.size(); i++)
    {
        int j;
        for(j = 0; j < this->Nodes.size(); j++)
        {
            if(pred[j] == 0)
            {
                break;//first node with 0 predecessor found
            }
        }
        if(pred[j] != 0 && pred[j] != -1)
            return false;

        if(pred[j] == -1)//all node are exhausted
            return true;
        
        //jth vertex does not have a predecessor
        cout << j << " ";

        list<ListData>::iterator it;
        for(it = this->Nodes[j].adjList.begin(); it != this->Nodes[j].adjList.end(); it++)
        {
            pred[j] = -1;
            pred[it->index]--;
        }
    }
}

//MSTset --> {(base_node_index,edge_directed_to_index),weight}

 void Graph::MSTprims()
 {
    vector<pair<pair<int,int>,int>> MSTset;
    set<int> visited;
    //min heap to extract min weight edge
    priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,myComparator> minHeap;
    //starting from 0
    visited.insert(0);
    list<ListData>::iterator it;
    for(it = this->Nodes[0].adjList.begin(); it != this->Nodes[0].adjList.end(); it++)
    {
        minHeap.push(make_pair(make_pair(0,it->index),it->weight));
    }

    while(MSTset.size() < (this->Nodes.size() - 1))
    {
        pair<pair<int,int>,int> top = minHeap.top();
        if(visited.find(top.first.second) == visited.end())
        {
            visited.insert(top.first.second);
            MSTset.push_back(make_pair(make_pair(top.first.first,top.first.second),top.second));
            minHeap.pop();
            for(it = (this->Nodes.begin() + top.first.second)->adjList.begin(); it != (this->Nodes.begin() + top.first.second)->adjList.end(); it++)
            {
                minHeap.push(make_pair(make_pair((this->Nodes.begin() + top.first.second)->index,it->index),it->weight));
            }
        }
        else
        {
            minHeap.pop();
        }
    }

    cout << "The MST is --> " << endl;

    vector<pair<pair<int,int>,int>>::iterator i;
    for(i = MSTset.begin();i != MSTset.end(); i++)
    {
        cout << "(" << i->first.first << " , " << i->first.second << ") ";
    }

 }

bool Graph::shortestPathFixedNode(int index)
{
    if(index > this->Nodes.size() || index < 0)
    {
        cout << "Invalid index" << endl;
        return false;
    }

    int* found = new int[this->Nodes.size()];
    memset(found,0,sizeof(found));

    int* distance = new int[this->Nodes.size()];
    memset(distance,INT_MAX,sizeof(distance));

    int* prev = new int[this->Nodes.size()];
    memset(prev,index,sizeof(prev));

    found[index] = 1;
    list<ListData>::iterator it;
    for(it = this->Nodes[index].adjList.begin(); it != this->Nodes[index].adjList.end(); it++)
    {
        distance[it->index] = it->weight;
    }

    for(int i = 0; i < this->Nodes.size(); i++)
    {
        int min = INT_MAX;
        int min_ind = 0;
        for(int j = 0; j < this->Nodes.size(); j++)
        {
            if(distance[j] < min && found[j] == 0)
            {
                min = distance[j];
                min_ind = j;
            }
        }

        found[min_ind] = 1;

        for(it = this->Nodes[min_ind].adjList.begin(); it != this->Nodes[min_ind].adjList.end(); it++)
        {
            if(found[it->index] == 0 && (distance[min_ind] + it->weight < distance[it->index]))
            {
                distance[it->index] = distance[min_ind] + it->weight;
                prev[it->index] = min_ind;
            }
        }
    }
}

void Graph::AllPairShortestPath()
{
    vector<vector<int>> Dist(this->Nodes.size(),vector<int> (this->Nodes.size(),INT_MAX));

    vector<vector<list<int>>> Path;

    for(auto i : this->Nodes)
    {
        for(auto j : i.adjList)
        {
            Dist[i.index][j.index] = j.weight;
            Path[i.index][j.index].push_back(1);//first node of the list marked as 1 to show the presence of edge
        }
    }

    for(int k = 0; k < this->Nodes.size(); k++)
    {
        for(int i = 0; i < this->Nodes.size(); i++)
        {
            for(int j = 0; j < this->Nodes.size(); j++)
            {
                if(Dist[i][j] > Dist[i][k] + Dist[k][j])
                {
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
                    Path[i][j].push_back(k);
                }
            }
        }
    }
}

void Graph::dfsSearchWrap(int Givedata)
{
    int* dfsvisited = new int[sizeof(Nodes)];
    memset(dfsvisited,false,sizeof(dfsvisited));

    found = 0;

    for(auto it:this->Nodes)
    {
        if( !dfsvisited[it.index] )
        {
            this->dfsSearch(Givedata,it.index,dfsvisited);
        }
    }

}

void Graph::dfsSearch(int Givedata,int index,int* dfsvisited)
{   
    dfsvisited[index] = true;
    if(this->Nodes[index].data == Givedata)
    {
        cout << "Data found At Index - " << index;
        return; 
        found = 1;
    }

    list<ListData>::iterator it;
    for(it = this->Nodes[index].adjList.begin(); it != this->Nodes[index].adjList.end(); it++)
    {
        if( !dfsvisited[it->index])
        {
            this->dfsSearch(Givedata,it->index,dfsvisited);
            if(found == 1)
                return;
        }
    }
}

void Graph::breadthFirstSearch(int index,int Givedata)
{
    if(index < 0 || index > sizeof(this->Nodes))
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
        if(this->Nodes[index].data == Givedata)
        {
            cout << "Found at index - " << index;
            break;
        }
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


bool Graph::isCyclic()
{
    bool* visited = new bool[this->Nodes.size()];
    bool* recStack = new bool[this->Nodes.size()];

    memset(visited,false,sizeof(visited));
    memset(recStack,false,sizeof(recStack));

    for(int i = 0; i < this->Nodes.size(); i++)
    {
        if(this->isCyclicUtil(i,visited,recStack))
            return true;
        
        return false;
    }
}

bool Graph::isCyclicUtil(int index,bool* visited,bool* recStack)
{
    if(visited[index] == false)
    {
        visited[index] = true;
        recStack[index] = true;

        list<ListData>::iterator it;
        for(it = this->Nodes[index].adjList.begin(); it != this->Nodes[index].adjList.end(); it++)
        {
            if( !visited[it->index] && this->isCyclicUtil(it->index,visited,recStack))
            {
                return true;
            }
            else if(recStack[it->index])
            {
                return true;
            }
        }

        recStack[index] = false;
        return false;
    }
}

void Graph::allPathsBetweenPairOfNodes(int index1, int index2)
{
    if((index1 < 0 || index1 > this->Nodes.size()) || (index2 < 0 || index2 > this->Nodes.size()))
    {
        cout << "invalid indices" << endl;
        return;
    }

    bool* visited = new bool[this->Nodes.size()];
    memset(visited,false,sizeof(visited));

    int* path = new int[this->Nodes.size()];
    int pathIndex = 0;

    
    this->allPathsBetweenPairOfNodesUtil(index1,index2,visited,path,pathIndex);
    
}


void Graph::allPathsBetweenPairOfNodesUtil(int index1, int index2,bool* visited,int* path,int& pathIndex)
{
    visited[index1] = true;
    path[pathIndex] = index1;
    pathIndex++;

    if(index1 == index2)
    {
        for(int i = 0; i < pathIndex; i++)
        {
            cout << "Path - " << endl;
            cout << path[i] << " ";
        }
        cout << endl;

    }
    else
    {
        list<ListData>::iterator it;
        for(it = this->Nodes[index1].adjList.begin(); it != this->Nodes[index1].adjList.end(); it++)
        {
            if( !visited[it->index])
            {
                this->allPathsBetweenPairOfNodesUtil(it->index,index2,visited,path,pathIndex);
            }
        }
    }

    pathIndex--;
    visited[index1] = false;
}

int main()
{
    return 0;
}
