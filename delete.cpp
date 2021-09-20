#include "delete.hpp"

#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef void (Delete::*commandsMethod) (vector<string> data);

Delete::Delete(Utrip* utrip_, User* user_):Command(utrip_,user_){
}
void Delete::doCommand(vector<string> data)
{
    map<string, commandsMethod> commands;
    commands[FILTERS_KEYWORD] = &Delete::filters;
    commands[RESERVES_KEYWORD] = &Delete::reserves;
    try{
      auto cm_itr = commands.find(data[1]);
      if(cm_itr == commands.end())
      {
        throw NOT_FOUND_MSG;
      }
      (this->*commands[data[1]]) (data);

    }
    catch(const char* msg){
      cout << msg << endl;
    }
}
void Delete::filters(vector<string> data)
{
  isUserLogin();
  user->deleteFilters();
  throw OK_MSG;
}
void Delete::reserves(vector<string> data){
  isUserLogin();
  int id = stoi(data[4]);
  user->deleteReservation(id); 
  throw OK_MSG;
}