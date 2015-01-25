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
#include <stddef.h>
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
