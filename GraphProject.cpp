#include <bits/stdc++.h>
using namespace std;
#include"Headers.h"


/*-----------------------------------------LISTDATA MEMBER METHODS--------------------------------------------*/
ListData::ListData(string GiveIDNum,int Giveweight, int Giveindex)
    :idNum(GiveIDNum),index(Giveindex),weight(Giveweight)
{
}

/*-----------------------------------------DATA CLASS MEMBER METHODS-----------------------------------------*/
Data::Data(string Givekey, Graph* GiveGref)
    :Gref(GiveGref),idNum(Givekey)
{

}


Data::~Data()
{
    this->adjList.clear();
}



bool Data::addEdgeByIDNum(string GiveIDNum, int Giveweight)
{
    if (this->idNum == GiveIDNum)//avoiding self loops
    {
        cout << "Don't connect To YourSelf LOL" << endl;
        return false;
    } 
    vector<Data>::iterator i, d1;
    //searching for the key
    for (i = this->Gref->Nodes.begin(); i != this->Gref->Nodes.end(); i++)
    {
        if (i->idNum == GiveIDNum)
        {
            d1 = i;
            break;
        }
    }
    if (d1 == this->Gref->Nodes.end())//key not found
    {
        cout << "Key Not Found" << endl;
        return false;
    }

    //else found -- check for existing edge
    list<ListData>::iterator it;
    for(it = this->Gref->Nodes[this->index].adjList.begin();it != this->Gref->Nodes[this->index].adjList.end(); it++)
    {
        if(it->index == d1->index)
        {
            cout << "Already Connection exists" << endl;
            return false;//already exists
        }
    }

    //else add an edge
    this->adjList.push_back(ListData(this->idNum, Giveweight, d1->index));//found and pushed
    //make a reverse connection -- no need of approval on connection
    this->Gref->Nodes[d1->index].adjList.push_back(ListData(this->idNum,Giveweight,this->index));
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

    g.Nodes[this->index].adjList.push_back(ListData(this->idNum, Giveweight, Giveindex));//not found -- adding the edge
    cout << "Edge Added" << endl;
    return true;
    
}

