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
  cout<<"Name:"<<act_name<<", duration:"<<act_duration<<", predecessors:"<<act_predecessors<<", Cost:"<<act_cost<<", Min Start:"<<min_start<<", Min End: "<< min_end<<endl;
}

ActivityNode::ActivityNode(string name, int duration, string pred, int cost)
{
  act_name = name;
  act_duration = duration;
  act_predecessors = pred;
  act_cost = cost;

  //initialize the values for duration comparision
  min_start = min_end = max_start = max_end = -1;
}

ActivityNode::ActivityNode()
{
  //empty constructor
}

void ActivityNode::AddPredecessor(ActivityNode *pred)
{
  act_vector_pred.push_back(pred);
}

void ActivityNode::AddSuccessor(ActivityNode *succ)
{
    act_vector_succ.push_back(succ);
}
