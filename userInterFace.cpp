#include "userInterFace.hpp"
#include "command.hpp"
#include<iostream>
#include<fstream>
#include<sstream>

#include"post.hpp"
#include"get.hpp"
#include"delete.hpp"

#define POST_COMMANDS "POST"
#define GET_COMMANDS "GET"
#define DELETE_COMMANDS "DELETE"
#define COMMANDS_TYPE 0


const char delimitersFile = ',';
const char delimitersLine = ' ';

using namespace std;

vector<string> splitString(string line, char delimiter)
{
  stringstream temp(line);
  vector<string> lines;
  string seplited;
  while (getline(temp, seplited, delimiter))
  {
    lines.push_back(seplited);
  }
  return lines;
}
UserInterface::UserInterface()
{
  Utrip* utrip_ = new Utrip();
  utrip = utrip_;
  user = NULL;
}
double stodFunction(string s)
{
  return stod(s);
}
void UserInterface::readData(string hotelsDataAddress, string ratingsDataAddress)
{
  string hotelsLine, ratingsLine;
  fstream hotelsFile, ratingsFile;
  hotelsFile.open(hotelsDataAddress);
  ratingsFile.open(ratingsDataAddress);
  getline(hotelsFile,hotelsLine);
  getline(ratingsFile,ratingsLine);
  while (!hotelsFile.eof())
  {
    getline(hotelsFile, hotelsLine);
    getline(ratingsFile, ratingsLine);
    if (hotelsLine.length() >= 1)
    {
      vector<string> hotelData = splitString(hotelsLine, delimitersFile);
      vector<string> ratingsData = splitString(ratingsLine, delimitersFile);
      ratingsData.erase(ratingsData.begin());
      vector<double> averageRatings(ratingsData.size());
      transform(ratingsData.begin(), ratingsData.end(), averageRatings.begin(), stodFunction);
      utrip->addHotel(hotelData, averageRatings);
    }
    else
    break;
  }
  
}
void UserInterface::getCommands(string command)
{
  vector<string> commands = splitString(command, delimitersLine);
  if (commands[COMMANDS_TYPE] == POST_COMMANDS)
  {
    Post* post = new Post(utrip,user);
    user = post->doCommand(commands);
  }
  else if(commands[COMMANDS_TYPE] == GET_COMMANDS)
  {
    Get* get = new Get(utrip,user);
    get->doCommand(commands);
  }
  else if(commands[COMMANDS_TYPE] == DELETE_COMMANDS)
  {
    Delete* del = new Delete(utrip,user);
    del->doCommand(commands);
  }
  else
  {
    cout << BAD_REQUEST_MSG << endl;
  }
}
