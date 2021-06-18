#include <bits/stdc++.h>
using namespace std;
#include"Headers.h"

ListData::ListData(int Givekey,int Giveweight, int Giveindex)
    :key(Givekey),index(Giveindex),weight(Giveweight)
{
}



Data::Data(int Givekey)
{
    this->key = Givekey;
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
    for (int i = 0; i < this->Nodes.size(); i++)
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
                else if(lIt->index == Foundindex)
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

bool Graph::deleteNodeByIndex(int Giveindex)
{
    int found = 0;
    if (Giveindex > this->Nodes.size() || Giveindex < 0)//invalid index
        return false;

    vector<Data>::iterator vecIt;
    for(vecIt = this->Nodes.begin(); vecIt != this->Nodes.end(); vecIt++)
    {
        list<ListData>::iterator lIt,eraseptr;
        found = 0;
        for(lIt = vecIt->adjList.begin(); lIt != vecIt->adjList.end(); lIt++)
        {
            if(lIt->index > Giveindex)
            {
                lIt->index--;
            }
            else if(lIt->index == Giveindex)
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
    this->Nodes.erase(i + Giveindex);
    for (int j = Giveindex; j < this->Nodes.size(); j++)
    {
        this->Nodes[j].index = j;
    }
    return true;
}

bool Data::addEdgeByKey(int Givekey, int Giveweight, Graph &g)
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
        cout << "Key Not Found" << endl;
        return false;
    }

    //else found -- check for existing edge
    list<ListData>::iterator it;
    for(it = g.Nodes[this->index].adjList.begin();it != g.Nodes[this->index].adjList.end(); it++)
    {
        if(it->index == d1->index)
        {
            cout << "Already edge existing" << endl;
            return false;//already exists
        }
    }

    //else add an edge
    this->adjList.push_back(ListData(Givekey, Giveweight, d1->index));//found and pushed
    return true;
}

bool Data::addEdgeByIndex(int Giveindex, int Giveweight, Graph& g)
{
    if(Giveindex > g.Nodes.size() || this->index == Giveindex || Giveindex < 0)//invalid index or self loop
    {
        cout << "Invalid Index" << endl;
        return false;//invalid index
    }

    list<ListData>::iterator it;
    for(it = g.Nodes[this->index].adjList.begin(); it != g.Nodes[this->index].adjList.end(); it++)
    {
        if(it->index == Giveindex)
        {
            cout << "Already Exists" << endl;
            return false;//already edge exists
        }
    }

    g.Nodes[this->index].adjList.push_back(ListData(g.Nodes[Giveindex].key, Giveweight, Giveindex));//not found -- adding the edge
    cout << "Edge Added" << endl;
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
    if(index < 0 || (index > this->Nodes.size()))
    {
        cout<<"invalid index"<<endl;
        return;//invalid index
    }

    bool* visited = new bool[this->Nodes.size()];
    //memset(visited,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        visited[i] = false;
    }

    list<int> queue;
    visited[index] = true;

    queue.push_back(index);

    list<ListData>::iterator it;
    while(!queue.empty())
    {
        index = queue.front();
        //later appropriate data should be printed
        cout << index << " ";
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
    int* dfsvisited = new int[this->Nodes.size()];
    //memset(dfsvisited,false,this->Nodes.size()*sizeof(int));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        dfsvisited[i] = false;
    }

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
    memset(pred,0,this->Nodes.size()*sizeof(int));

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
        pred[j] = -1;//visited

        list<ListData>::iterator it;
        for(it = this->Nodes[j].adjList.begin(); it != this->Nodes[j].adjList.end(); it++)
        {
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

bool Graph::shortestPathFixedNode(int Giveindex)
{
    if(Giveindex > this->Nodes.size() || Giveindex < 0)
    {
        cout << "Invalid index" << endl;
        return false;
    }

    int* found = new int[this->Nodes.size()];
    memset(found,0,this->Nodes.size()*sizeof(int));
    cout<<endl;

    int* distance = new int[this->Nodes.size()];
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        distance[i] = INT_MAX;
    }


    int* prev = new int[this->Nodes.size()];
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        prev[i] = Giveindex;
    }

    found[Giveindex] = 1;
    distance[Giveindex] = 0;
    list<ListData>::iterator it;
    for(it = this->Nodes[Giveindex].adjList.begin(); it != this->Nodes[Giveindex].adjList.end(); it++)
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

    for(int i = 0; i < this->Nodes.size(); i++)
    {
        cout<<distance[i]<<" ";
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
    int* dfsvisited = new int[this->Nodes.size()];
    //memset(dfsvisited,false,this->Nodes.size()*sizeof(int));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        dfsvisited[i] = false;
    }

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
    //memset(visited,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        visited[i] = false;
    }

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

    //memset(visited,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        visited[i] = false;
    }
    //memset(recStack,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        recStack[i] = false;
    }

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
    //memset(visited,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        visited[i] = false;
    }

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

    // Graph g;
    // g.addNode(0);
    // g.addNode(1);
    // g.addNode(2);
    // g.addNode(3);
    // g.addNode(4);
    // g.addNode(5);
    // g.addNode(6);
    // g.addNode(7);
    // g.Nodes[0].addEdgeByIndex(1,10,g);
    // g.Nodes[1].addEdgeByIndex(3,10,g);
    // g.Nodes[1].addEdgeByIndex(4,10,g);
    // g.Nodes[4].addEdgeByIndex(7,10,g);
    // g.Nodes[3].addEdgeByIndex(7,10,g);
    // g.Nodes[7].addEdgeByIndex(5,10,g);
    // g.Nodes[7].addEdgeByIndex(6,10,g);
    // g.Nodes[5].addEdgeByIndex(2,10,g);
    // g.Nodes[6].addEdgeByIndex(2,10,g);
    // g.Nodes[2].addEdgeByIndex(0,10,g);

    // cout << endl;
    // g.Nodes[2].deleteEdgeByIndex(0);
    // g.topologicalSort();
    // cout << endl;

    // g.deleteNodeByIndex(5);
    // vector<Data>::iterator it = g.Nodes.begin();
    // list<ListData>::iterator j;
    // for(it = g.Nodes.begin();it != g.Nodes.end(); it++)
    // {
    //     cout<<it->index<<" ";
    //     for(j = g.Nodes[it->index].adjList.begin(); j!=g.Nodes[it->index].adjList.end();j++)
    //     {
    //         cout<<j->index<<"-";
    //     }
    //     cout<<endl;

    // }
    // g.deleteNodeByKey(4);
    // for(it = g.Nodes.begin();it != g.Nodes.end(); it++)
    // {
    //     cout<<it->index<<" ";
    //     for(j = g.Nodes[it->index].adjList.begin(); j!=g.Nodes[it->index].adjList.end();j++)
    //     {
    //         cout<<j->index<<"-";
    //     }
    //     cout<<endl;

    // }
    
    // g.dfsTraversalWrap();
    // cout<<endl;
    // g.breadthFirstTraversal(0);

    // cout<<"\n\n";
    // Graph g1;
    // g1.addNode(0);
    // g1.addNode(1);
    // g1.addNode(2);
    // g1.addNode(3);
    // g1.Nodes[0].addEdgeByIndex(1,3,g1);
    // g1.Nodes[1].addEdgeByIndex(0,3,g1);
    // g1.Nodes[0].addEdgeByIndex(2,3,g1);
    // g1.Nodes[2].addEdgeByIndex(0,3,g1);
    // g1.Nodes[1].addEdgeByIndex(2,2,g1);
    // g1.Nodes[2].addEdgeByIndex(1,2,g1);
    // g1.Nodes[2].addEdgeByIndex(3,2,g1);
    // g1.Nodes[3].addEdgeByIndex(2,2,g1);
    // g1.Nodes[3].addEdgeByIndex(1,3,g1);
    // g1.Nodes[1].addEdgeByIndex(3,3,g1);
    // g1.MSTprims();

    Graph g2;
    g2.addNode(0);
    g2.addNode(1);
    g2.addNode(2);
    g2.addNode(3);
    g2.addNode(4);

    g2.Nodes[0].addEdgeByIndex(1,2,g2);
    g2.Nodes[0].addEdgeByIndex(2,5,g2);
    g2.Nodes[0].addEdgeByIndex(4,3,g2);

    g2.Nodes[1].addEdgeByIndex(2,6,g2);
    g2.Nodes[1].addEdgeByIndex(4,10,g2);
    g2.Nodes[1].addEdgeByIndex(3,4,g2);

    g2.Nodes[2].addEdgeByIndex(4,2,g2);
    g2.Nodes[2].addEdgeByIndex(3,6,g2);

    g2.Nodes[4].addEdgeByIndex(2,1,g2);
    g2.Nodes[4].addEdgeByIndex(3,2,g2);

    g2.shortestPathFixedNode(0);
    //cout<<INT_MAX;




    return 0;
}
