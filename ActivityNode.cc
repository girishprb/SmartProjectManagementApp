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
   cout<<"Name:"<<act_name<<", duration:"<<act_duration<<", predecessors:"<<act_predecessors<<", Cost:"<<act_cost<<endl;
}

ActivityNode::ActivityNode(string name, int duration, string pred, int cost)
{
  act_name = name;
  act_duration = duration;
  act_predecessors = pred;
  act_cost = cost;
}

ActivityNode::ActivityNode()
{
  //empty constructor
}