bool Data::deleteEdgeByKey(string Givekey)
{
    list<ListData>::iterator it;
    for(it = this->adjList.begin(); it != this->adjList.end(); it++)//search for the key
    {
        if(it->idNum == Givekey)//key found
        {
            break;
        }
    }
    if(it != this->adjList.end())//erase if valid listnode found
    {
        list<ListData>::iterator ptr,found;
        for(ptr = this->Gref->Nodes[it->index].adjList.begin(); ptr != this->Gref->Nodes[it->index].adjList.end(); ptr++)
        {
            if(ptr->idNum == this->idNum)
            {
                found = ptr;
                break;
            }
        }
        this->Gref->Nodes[it->index].adjList.erase(found);
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


void Data::addData(string Givekey)
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
    this->idNum = Givekey;
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
            cout << "Enter a Later date than the start date" << endl;
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


void Data::showdata()
{
    cout << "---------------------------------------------------------------------" << endl;
    cout << "First Name - " << this->fname << " " << "Last Name - " << this->lname << endl;
    cout << "IdNum - " << this->idNum << endl;
    cout << "Educational Data - " << endl;
    list<educatinalInstitute>::iterator it;
    for(it = this->EducationList.begin(); it != this->EducationList.end(); it++)
    {
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Institute - " << it->InstituteName << endl;
        cout << "Start Date - " << it->startDate.day << "/" << it->startDate.month << "/" << it->startDate.year << endl;
        cout << "End Date - " << it->endDate.day << "/" << it->endDate.month << "/" << it->endDate.year << endl;
        cout << "---------------------------------------------------------------------" << endl;
    }
    cout << "Hobbies - " << endl;
    list<string>::iterator jt;
    for(jt = this->hobbies.begin(); jt != hobbies.end(); jt++)
    {
        cout << "---------------------------------------------------------------------" << endl;
        cout << *jt << endl;
        cout << "---------------------------------------------------------------------" << endl;
    }
}

void Data::updateData()
{
    int option = -1;
    string EdInstitute;
    date temp1,temp2;
    string tempHobby;
    cout << "---------------------------UPDATE DATA-------------------------------" << endl;
    cout << "--------------------Displaying current Data--------------------------" << endl;
    this->showdata();
    cout << "=========Press the Number corresponding to the Options To Update=====" << endl;
    cout << "==================1 - First Name | 2 - Last Name=====================" << endl;
    cout << "===============3 - Add Institute | 4 - update Institue===============" <<endl;
    cout << "===================5 - Add hobby | 6 - update hobby==================" << endl;
    cout << "============7 - Delete Institute | 8 - Delete Hobby==================" << endl;
    cin >> option;
    switch (option)
    {
    case 1:
        {
            cout << "Enter First Name - " << endl;
            cin >> this->fname;
            cout << "-----------------------------UPDATED---------------------------------" << endl;
        }
        break;
    case 2:
        {
            cout << "Enter Last Name - " << endl;
            cin >> this->lname;
            cout << "-----------------------------UPDATED---------------------------------" << endl;
        }
        break;
    case 3:
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
                cout << "Enter a Later date than the start date" << endl;
                temp2.setDate();
            }
            this->EducationList.push_back(educatinalInstitute(EdInstitute,temp1,temp2));
            cout << "------------------------------ADDED----------------------------------" << endl;
        }
        break;
    case 4:
        {
            cout << "Enter Institute Name - " << endl;
            cin.ignore();
            getline(cin,EdInstitute);
            list<educatinalInstitute>::iterator it,found;
            for(it = this->EducationList.begin(); it != this->EducationList.end(); it++)
            {
                if(it->InstituteName == EdInstitute)
                {
                    found = it;
                    break;
                }
            }
            if(it != this->EducationList.end())
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
                    cout << "Enter a Later date than the start date" << endl;
                    temp2.setDate();
                }
                found->InstituteName = EdInstitute;
                found->startDate = temp1;
                found->endDate = temp2;
                cout << "-----------------------------UPDATED---------------------------------" << endl;
            }
            else
            {
                cout << "Input Invalid" << endl;
            }
        }
        break;
    case 5:
        {
            cout << "Enter Hobby To Add - " << endl;
            cin >> tempHobby;
            this->hobbies.push_back(tempHobby);
            cout << "------------------------------ADDED----------------------------------" << endl;
        }
        break;
    case 6:
        {
            cout << "Enter Hobby Name in the current hobbies To Update - " << endl;
            cin >> tempHobby;
            list<string>::iterator it,found;
            for(it = this->hobbies.begin(); it != this->hobbies.end(); it++)
            {
                if(tempHobby == *it)
                {
                    found = it;
                    break;
                }
            }
            if(it != this->hobbies.end())
            {
                cout << "Enter The Updated Hobby - " << endl;
                cin >> *found;
                cout << "-----------------------------UPDATED---------------------------------" << endl;
            }
            else
            {
                cout << "Invalid Input" << endl;
            }
        }
        break;
    case 7:
        {
            cout << "Enter Institute Name To Delete - " << endl;
            cin >> EdInstitute;
            list<educatinalInstitute>::iterator it,found;
            for(it = this->EducationList.begin(); it != this->EducationList.end(); it++)
            {
                if(EdInstitute == it->InstituteName)
                {
                    found = it;
                    break;
                }
            }
            if(it != this->EducationList.end())
            {  
                this->EducationList.erase(found);
                cout << "-----------------------------DELETED---------------------------------" << endl;
            }
            else
            {
                cout << "Invalid Input" << endl;
            }
        }
        break;
    case 8:
        {
            cout << "Enter Hobby Name To Delete - " << endl;
            cin >> tempHobby;
            list<string>::iterator it,found;
            for(it = this->hobbies.begin(); it != this->hobbies.end(); it++)
            {
                if(tempHobby == *it)
                {
                    found = it;
                    break;
                }
            }
            if(it != this->hobbies.end())
            {
                this->hobbies.erase(found);
                cout << "-----------------------------DELETED---------------------------------" << endl;
            }
            else
            {
                cout << "Invalid Input" << endl;
            }
        }
        break;
    
    default:
        break;
    }
}


