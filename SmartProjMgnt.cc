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
      map[activity[0]] = new ActivityNode(activity[0], std::stoi(activity[1], nullptr), activity[2], std::stoi(activity[3], nullptr));
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
  ComputePERTValsRwnd();
}

void SmartProjMgnt::ComputePERTValsFwd()
{
  //Temporary string,bool hash-table to store results
  unordered_map<string, bool> map_results;
  //Iterate through the starting list and update min_start and min_end values
  for (vector<ActivityNode*>::iterator it_vect = starting_points.begin() ; it_vect != starting_points.end(); ++it_vect)
  {
    (*it_vect)->SetMinStart(0);
    (*it_vect)->SetMinEnd((*it_vect)->GetActivityDuration()); 
    map_results[(*it_vect)->GetActivityName()] = true;
  }
  
  //Iterate through the map: for each, check their predecessors' values are updated
  while(map_results.size() != map.size())
  {
    for(unordered_map<string, ActivityNode*>::iterator it_map = map.begin(); it_map != map.end(); ++it_map)
    {
      if(map_results.find(it_map->first) != map_results.end() && map_results[it_map->first])
	break;

      //Check if the predecessors have valid min_end values
      vector<ActivityNode*> predecessors = it_map->second->GetPredecessors();
      int end = -1;
      for (vector<ActivityNode*>::iterator it_vect = predecessors.begin(); it_vect != predecessors.end(); ++it_vect)
      {
	//Find the maximum in min_end duration, thats the start date
	if((*it_vect)->GetMinEnd() > end)
	  end = (*it_vect)->GetMinEnd();
      }
      
      if(end != -1)
      {
	//Add the activity duration 
	it_map->second->SetMinStart(end);
	it_map->second->SetMinEnd(end + it_map->second->GetActivityDuration());
	map_results[it_map->first] = true;
      }
    } //End of For
  } //End of While
  cout<<"End of PERT fwd result calc"<< endl;
}

void SmartProjMgnt::ComputePERTValsRwnd()
{

}
