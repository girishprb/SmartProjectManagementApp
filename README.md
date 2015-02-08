SmartProjectManagementApp

Format for the activities file
-----------------------------
Activity_id|Duration|Predecessor|Activity_Name|Req_SkillSets|

Req_SkillSets: comma separated possible skill sets
Predecessors: comma separated activity id

Format for the resources file
-----------------------------
Resource_Name|Resouce_type|Rate


Progress so far
--------------
1. Read from the Activity file and create the graph
2. Add Finish and Start nodes to the graph //Not sure if this required yet
3. Traverse the graph and fill in the min and max start/end dates
4. Compute the max time required for the project
5. Identify the critical path nodes

To Do
---------------
1. Read the crashing possibilities for each activity
2. Logic to determine the crashing process and find the best solution
3. Take resources and skillsets into consideration during the crashing