bool Data::getConnected()
{
    int choice = -1;
    string tempIDNUM;
    int rating = -1;
    while(choice != 2)
    {
        cout << "Press 1 to get connected via IDNUM | 0 to show List of PEOPLE on the network | 2 to exit" << endl;
        cin >> choice;
        if(choice == 1)
        {
            cout << "PLease Enter the IDNUM to get connected - " << endl;
            cin >> tempIDNUM;
            cout << "On a scale of 0-100 how nicely do you know the connection you are making?" << endl;
            rating = -1;
            while(rating < 0 || rating > 100)
            {
                cout << "Enter a valid rating - " << endl;
                cin >> rating;
            }
            if(this->addEdgeByIDNum(tempIDNUM,100-rating))
            {
                cout << "Connection Added" << endl;
            }

            cout << endl;
        }
        else if(choice == 0)//show all the people on the network to whom user can connect
        {
            int* dfsvisited = new int[this->Gref->Nodes.size()];
            for(int i = 0; i < this->Gref->Nodes.size(); i++)
            {
                dfsvisited[i] = false;
            }
            list<ListData>::iterator tr;
            for(tr = this->adjList.begin(); tr != this->adjList.end(); tr++)
            {
                dfsvisited[tr->index] = true;
            }
            dfsvisited[this->index] = true;

            for(auto it:this->Gref->Nodes)
            {
                if( !dfsvisited[it.index] )
                {
                    this->Gref->dfsTraversalForAddEdge(it.index,dfsvisited);
                }
            }
        }
        else if(choice == 2)
        {

        }
        else
        {
            cout << "Invalid Choice" << endl;
        }
    }
}


void Data::listLatestConnectionsForMyNetwork()
{
    int i;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << " - Showing Latest Connections That Were Make By Your Contacts/Connections - " << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    list<ListData>::iterator it,jt;
    for(it = this->adjList.begin(); it != this->adjList.end(); it++)
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Your Connection - " << this->Gref->Nodes[it->index].fname << " " << this->Gref->Nodes[it->index].lname << endl;
        cout << "Had latest connections --> " << endl;

        //int size = this->Gref->Nodes[it->index].adjList.size();
        jt = this->Gref->Nodes[it->index].adjList.end();
        i = 0;
        while(jt != this->Gref->Nodes[it->index].adjList.begin() and i < 3)
        {
            jt--;
            i++;
        }

        for(;jt != this->Gref->Nodes[it->index].adjList.end(); jt++)
        {
            cout << "-------------------------------------------------------------------------------" << endl;
            cout << this->Gref->Nodes[jt->index].fname << " " << this->Gref->Nodes[jt->index].lname << endl;
            cout << this->Gref->Nodes[jt->index].idNum << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
        }
    }
}


void Data::findEducationMates()
{
    this->Gref->findEducationMates(this->index);
}

void Data::shortestPathToKnowSomeone()
{
    this->Gref->shortestPathFixedNode(this->index);
}


