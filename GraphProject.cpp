#include <bits/stdc++.h>
using namespace std;
#include"Headers.h"


/*-----------------------------------------LISTDATA MEMBER METHODS--------------------------------------------*/
ListData::ListData(int Givekey,int Giveweight, int Giveindex)
    :key(Givekey),index(Giveindex),weight(Giveweight)
{
}


/*-----------------------------------------DATA CLASS MEMBER METHODS-----------------------------------------*/
Data::Data(int Givekey)
{
    this->key = Givekey;
}

Data::Data(int Givekey,int Givedata)
{
    this->key = Givekey;
    this->data = Givedata;
}

Data::~Data()
{
    this->adjList.clear();
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


void Data::addData()
{
    int flag = 0;
    int hobbyflag = 0;
    string EdInstitute;
    string tempHobby;
    date temp1(0,0,0);
    date temp2(0,0,0);
    cout << "Enter Your First Name - " << endl;
    cin >> this->fname;
    cout << "Enter Your Last Name - " << endl;
    cin >> this->lname;
    cout << "Enter Your ID Number / Identification Serial Code - " << endl;
    cin >> this->idNum;
    cout << "Enter the Educational Details - " << endl;
    cout << "Press 1 to Stop" << endl;
    while(flag == 0)
    {
        cout << "Enter Name Of the Institution - " << endl;
        cin.ignore();
        getline(cin,EdInstitute);
        cout << "Enter Start Date - " << endl;
        temp1.setDate();
        cout << "Enter End Date - " << endl;
        cout << "If currently Studying Enter Expected Completion Date - " << endl;
        while(!temp2.checkGreater(temp1))
        {
            cout << "Enter a Later date than the strat date" << endl;
            temp2.setDate();
        }
        this->EducationList.push_back(educatinalInstitute(EdInstitute,temp1,temp2));
        temp1.setDateDefault();
        temp2.setDateDefault();

        cout << "Enter 1 to Stop OR 0 to Add More Institutions" << endl;
        cin >> flag;
    }


    cout << "Enter Your hobbies - " << endl;

    while(hobbyflag == 0)
    {
        cout << "Enter Hobby - " << endl;
        cin >> tempHobby;
        this->hobbies.push_back(tempHobby);
        cout << "Enter 1 to stop entering hobbies | 0 to enter more hobbies - " << endl;
        cin >> hobbyflag;
    }

}

/*----------------------------------------GRAPH CLASS MEMBERS METHODS-----------------------------------------------------*/

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

bool Graph::addNode(int Givekey,int Givedata)
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
    Nodes.push_back(Data(Givekey,Givedata));
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
    cout << endl;
    // for(int i = 0; i < this->Nodes.size(); i++)
    // {
    //     cout<<prev[i]<<" ";
    // }
    // cout << "\n" <<Giveindex<<endl;
    // cout << "Paths --> "<< endl;
    // for(int i = 0; i < this->Nodes.size(); i++)
    // {
    //     int j = this->Nodes[i].index;
    //     cout<<prev[j] <<"<-";
    //     //cout<<Giveindex<<" ";
    //     while(prev[j] != Giveindex);
    //     {
    //         cout << prev[j] << "<-";  
    //         j = this->Nodes[prev[j]].index;
    //     }
    //     cout <<endl;
    // }
}

