#ifndef UTRIP_HPP
#define UTRIP_HPP "UTRIP_HPP"

#include "hotel.hpp"
#include "user.hpp"
#include <vector>
#include "defines.hpp"

class Utrip{

public:
  void addHotel(std::vector<std::string> hotelsData, std::vector<double> hotelRatings);
  User* addUser(std::vector<std::string> usersData);
  User* logInUser(std::string username, std::string password);
  bool isThisEmailExistsInYourUsers(std::string email);
  bool isThisUsernameExistsInYourUsers(std::string username);
  void chargeUsersAccount(User* user, std::string money);
  std::vector<Hotel*>  doFilters(std::vector<Filter*> filters);
  Hotel* getHotel(std::string id);
  std::vector<Room*> reserve(std::string hotelId, std::string type, int quantity, int checkIn, int checkOut, User* user);
private:
  std::vector<Hotel*> hotels;
  std::vector<User*> users;

};

#endif