void Data::showNetwork()
{
    string id1;
    int index1 = this->index;
    

    cout << "The complete NETWORK CONNECTIONS for the your IDNUM are -->" << endl;

    list<ListData>::iterator it;
    for(it = this->Gref->Nodes[index1].adjList.begin(); it != this->Gref->Nodes[index1].adjList.end(); it++)
    {
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
        cout << this->Gref->Nodes[it->index].fname << " " << this->Gref->Nodes[it->index].lname << endl;
        cout << "IDNUM - " << this->Gref->Nodes[it->index].idNum << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
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

void Graph::addNodeWrap()
{
    string tempID;
    cout << "Please Enter Your IDNUMBER - " << endl;
    cin >> tempID;
    int findInd = -1;
    if(this->Nodes.size() > 0)
    {
        findInd = this->dfsSearchWrapID(tempID);
        if(findInd != -1)
        {
            cout << "Entry with this ID already Exists!" << endl;
            return;
        }
        else
        {
            this->addNode(tempID);
        }
    }
    else
    {
        this->addNode(tempID);
    }
}

bool Graph::addNode(string Givekey)
{
    vector<Data>::iterator it;
    //check for Not coming through wrapper
    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        if(it->idNum == Givekey)
        {
            cout<<"Already Exists"<<endl;
            return false;
        }
    }
    //else push the node
    this->Nodes.push_back(Data(Givekey,this));
    this->Nodes[this->Nodes.size() - 1].index = this->Nodes.size() - 1;
    this->Nodes[this->Nodes.size() - 1].addData(Givekey);
    return true;
}


void Graph::deleteNodeByKeyWrap()
{
    string tempid;
    cout << "Enter the Key to delete the Data" << endl;
    cin >> tempid;
    
    if(this->deleteNodeByKey(tempid))
    {
        cout << "Deleted SuccessFully" << endl;
        return;
    }

    cout << "ID NOT FOUND" << endl;

}


bool Graph::deleteNodeByKey(string Givekey)
{
    int found = 0;
    vector<Data>::iterator i;
    for (i = this->Nodes.begin(); i != this->Nodes.end(); i++)
    {
        if (i->idNum == Givekey)
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

void Graph::dfsTraversal(int Giveindex,int* dfsvisited)
{
    dfsvisited[Giveindex] = true;
    //cout << "visiting node no." << index <<" ";
    cout <<"-------------------------------------------------" << endl;
    cout << this->Nodes[Giveindex].fname << " " << this->Nodes[Giveindex].lname << endl;
    cout << "IDNUMBER - " << this->Nodes[Giveindex].idNum << endl;
    cout << "------------------------------------------------" << endl;

    list<ListData>::iterator it;
    for(it = this->Nodes[Giveindex].adjList.begin(); it != this->Nodes[Giveindex].adjList.end(); it++)
    {
        if( !dfsvisited[it->index])
        {
            this->dfsTraversal(it->index,dfsvisited);
        }
    }
}


void Graph::dfsTraversalForAddEdge(int Giveindex,int* dfsvisited)
{
    dfsvisited[Giveindex] = true;
    //cout << "visiting node no." << index <<" ";

    cout <<"-------------------------------------------------" << endl;
    cout << this->Nodes[Giveindex].fname << " " << this->Nodes[Giveindex].lname << endl;
    cout << "IDNUMBER - " << this->Nodes[Giveindex].idNum << endl;
    cout << "------------------------------------------------" << endl;

    list<ListData>::iterator it;
    for(it = this->Nodes[Giveindex].adjList.begin(); it != this->Nodes[Giveindex].adjList.end(); it++)
    {
        if( !dfsvisited[it->index])
        {
            this->dfsTraversalForAddEdge(it->index,dfsvisited);
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
   //cout << "The MST is --> " << endl;
   cout  << "The Most Close People Over The Network  --> " << endl;
   vector<pair<pair<int,int>,int>>::iterator i;
   for(i = MSTset.begin();i != MSTset.end(); i++)
   {
       //cout << "(" << i->first.first << " , " << i->first.second << ") ";
       cout << "-------------------------------------------------------------" << endl;
       cout << this->Nodes[i->first.first].fname << " " << this->Nodes[i->first.first].lname << " <-----> " << this->Nodes[i->first.second].fname << " " << this->Nodes[i->first.second].lname << endl;
       cout << "-------------------------------------------------------------" << endl;
   }
}


void Graph::shortestPathToKnowEveryOne()
{
    string tempId;
    cout << "Enter Your ID" << endl;
    cin >> tempId;
    int indexfind = dfsSearchWrapID(tempId);
    if(indexfind != -1)
    {
        this->shortestPathFixedNode(indexfind);
    }
    else
    {
        cout << "Invalid ID" << endl;
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

    for(int i = 0; i < this->Nodes.size() - 2; i++)
    {
        int min = INT_MAX;
        int min_ind = 0;
        for(int j = 0; j < this->Nodes.size(); j++)
        {
            if(found[j] == 0 && distance[j] < min)
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

    cout << "Paths --> "<< endl;
    int j;
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        j = i;
        cout << this->Nodes[j].fname << " " << this->Nodes[j].lname << endl;
        cout << this->Nodes[j].idNum << endl;

        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" <<endl;

        cout << this->Nodes[prev[j]].fname<< " " << this->Nodes[prev[j]].lname << endl;
        cout << this->Nodes[prev[j]].idNum << endl;
        while(prev[j] != Giveindex)
        {
            j = prev[j];
            //cout << "<-" << prev[j];   
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" <<endl;
            cout << this->Nodes[prev[j]].fname<< " " << this->Nodes[prev[j]].lname << endl;
            cout << this->Nodes[prev[j]].idNum << endl;
        }
        cout << "------------------------------------------" << endl;
        cout << endl;
    }
    return true;
}

void Graph::AllPairShortestPath()
{
    int count = 0;

    vector<vector<int>> Dist(this->Nodes.size(),vector<int> (this->Nodes.size(),INT_MAX));

    vector<vector<int>> Next(this->Nodes.size(),vector<int>(this->Nodes.size(),-1));

    vector<Data>::iterator it;
    list<ListData>::iterator jt;

    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        for(jt = it->adjList.begin(); jt != it->adjList.end(); jt++)
        {
            Dist[it->index][jt->index] = jt->weight;

            if(Dist[it->index][jt->index] != INT_MAX)
            {
                Next[it->index][jt->index] = jt->index;
            }
            else
            {
                Next[it->index][jt->index] = -1;
            }
        }
    }



    for(int k = 0; k < this->Nodes.size(); k++)
    {
        for(int i = 0; i < this->Nodes.size(); i++)
        {
            for(int j = 0; j < this->Nodes.size(); j++)
            {
                if(Dist[i][j] > Dist[i][k] + Dist[k][j] && (Dist[k][j] != INT_MAX && Dist[i][k] != INT_MAX))
                {
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }

    int max = INT_MIN;
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        for(int j = 0; j < this->Nodes.size(); j++)
        {
            count = 0;
            int u = i;
            int v = j;
            if(Next[u][v] == -1)
                continue;
            while(u != v)
            {
                u = Next[u][v];
                count++;
            }
            if(count > max)
            {
                max = count;
            }
        }
    }

    cout << "Max degree of separation is - " << max + 1 << endl;
}


void Graph::MaximumDegreeOfSeparation()
{
    this->AllPairShortestPath();
}



void Graph::dfsSearchWrap(string Givekey)
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
            this->dfsSearch(Givekey,it->index,dfsvisited);
        }
    }

}

void Graph::dfsSearch(string Givekey,int index,int* dfsvisited)
{   
    dfsvisited[index] = true;
    if(this->Nodes[index].idNum == Givekey)
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
            this->dfsSearch(Givekey,it->index,dfsvisited);
            if(found == 1)
                return;
        }
    }
}


int Graph::dfsSearchWrapID(string Givekey)
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

int Graph::dfsSearchID(string Givekey,int index,int* dfsvisited)
{   
    int ret_val = -1;
    dfsvisited[index] = true;
    if(this->Nodes[index].idNum == Givekey)
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

void Graph::breadthFirstSearch(int index,string Givekey)
{
    if(index < 0 || index > this->Nodes.size())
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
        if(this->Nodes[index].idNum == Givekey)
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

int Graph::breadthFirstSearchIDNum(int Giveindex,string GiveIDNum)
{
    if(Giveindex < 0 || Giveindex > this->Nodes.size())
    {
        cout << "invalid index" << endl;
        return -1;//invalid index
    }

    bool* visited = new bool[this->Nodes.size()];
    //memset(visited,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        visited[i] = false;
    }

    list<int> queue;
    visited[Giveindex] = true;

    queue.push_back(Giveindex);

    list<ListData>::iterator it;
    while(!queue.empty())
    {
        Giveindex = queue.front();
        //later appropriate data should be printed
        if(this->Nodes[Giveindex].idNum == GiveIDNum)
        {
            cout << "Found at index - " << Giveindex << endl;
            return Giveindex;
        }
        queue.pop_front();

        for(it = Nodes[Giveindex].adjList.begin(); it != Nodes[Giveindex].adjList.end(); it++)
        {
            if(!visited[it->index])
            {
                visited[it->index] = true;
                queue.push_back(it->index);
            }
        }

    }
    return -1;
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

void Graph::allPathsBetweenPairOfNodesWrap()
{
    string tempid1,tempid2;
    cout << "Enter IdNumber Of Person 1" << endl;
    cin >> tempid1;
    int index1 = dfsSearchWrapID(tempid1);
    if(index1 == -1)
    {
        cout << "Invalid IdNumber" << endl;
        cout << "Sorry Not Found On Network" << endl;
        return;
    }
    cout << "Enter IdNumber Of Person 2" << endl;
    cin >> tempid2;
    int index2 = dfsSearchWrapID(tempid2);
    if(index2 == -1)
    {
        cout << "Invalid IdNumber" << endl;
        cout << "Sorry Not Found On Network" << endl;
        return; 
    }

    this->allPathsBetweenPairOfNodes(index1,index2);

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
        cout << "Intermediate Connections From Person1 To Person2 are --> " << endl;
        for(int i = 1; i < pathIndex - 1; i++)
        {
            cout << "------------------------------------------------------------------------" << endl;
            cout << this->Nodes[path[i]].fname << " " << this->Nodes[path[i]].lname << endl;
            cout << "IDNUM --> "<< this->Nodes[path[i]].idNum << endl;
            cout << "------------------------------------------------------------------------" << endl;
            //cout << path[i] << " ";
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

void Graph::addEdge(string selfkey,string tokey)
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
    //cout << "hi2" << endl;
    while(wt < 0 || wt > 101)
    {
        //cout << "hi3" << endl;
        cout << "How nicely Do you know the person you are connecting...on a scale of 0 - 100" << endl;
        cout << "0 - least | 100 - most" << endl;
        cin  >> wt;
    }

    //both ids are found so add the edge
    this->Nodes[selfindex].addEdgeByIndex(toindex,100 - wt,*this);
}


void Graph::findEducationMates(int Giveindex)
{
    if(Giveindex < 0 || Giveindex > this->Nodes.size())
    {
        cout << "invalid index" << endl;
        return;//invalid index
    }
    int fixedindex = Giveindex;

    bool* visited = new bool[this->Nodes.size()];
    //memset(visited,false,this->Nodes.size()*sizeof(bool));
    for(int i = 0; i < this->Nodes.size(); i++)
    {
        visited[i] = false;
    }

    list<int> queue;
    visited[Giveindex] = true;

    queue.push_back(Giveindex);

    list<ListData>::iterator it;
    while(!queue.empty())
    {
        Giveindex = queue.front();
        //later appropriate data should be printed
        if(Giveindex != fixedindex)
        {
            list<educatinalInstitute>::iterator edptr1,edptr2;
            for(edptr1 = this->Nodes[Giveindex].EducationList.begin(); edptr1 != this->Nodes[Giveindex].EducationList.end(); edptr1++)
            {
                for(edptr2 = this->Nodes[fixedindex].EducationList.begin(); edptr2 != this->Nodes[fixedindex].EducationList.end(); edptr2++)
                {
                    if(edptr1->InstituteName == edptr2->InstituteName)
                    {
                        cout << "You may know - " << this->Nodes[Giveindex].fname << " " << this->Nodes[Giveindex].lname << endl;
                        cout << "From - " << edptr1->InstituteName << " as you were in same Educational Institute" << endl;
                        cout << "\n" << endl;
                    }
                }
                
            }
        }
        queue.pop_front();

        for(it = Nodes[Giveindex].adjList.begin(); it != Nodes[Giveindex].adjList.end(); it++)
        {
            if(!visited[it->index])
            {
                visited[it->index] = true;
                queue.push_back(it->index);
            }
        }

    }
}


void Graph::checkConnectionWrap()
{
    if(this->Nodes.size() < 1)
    {
        cout << "Network Contains Very Few People. Bye!" <<endl;
        return;
    }

    int direct = 0;

    string id1,id2;
    int index1 = -1,index2 = -1;
    cout << "Enter the First Person IDNUM to check connection for - " << endl;
    while(index1 == -1)
    {
        cout << "Enter a valid ID - " << endl;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        fflush(stdin);
        cin >> id1;
        index1 = this->breadthFirstSearchIDNum(0,id1);
    }
    
    cout << "Enter the Second Person IDNUM to check connection for - " << endl;
    while(index2 == -1)
    {
        cout << "Enter a valid ID - " << endl;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        fflush(stdin);
        cin >> id2;
        index2 = this->breadthFirstSearchIDNum(index1,id2);
        //searching from the found index to get the person quickly if the are connected
    }

    if(index1 == index2)
    {
        cout << "Great! You Found Same Person! but there's no connection! no self Loops!" << endl;
        return;
    }

    list<ListData>::iterator it;
    for(it = this->Nodes[index1].adjList.begin(); it != this->Nodes[index1].adjList.end(); it++)
    {
        if(it->index == index2)
        {
            cout << "Person 2 - " << this->Nodes[index2].fname << " " << this->Nodes[index2].lname << endl;
            cout << "is directly connected to the Person 1" << this->Nodes[index1].fname << " " << this->Nodes[index1].lname << endl;
            direct = 1;
        }
    }
    if(direct == 0)
    {
        cout << "The Person 1 " << this->Nodes[index1].fname << " " << this->Nodes[index1].lname << " is Not directly connected to " << endl;
        cout << "Person 2" << this->Nodes[index2].fname << " " << this->Nodes[index2].lname << endl;
    }
    
    this->allPathsBetweenPairOfNodes(index1,index2);

}


void Graph::showCompleteNetwork()
{
    string id1;
    int index1 = -1;
    cout << "Enter the Person IDNUM to GET Network for --> " << endl;
    while(index1 == -1)
    {
        cout << "Enter a valid ID - " << endl;
        cin >> id1;
        index1 = this->breadthFirstSearchIDNum(0,id1);
    }

    cout << "The complete NETWORK CONNECTIONS for the given IDNUM are -->" << endl;

    list<ListData>::iterator it;
    for(it = this->Nodes[index1].adjList.begin(); it != this->Nodes[index1].adjList.end(); it++)
    {
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
        cout << this->Nodes[it->index].fname << " " << this->Nodes[it->index].lname << endl;
        cout << "IDNUM - " << this->Nodes[it->index].idNum << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }
}


void Graph::listPotentialGroupsOnHobbies()
{
    unordered_map<string,list<int>> hbyMap;

    vector<Data>::iterator it;
    list<string>::iterator jt;
    list<int>::iterator ptr;

    for(it = this->Nodes.begin(); it != this->Nodes.end(); it++)
    {
        for(jt = it->hobbies.begin(); jt != it->hobbies.end(); jt++)
        {
            hbyMap[*jt].push_back(it->index);
        }
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "----------------------------POTENTIAL HOBBY GROUPS-----------------------------" << endl;
    unordered_map<string,list<int>>::iterator i;
    for(i = hbyMap.begin(); i != hbyMap.end(); i++)
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "---------------------------------Hobby " << i->first <<"-----------------------" << endl;
        for(ptr = i->second.begin(); ptr != i->second.end(); ptr++)
        {
            cout << "-------------------------------------------------------------------------------" << endl;
            cout << this->Nodes[*ptr].fname << " " << this->Nodes[*ptr].lname << endl;
            cout << this->Nodes[*ptr].idNum << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
        }
    }
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
    Graph G;
    int choice = 0;
    int graphChoice = -1;
    string idTemp;
    string tempIDforRemove;
    cout << "=======================================================================================================================" << endl;
    cout << "=========================================== WELCOME TO MY VERSION OF LINKEDIN =========================================" << endl;
    cout << "=======================================================================================================================" << endl;

    while(choice == 0)
    {
        cout << "============================Enter The Following Numbers For The Following Options======================================" << endl;
        cout << "==================== 1 - Viewing people On The Network | 2 - Add An Account ===========================================" << endl;
        cout << "==================== 3 - Shortest Path To Know Someone | 4 - Login To Your Account ====================================" << endl;
        cout << "============ 5 - Most Close Connections On The Network | 6 - To Know All Ways To Reach From Person 1 To Person 2 ======" << endl;
        cout << "==== 7 - Show Complete Network For A perticular Person | 8 - Maximum Degree Of Separation On The Network ==============" << endl;
        cout << "==================9 - List Potential groups On Hobbies | 10 - Delete Account ==========================================" << endl;
        cout << "=================================================== 11 - Quit =========================================================" << endl;

        cin >> graphChoice;

        switch (graphChoice)
        {
        case 1:
            {
                G.dfsTraversalWrap();
            }
            break;

        case 2:
            {
                G.addNodeWrap();
            }
            break;
        case 3:
            {
                G.shortestPathToKnowEveryOne();
            }
            break;
        case 4:
            {
                cout << "Enter IdNumber Of Person 1" << endl;
                cin >> idTemp;
                int fineChoice = -1;
                int index1Main = G.dfsSearchWrapID(idTemp);
                if(index1Main == -1)
                {
                    cout << "Invalid IdNumber" << endl;
                    cout << "Sorry Not Found On Network" << endl;
                    break;
                }
                int continueTerm = 1;
                while(continueTerm == 1)
                {
                    cout << "================================Enter The Number corresponding To Following Options==========================" << endl;
                    cout << "========================= 1 - To Get Connected To SomeOne | 2 - To View Your Connections ====================" << endl;
                    cout << "==== 3 - View Shortest Way To Get In Contact With SomeOne | 4 - View Latest Connections For Your Network ====" << endl;
                    cout << "================================ 5 - Find Education Mates | 6 - Update Data =================================" << endl;
                    cout << "==================================== 7 - RemoveConnection | 8 - Logout ======================================" << endl;
                    cin >> fineChoice;
                    if(fineChoice == 1)
                    {
                        G.Nodes[index1Main].getConnected();
                    }
                    else if(fineChoice == 2)
                    {
                        G.Nodes[index1Main].showNetwork();
                    }
                    else if(fineChoice == 3)
                    {
                        G.Nodes[index1Main].shortestPathToKnowSomeone();
                    }
                    else if(fineChoice == 4)
                    {
                        G.Nodes[index1Main].listLatestConnectionsForMyNetwork();
                    }
                    else if(fineChoice == 5)
                    {
                        G.Nodes[index1Main].findEducationMates();
                    }
                    else if(fineChoice == 6)
                    {
                        G.Nodes[index1Main].updateData();
                    }
                    else if(fineChoice == 7)
                    {
                        cout << "Enter IdNum to remove Connection for - " << endl;
                        cin >> tempIDforRemove;
                        list<ListData>::iterator rmptr;
                        for(rmptr = G.Nodes[index1Main].adjList.begin(); rmptr != G.Nodes[index1Main].adjList.end(); rmptr++)
                        {
                            if(rmptr->idNum == tempIDforRemove)
                            {
                                break;
                            }
                        }
                        if(rmptr != G.Nodes[index1Main].adjList.end())
                        {
                            G.Nodes[index1Main].deleteEdgeByKey(rmptr->idNum);
                        }
                        else
                        {
                            cout << "Invalid IDNum" << endl;
                        }
                        
                    }
                    else if(fineChoice == 8)
                    {
                        continueTerm = 0;
                    }
                    else
                    {
                        cout << "Invalid Choice" << endl;
                    }
                }
            }
            break;
        case 5:
            {
                G.MSTprims();
            }
            break;
        case 6:
            {
                G.allPathsBetweenPairOfNodesWrap();
            }
            break;
        case 7:
            {
                G.showCompleteNetwork();
            }
            break;
        case 8:
            {
                G.AllPairShortestPath();
            }
            break;
        case 9:
            {
                G.listPotentialGroupsOnHobbies();
            }
            break;
        case 10:
            {
                G.deleteNodeByKeyWrap(); 
            }
            break;
        case 11:
            {
                cout << "Thank You" << endl;
                choice = 1; 
            }
            break;
        default:
            break;
        }
    }

    return 0;
}