void Graph::AllPairShortestPath()
{
    cout << "hi" <<endl;
    vector<vector<int>> Dist(this->Nodes.size(),vector<int> (this->Nodes.size(),INT_MAX));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        for(int j = 0; j < this->Nodes.size(); j++)
        {
            cout << Dist[i][j] << " ";
        }
        cout << endl;
    }

    //vector<vector<vector<int>>> Path;
    cout << "hi" <<endl;
    vector<Data>::iterator it;
    list<ListData>::iterator jt;
    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        //cout << "hi" <<endl;
        for(jt = it->adjList.begin(); jt != it->adjList.end(); jt++)
        {
            Dist[it->index][jt->index] = jt->weight;
            cout << "hi" <<endl;
            //Path[it->index][jt->index].push_back(1);//first node of the list marked as 1 to show the presence of edge
        }
    }

    for(int i = 0; i < this->Nodes.size(); i++)
    {
        for(int j = 0; j < this->Nodes.size(); j++)
        {
            cout << Dist[i][j] << " ";
        }
        cout << endl;
    }

    cout << "hi" <<endl;
    for(int k = 0; k < this->Nodes.size(); k++)
    {
        for(int i = 0; i < this->Nodes.size(); i++)
        {
            for(int j = 0; j < this->Nodes.size(); j++)
            {
                if(Dist[i][j] > Dist[i][k] + Dist[k][j] && (Dist[k][j] != INT_MAX && Dist[i][k] != INT_MAX))
                {
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
                    //Path[i][j].push_back(k);
                }
            }
        }
    }
    cout << "hi" <<endl;
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        for(int j = 0; j < this->Nodes.size(); j++)
        {
            cout << Dist[i][j] << " ";
        }
        cout << endl;
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

    vector<Data>::iterator it;
    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        if( !dfsvisited[it->index] )
        {
            this->dfsSearch(Givedata,it->index,dfsvisited);
        }
    }

}

void Graph::dfsSearch(int Givedata,int index,int* dfsvisited)
{   
    dfsvisited[index] = true;
    if(this->Nodes[index].data == Givedata)
    {
        cout << "Data found At Index - " << index << endl;
        found = 1;
        return; 
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


int Graph::dfsSearchWrapID(int Givekey)
{
    int ret_val = -1;
    int* dfsvisited = new int[this->Nodes.size()];
    //memset(dfsvisited,false,this->Nodes.size()*sizeof(int));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        dfsvisited[i] = false;
    }

    found = 0;

    vector<Data>::iterator it;
    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        if( !dfsvisited[it->index] )
        {
            ret_val = this->dfsSearchID(Givekey,it->index,dfsvisited);
            if(ret_val != -1)
                return ret_val;
        }
    }

    return ret_val;

}

int Graph::dfsSearchID(int Givekey,int index,int* dfsvisited)
{   
    int ret_val = -1;
    dfsvisited[index] = true;
    if(this->Nodes[index].key == Givekey)
    {
        cout << "Data found At Index - " << index << endl;
        found = 1;
        return index; 
    }

    list<ListData>::iterator it;
    for(it = this->Nodes[index].adjList.begin(); it != this->Nodes[index].adjList.end(); it++)
    {
        if( !dfsvisited[it->index])
        {
            ret_val = this->dfsSearchID(Givekey,it->index,dfsvisited);
            if(found == 1)
                return ret_val;
        }
    }
    return -1;
}

