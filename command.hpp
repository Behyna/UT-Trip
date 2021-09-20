#ifndef COMMAND_HPP
#define COMMAND_HPP "COMMAND_HPP"

#include"utrip.hpp"
#include<vector>
#include<string>

class Command{

public:

  Command(Utrip* utrip_, User* user_);
  virtual bool isUserLogin();
protected:

  Utrip* utrip;
  User* user;

};

#endif
