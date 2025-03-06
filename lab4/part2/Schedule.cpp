#include <iostream>
#include <map>
#include "Schedule.h"

using namespace std;

Schedule::Schedule(string name)
{
    mName = name;
}

bool Schedule::dropCourse(std::string name)
{
    // TO DO: if the course was not already in the map, return false
    // otherwise, remove it from the map and return true!
    if(courseMap.find(name) != courseMap.end()){
        courseMap.erase(name);
        return true;
    }

    return false;
}

bool Schedule::addCourse(Course* c)
{
    // TO DO: if the course was already in the map, return false
    // otherwise, add it to the map and return true!
    if(courseMap.find(c->getCourseName()) == courseMap.end()){
        courseMap.insert(pair<string, Course*>(c->getCourseName(), c));
        return true;
    }

    return false;
}

void Schedule::printAllAssignments()
{
    // TO DO: print out the name of each course, followed by the set of assignments.
    // for each assignment, display its name, its type (essay vs hw vs exam), and whether or not it was completed.
    // formatting is up to you, but make sure it's easy to read!

    for(std::map<string, Course*>::iterator it = courseMap.begin(); it != courseMap.end(); it++){
        cout << it->first << endl;
        cout << "Assignments: " << endl;
        set<Assignment*> assignmentSet = it->second->getAssignmentSet();
        for(set<Assignment*>::iterator it2 = assignmentSet.begin(); it2 != assignmentSet.end(); it2++){
            cout << "Name: " << (*it2)->getName() << endl;
            cout << "Type: " << (*it2)->getType() << endl;
            cout << "Completed: " << ((*it2)->isComplete() ? "Yes" : "No") << endl;
        }
    }
    
}

std::map<std::string, Course*> Schedule::getCourses()
{
    return courseMap;
}