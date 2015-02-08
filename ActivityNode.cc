/*
  File Name: ActivityNode.cc
  Author: Girish Prabhu H
  Date: Jan 24 2015
  Description:

 */

#include<iostream>
#include "ActivityNode.h"

using namespace std;

void ActivityNode::Represent()
{
  cout<<"Name:"<<act_name<<endl;
  cout<<"Project Duration:"<<act_duration<<endl;
  cout<<"Normal Cost:"<<act_cost<<endl;
  cout<<"Min Start:"<<min_start<<endl;
  cout<<"Min End:"<< min_end<<endl;
  cout<<"Max Start:"<<max_start<<endl;
  cout<<"Max End:"<<max_end<<endl;
  cout<<"Predecessors:";
  //loop and print the Predecessors
  if(act_vector_pred.size() == 0)
    cout<<"-";
  else
    for (vector<ActivityNode*>::iterator it_vect = act_vector_pred.begin(); it_vect != act_vector_pred.end(); ++it_vect)
      cout<<(*it_vect)->GetActivityName()<<" ";

  //loop and print the Successors
  cout<<endl<<"Succcessors:";
  for (vector<ActivityNode*>::iterator it_vect = act_vector_succ.begin(); it_vect != act_vector_succ.end(); ++it_vect)
    cout<<(*it_vect)->GetActivityName()<<" ";

  cout<<endl<<endl;
}

ActivityNode::ActivityNode(string name, float duration, string pred, string desc, string skillset, int cost)
{
  act_name = name;
  act_duration = duration;
  act_predecessors = pred;
  act_cost = cost;
  act_skillset = skillset;
  act_description = desc;
  //initialize the values for duration comparision
  min_start = min_end = max_start = max_end = -1;
}

ActivityNode::ActivityNode()
{
  //empty constructor
}

//Adds a predecessor to the list
void ActivityNode::AddPredecessor(ActivityNode *pred)
{
  if(pred)
    act_vector_pred.push_back(pred);
}

//Adds a node to Successor Vector 
void ActivityNode::AddSuccessor(ActivityNode *succ)
{
  if(succ)
    act_vector_succ.push_back(succ);
}

//Destructor: Delete memory allocated on the heap
ActivityNode::~ActivityNode()
{
  // if(!act_skillset)
  //   delete act_skillset;
}
