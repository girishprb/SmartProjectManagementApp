/*
  File Name: SmartProjMgnt.h
  Author: Girish Prabhu H
  Date: Jan 24 2015
  Description:
 */

#ifndef SMART_PROJ_MGNT_H
#define SMART_PROJ_MGNT_H
#include <string>
//#include <stdef>
#include <vector>
#include <unordered_map>
#include "ActivityNode.h"

//Singleton class
class SmartProjMgnt
{
  //Global Hash table
public:
  static SmartProjMgnt* Instance();
  void AddToTable(std::string act_name, ActivityNode *act_ptr);
  void PrintContents();
  void DeleteAll();
  void CreateLinks();
  ActivityNode *GetActivity(std::string act_name);
  void ReadActivity(char * fileName);
  void ComputePERTVals();

private:
  std::unordered_map<std::string, ActivityNode *> map;
  static SmartProjMgnt * m_pInstance;
  SmartProjMgnt(){};               
  SmartProjMgnt(SmartProjMgnt const&){};           
  SmartProjMgnt& operator=(SmartProjMgnt const&){ };  
  void ComputePERTValsFwd();
  void ComputePERTValsRwnd();
  std::vector<ActivityNode*> starting_points;
};
#endif
