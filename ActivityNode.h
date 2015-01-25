/*
  File Name: ActivityNode.h
  Author: Girish Prabhu H
  Date: Jan 25 2015
  Description:

 */

#ifndef ACTIVITY_NODE_H
#define ACTIVITY_NODE_H
#include <string>

class ActivityNode
{
private:
  std::string act_name;
  int act_duration;
  std::string act_predecessors;
  int act_cost;

public:
  ActivityNode();  
  ActivityNode(std::string name, int duration, std::string pred, int cost);
  void Represent();
};

#endif
