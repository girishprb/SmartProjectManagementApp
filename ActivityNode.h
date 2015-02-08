/*
  File Name: ActivityNode.h
  Author: Girish Prabhu H
  Date: Jan 25 2015
  Description:

 */

#ifndef ACTIVITY_NODE_H
#define ACTIVITY_NODE_H
#include <string>
#include <vector>

class ActivityNode
{
private:
  std::string act_name;
  std::string act_description;
  float act_duration;
  std::string act_predecessors;
  int act_cost;
  std::vector<ActivityNode*> act_vector_pred;
  std::vector<ActivityNode*> act_vector_succ;
  int min_start, min_end, max_start, max_end;
  std::string act_skillset;
public:
  ActivityNode();  
  ~ActivityNode();
  ActivityNode(std::string name, float duration, std::string pred, std::string desc, std::string skillset, int cost=0);
  void Represent();
  void AddPredecessor(ActivityNode *pred);
  void AddSuccessor(ActivityNode *succ);

  //Getter functions
  std::string GetStrPredecessor() { return act_predecessors; }
  int GetNormalCost() { return act_cost; }
  float GetActivityDuration() {return act_duration; }
  int GetMinStart() { return min_start; }
  int GetMinEnd() { return min_end; }
  int GetMaxStart() { return max_start; }
  int GetMaxEnd() { return max_end; }
  std::string GetActivityName() { return act_name; }
  std::vector<ActivityNode*> GetPredecessors() { return act_vector_pred; }
  std::vector<ActivityNode*> GetSuccessors() { return act_vector_succ; }

  //Setter functions
  void SetMinStart(int start){ min_start = start; }
  void SetMinEnd(int end){ min_end = end; }
  void SetMaxStart(int start){ max_start = start; }
  void SetMaxEnd(int end){ max_end = end; }
};

#endif