void Graph::breadthFirstSearch(int index,int Givedata)
{
    if(index < 0 || index > sizeof(this->Nodes))
    {
        cout << "invalid index" << endl;
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
            cout << "Found at index - " << index << endl;
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
        cout << "Path - " << endl;
        for(int i = 0; i < pathIndex; i++)
        {
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

void Graph::addEdge(int selfkey,int tokey)
{
    cout << "hi" << endl;
    int selfindex = dfsSearchWrapID(selfkey);
    cout << selfindex << endl;
    int toindex = dfsSearchWrapID(tokey);
    cout << toindex << endl;
    if(selfindex == -1)
    {
        cout << "Enter valid Id -- > ID NOT FOUND!" << endl;
        return;
    }
    if(toindex == -1)
    {
        cout << "Enter valid ID for the connection to make -- > ID to connect NOT FOUND!" << endl;
        return;
    }
    int wt = -1;//weight for the edge //for the application it is the factor that
    //how much the person the connection is made to is familiar to him/her
    cout << "hi2" << endl;
    while(wt < 0 || wt > 101)
    {
        cout << "hi3" << endl;
        cout << "How nicely Do you know the person you are connecting...on a scale of 0 - 100" << endl;
        cout << "0 - least | 100 - most" << endl;
        cin  >> wt;
    }

    //both ids are found so add the edge
    this->Nodes[selfindex].addEdgeByIndex(toindex,100 - wt,*this);
}

/*------------------------------------------------DATE CLASS MEMBER METHODS-----------------------------------------------*/
date::date(int giveDay,int giveMonth, int giveYear)
    :day(giveDay),month(giveMonth),year(giveYear)
{

}

void date::setDate()
{
    cout << "Enter date - "<< endl;
    cout << "Enter day (1-28/29/30/31) - " << endl;
    int flag = 0;
    while( !flag )
    {
        cin >> this->day;
        if(this->day > 31 || this->day < 1)
        {
            cout << "Enter valid date - " << endl;
        }
        else
        {
            flag = 1;//valid day found
        }
    }
    flag = 0;
    cout << "Enter Month (1-12) - " << endl;

    while( !flag )
    {
        cin >> this->month;
        if(this->month < 1 || this->month > 12)
        {
            cout << "Enter a valid Month - " << endl;
        }
        else
        {
            flag = 1;
        }
    }

    flag = 0;
    cout << "Enter Year (1900 - 2030) - " << endl;

    while( !flag )
    {
        cin >> this->year;
        if(this->year < 1900 || this->year > 2030)
        {
            cout << "Enter a valid Year - " << endl;
        }
        else
        {
            flag = 1;
        }
    }
}

void date::setDateDefault()
{
    this->day = 0;
    this->month = 0;
    this->year = 0;
}


bool date::checkGreater(const date& checkdate)
{
    if(this->year > checkdate.year)
        return true;
    if(this->year == checkdate.year)
    {
        if(this->month > checkdate.month)
            return true;
        if(this->month == checkdate.month)
        {
            if(this->day > checkdate.day)
            {
                return true;
            }
        }
    }
    return false;
}

/*--------------------------------------EDUCATIONAL INSTITUTE CLASS MEMBER METHODS-----------------------------------------*/
educatinalInstitute::educatinalInstitute(string giveInstituteName, date givestartDate, date giveendDate)
{
    this->InstituteName = giveInstituteName;
    this->startDate = givestartDate;
    this->endDate = giveendDate;
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

    // Graph g2;
    // g2.addNode(0);
    // g2.addNode(1);
    // g2.addNode(2);
    // g2.addNode(3);
    // g2.addNode(4);

    // g2.Nodes[0].addEdgeByIndex(1,2,g2);
    // g2.Nodes[0].addEdgeByIndex(2,5,g2);
    // g2.Nodes[0].addEdgeByIndex(4,3,g2);

    // g2.Nodes[1].addEdgeByIndex(2,6,g2);
    // g2.Nodes[1].addEdgeByIndex(4,10,g2);
    // g2.Nodes[1].addEdgeByIndex(3,4,g2);

    // g2.Nodes[2].addEdgeByIndex(4,2,g2);
    // g2.Nodes[2].addEdgeByIndex(3,6,g2);

    // g2.Nodes[4].addEdgeByIndex(2,1,g2);
    // g2.Nodes[4].addEdgeByIndex(3,2,g2);

    // g2.shortestPathFixedNode(0);
    //g2.AllPairShortestPath();
    //cout<<INT_MAX;
    // cout << g2.isCyclic();

    Graph g2;
    g2.addNode(0,200);
    g2.addNode(1,400);
    g2.addNode(2,600);
    g2.addNode(3,800);
    cout << g2.Nodes[0].data;
    g2.Nodes[2].addData();

    g2.Nodes[0].addEdgeByIndex(1,10,g2);
    g2.Nodes[0].addEdgeByIndex(2,5,g2);
    g2.Nodes[1].addEdgeByIndex(3,2,g2);
    g2.Nodes[2].addEdgeByIndex(3,1,g2);
    //g2.Nodes[0].addEdgeByIndex(3,4,g2);
    g2.addEdge(0,3);
    cout << g2.isCyclic();

    g2.breadthFirstSearch(0,800);
    g2.dfsSearchWrap(400);
    g2.allPathsBetweenPairOfNodes(0,3);
    cout << "hi";
    g2.deleteNodeByIndex(1);
    cout << g2.Nodes[1].fname << endl;
    list<educatinalInstitute>:: iterator k;
    k = g2.Nodes[1].EducationList.begin();
    cout << k->startDate.day << " " << k->startDate.year;




    return 0;
}
