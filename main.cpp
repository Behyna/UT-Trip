#include <iostream>
#include "userInterFace.hpp"
#include "utrip.hpp"
using namespace std;

int main(int argc, char *argv[])
{
  UserInterface* userInterface = new UserInterface();
  userInterface->readData(argv[1], argv[2]);
  while(true)
  {
    string command;
    getline(cin, command);
    userInterface->getCommands(command);
  }
}
