/*
  File Name: SmartProjMgnt.cc
  Author: Girish Prabhu H
  Date: Jan 24 2015
  Description:
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Utils.h"
#include "SmartProjMgnt.h"
#include "ActivityNode.h"

using namespace std;

//-----------Utils code---------------------

//Function Code referred from stackoverflow
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}

//Function Code referred from stackoverflow
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> split(const std::string &s, char delim)  
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
//-----------End of Utils-------------------

//Initializing the static member
SmartProjMgnt *SmartProjMgnt::m_pInstance = NULL;

SmartProjMgnt* SmartProjMgnt::Instance()
{
  if(!m_pInstance)
  {
    m_pInstance = new SmartProjMgnt;
  }
  return m_pInstance;
}

ActivityNode * SmartProjMgnt::GetActivity(string act_name)
{
  return map[act_name];
}


void SmartProjMgnt::DeleteAll()
{
  for(unordered_map<string, ActivityNode*>::iterator iter = map.begin(); iter != map.end(); ++iter)
  {
    delete iter->second;
  }
}

void SmartProjMgnt::AddToTable(std::string act_name, ActivityNode *act_ptr)
{
  //Add to the hash table
  map[act_name] = act_ptr;
}

void SmartProjMgnt::PrintContents()
{
  //iterator for map
  for(unordered_map<string, ActivityNode*>::iterator iter = map.begin(); iter != map.end(); ++iter)
  {
    iter->second->Represent();
  }
}

void SmartProjMgnt::ReadActivity(char * fileName)
{
  ifstream file_act (fileName);
  string line;
  std::vector<std::string> activity;
  if(file_act.is_open())
  {
    while(getline(file_act, line))
    {
      //Split string based on |
      activity = split(line, '|');
      //Create Nodes per line
      //ActivityNode(string id, float duration, std::string pred, std::string desc, std::string skillset, int cost);
      map[activity[0]] = new ActivityNode(activity[0],
					  std::stof(activity[1], nullptr), 
					  activity[2], 
					  activity[3],
					  activity[4]);
    }
    
    //Add dependencies once all nodes are created
    file_act.close();
  }
}

void SmartProjMgnt::CreateLinks()
{
  //Iterate through the string predecessors for all activities 
  std::vector<std::string> vector_pred;
  string str_pred;
  for(unordered_map<string, ActivityNode*>::iterator it_map = map.begin(); it_map != map.end(); ++it_map)
  {
    vector_pred = split(it_map->second->GetStrPredecessor(), ',');
    //For each item, add to neighbor vector accordingly
    for (vector<string>::iterator it_vect = vector_pred.begin() ; it_vect != vector_pred.end(); ++it_vect)
    {
      if(it_vect->compare("-")!=0)
      {
	//Add Predecessor
	it_map->second->AddPredecessor(map[*it_vect]);

	//Add Successor
	map[*it_vect]->AddSuccessor(it_map->second);
      }
      else
      {
	//If starting point, add to the vector list
	starting_points.push_back(it_map->second);
      }
    }
  }
}

void SmartProjMgnt::ComputePERTVals()
{
  ComputePERTValsFwd();
  AddFinishNode();
  ComputePERTValsRwnd();
}

void SmartProjMgnt::ComputePERTValsFwd()
{
  //Temporary string,bool hash-table to store results
  unordered_map<string, bool> map_results;
  int total_duration = 0;
  //Iterate through the starting list and update min_start and min_end values
  for (vector<ActivityNode*>::iterator it_vect = starting_points.begin() ; it_vect != starting_points.end(); ++it_vect)
  {
    (*it_vect)->SetMinStart(0);
    (*it_vect)->SetMinEnd((*it_vect)->GetActivityDuration()); 
    if(total_duration < (*it_vect)->GetMinEnd())
      total_duration = (*it_vect)->GetMinEnd();
    map_results[(*it_vect)->GetActivityName()] = true;
  }
  
  //Iterate through the map: for each, check their predecessors' values are updated
  while(map_results.size() != map.size())
  {
    for(unordered_map<string, ActivityNode*>::iterator it_map = map.begin(); it_map != map.end(); ++it_map)
    {
      if(map_results.find(it_map->first) != map_results.end() && map_results[it_map->first])
	continue;

      //Check if the predecessors have valid min_end values
      vector<ActivityNode*> predecessors = it_map->second->GetPredecessors();
      int end = INVALID_DURATION_VAL;
      for (vector<ActivityNode*>::iterator it_vect = predecessors.begin(); it_vect != predecessors.end(); ++it_vect)
      {
	//Find the maximum in min_end duration, thats the start date
	if((*it_vect)->GetMinEnd() > end)
	  end = (*it_vect)->GetMinEnd();
	else if((*it_vect)->GetMinEnd() == INVALID_DURATION_VAL)
	{
	  end = INVALID_DURATION_VAL;
	  break;
	}
      }
      
      if(end != INVALID_DURATION_VAL)
      {
	//Add the activity duration 
	it_map->second->SetMinStart(end);
	it_map->second->SetMinEnd(end + it_map->second->GetActivityDuration());
	map_results[it_map->first] = true;
	if(total_duration < it_map->second->GetMinEnd())
	  total_duration = it_map->second->GetMinEnd();
      }
    } //End of For
  } //End of While
  cout<<"Total Project duration: "<<total_duration<<endl;
  proj_total_duration = total_duration;
}

void SmartProjMgnt::ComputePERTValsRwnd()
{
  unordered_map<string, bool> map_results;
  //Start from the predecessor of finish
  map_results["fin"] = true;
  //Iterate through the map: for each, check if their sucessors' values are updated
  while(map_results.size() != map.size())
  {
    for(unordered_map<string, ActivityNode*>::iterator it_map = map.begin(); it_map != map.end(); ++it_map)
    {
      if(map_results.find(it_map->first) != map_results.end() && map_results[it_map->first])
	continue;

      //Check if the successors have valid min_end values
      vector<ActivityNode*> successors = it_map->second->GetSuccessors();
      int start = MAX_DURATION_VAL;
      for (vector<ActivityNode*>::iterator it_vect = successors.begin(); it_vect != successors.end(); ++it_vect)
      {
	//Find the min in max_start duration, thats the end date
	if((*it_vect)->GetMaxStart() != INVALID_DURATION_VAL && (*it_vect)->GetMaxStart() < start)
	  start = (*it_vect)->GetMaxStart();
	//If any of the successor values not computed, skip
	else if((*it_vect)->GetMaxStart() == INVALID_DURATION_VAL)
	{
	  start = MAX_DURATION_VAL;
	  break;
	}
      }
      
      if( start != MAX_DURATION_VAL)
      {
	//Add the activity duration 
	it_map->second->SetMaxEnd(start);
	it_map->second->SetMaxStart(start - it_map->second->GetActivityDuration());
	map_results[it_map->first] = true;
      }
    } //End of For
  } //End of While
}

void SmartProjMgnt::AddFinishNode()
{
  vector<ActivityNode*> end_points;
  //Find all the end points with no successors
  for(unordered_map<string, ActivityNode*>::iterator it_map = map.begin(); it_map != map.end(); ++it_map)
  {
    if(it_map->second->GetSuccessors().size() == 0)
    {
      end_points.push_back(it_map->second);
    }
  }

  //Add Finish node to the Table
  map["fin"] = new ActivityNode("fin", 0, "", "Last Node", "None", 0);

  //For all end points 
  for (vector<ActivityNode*>::iterator it_vect = end_points.begin(); it_vect != end_points.end(); ++it_vect)
  {
    //Let all the end points be fin's predecessors
    map["fin"]->AddPredecessor(*it_vect);

    //Let all the end points have finish as their common successor
    (*it_vect)->AddSuccessor(map["fin"]);
  }

  //Update the duration for fin
  map["fin"]->SetMinStart(proj_total_duration);
  map["fin"]->SetMinEnd(proj_total_duration);
  map["fin"]->SetMaxStart(proj_total_duration);
  map["fin"]->SetMaxEnd(proj_total_duration);
}
