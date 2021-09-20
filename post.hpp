#ifndef POST_HPP
#define POST_HPP "POST_HPP"

#include "command.hpp"

class Post:public Command{

public:
  Post(Utrip* utrip_, User* user_);
  User* doCommand(std::vector<std::string> command);

private:
  bool isThisUsernameExist(std::string enteredUsername);
  bool isThisEmailExist(std::string entredEmail);
  void signUp(std::vector<std::string> data);
  void logIn(std::vector<std::string> data);
  void logOut(std::vector<std::string> data);
  void wallet(std::vector<std::string> data);
  void filters(std::vector<std::string> data);
  void doFilters(std::vector<std::string> data);
  void reserves(std::vector<std::string> data);
  void comments(std::vector<std::string> data);
  void ratings(std::vector<std::string> data);
  void defaultPriceFilter(std::vector<std::string> data);
  void sort(std::vector<std::string> data);
  void manualWeights(std::vector<std::string> data);

}; 

#endif
