#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iostream>

#include "filter.hpp"
#include "defaultPriceFilter.hpp"
#include "reservation.hpp"
#include "defines.hpp"

class User{
public:

  User(std::string usersname, std::string userspassword, std::string usersemail);
  bool checkingUsersInfo(std::string enteredEmail, std::string enteredPassword);
  bool isThisYourEmail(std::string eteredEmail);
  bool isThisYourUserName(std::string enteredUsername);
  void chargeMyAccount(int money);
  void setFilters(Filter* newFilter);
  std::vector<Filter*> getFilters() {return filters;};
  void payCredit(int money);
  void addReserve(std::string hotelId, std::string type, int quantity, int cost,
                  int checkIn, int checkOut, std::vector<Room*> rooms);
  std::vector<Reservation*> getReservations();
  std::vector<int> getAccountTurnover(int count);
  void deleteFilters();
  void deleteReservation(int id);
  std::string getUsername(){return username;};
  void setDefaultPriceFilter(bool state);
  bool prepareDefaultPriceFilter();
  void setSortParams(std::string property, std::string order);
  std::pair<std::string, std::string> getSortParams(){return sortParams;};
  void setManualWeights(bool active, std::vector<double> weights);
  bool isManualWeightsActive(){return manualWeightsActive;};
  std::vector<double> getWeights();
  std::vector<double> getEstimatedWeights();
  std::vector<double> getManualWeights(){return manualWeights;};
  void addRatings(std::vector<double> ratings);
  std::vector<std::vector<double>> getAllRatings(){return allRatings;};
  bool insufficientRatings();

private:
  int nextReservationId;
  std::string username;
  std::string password;
  std::string email;
  int credit;
  std::vector<int> accountTurnover;
  std::vector<Filter*> filters;
  std::vector<Reservation*> reservations;
  bool defaultPriceFilter;
  double getReservationPricesMean();
  double getReservationPricesSD(double mean);
  std::pair<double, double> getReservationPriceStats();
  std::pair<std::string, std::string> sortParams;
  bool manualWeightsActive;
  std::vector<double> manualWeights;
  std::vector<double> estimatedWeights;
  std::vector<std::vector<double>> allRatings;
  bool estimatedWeightsAreValid;

};

#endif
