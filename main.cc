/*
  File Name: main.cc
  Author: Girish Prabhu H
  Date: Jan 25 2015
  Description:
 */
#include "SmartProjMgnt.h"
using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    cout<<"Usage: smartpm <activity_file> <resources_file>"<<endl;
    return -1;
  }
  
  // Read the activity input file
  SmartProjMgnt::Instance()->ReadActivity(argv[1]);
  SmartProjMgnt::Instance()->PrintContents();
  SmartProjMgnt::Instance()->DeleteAll();
  return 0;
}
