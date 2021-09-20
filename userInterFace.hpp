#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP "USERINTERFACE_HPP"

#include "utrip.hpp"
#include "user.hpp"

class UserInterface{
public:

  UserInterface();
  void readData(std::string hotelsDataAddress, std::string ratingsDataAddress);
  void getCommands(std::string command);
private:

  Utrip* utrip;
  User* user;
};

#endif
