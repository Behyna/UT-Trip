#include "post.hpp"
#include "filter.hpp"
#include "cityFilter.hpp"
#include "starFilter.hpp"
#include "averagePriceFilter.hpp"
#include "roomFilter.hpp"

#include<map>
#include<iostream>
#include<algorithm>
#include<sstream>

#define FILTERS_TYPE 3

using namespace std;

typedef void (Post::*commandsMethod) (vector<string> data);

void checkTimes(int checkIn, int checkOut)
{
  if (checkIn < 1 && checkIn > 31)
    throw BAD_REQUEST_MSG;
  if (checkOut < 1 && checkOut > 31)
    throw BAD_REQUEST_MSG;
  if (checkIn > checkOut)
    throw BAD_REQUEST_MSG;
}
void validateType(string type)
{
  if (type != STANDARD_KEYWORD && type != DELUXE_KEYWORD && type != LUXURY_KEYWORD && type != PREMIUM_KEYWORD)
    throw BAD_REQUEST_MSG;
}
void validatePrices(int min, int max)
{
  if (min < 0 || max < 0 || min > max)
    throw BAD_REQUEST_MSG;
}
void validateStars(int min, int max)
{
  if (min < 1 || min > 5)
    throw BAD_REQUEST_MSG;
  if (max < 1 || max > 5)
    throw BAD_REQUEST_MSG;
  if (min > max)
    throw BAD_REQUEST_MSG;
}
void validateRatings(vector<double> ratings)
{
  for (int i=0 ;i<ratings.size(); i++)
    if (ratings[i] < 1 || ratings[i] > 5)
      throw BAD_REQUEST_MSG;
}
Post::Post(Utrip* utrip_, User* user_):Command(utrip_,user_){
}
bool Post::isThisEmailExist(string entredEmail)
{
  if(utrip->isThisEmailExistsInYourUsers(entredEmail) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool Post::isThisUsernameExist(string enteredUsername)
{
  if(utrip->isThisUsernameExistsInYourUsers(enteredUsername) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}
User* Post::doCommand(vector<string> data)
{
  map<string, commandsMethod> commands;
  commands[SIGNUP_KEYWORD] = &Post::signUp;
  commands[LOGIN_KEYWORD] = &Post::logIn;
  commands[LOGOUT_KEYWORD] = &Post::logOut;
  commands[WALLET_KEYWORD] = &Post::wallet;
  commands[FILTERS_KEYWORD] = &Post::doFilters;
  commands[RESERVES_KEYWORD] = &Post::reserves;
  commands[COMMENTS_KEYWORD] = &Post::comments;
  commands[RATINGS_KEYWORD] = &Post::ratings;
  commands[DEFAULT_PRICE_FILTER_KEYWORD] = &Post::defaultPriceFilter;
  commands[SORT_KEYWORD] = &Post::sort;
  commands[MANUAL_WEIGHTS_KEYWORD] = &Post::manualWeights;
  try
  {
    auto cm_itr = commands.find(data[1]);
    if(cm_itr == commands.end())
    {
      throw NOT_FOUND_MSG;
    }
    (this->*commands[data[1]]) (data);
  }
  catch(const char* msg)
  {
    cout << msg << endl;
  }
  return user;
}
void Post::signUp(vector<string> data)
{
  string email, username, password;
  vector<string> usersData;
  for(int counter = 3; counter < data.size(); counter+=2)
  {
    if(data[counter] == EMAIL_KEYWORD)
    {
      email = data[counter+1];
      if(isThisEmailExist(email) == true)
      {
        throw BAD_REQUEST_MSG;
      }
    }
    else if(data[counter] == USERNAME_KEYWORD)
    {
      username = data[counter+1];
      if(isThisUsernameExist(username) == true)
      {
        throw BAD_REQUEST_MSG;
      }
    }
    else if(data[counter] == PASSWORD_KEYWORD)
    {
      password = data[counter+1];
    }
  }
  usersData.push_back(username);
  usersData.push_back(password);
  usersData.push_back(email);
  user = utrip->addUser(usersData);
  throw OK_MSG;
}
void Post::logIn(vector<string> data)
{
  string email, password;
  vector<string> usersData;
  for(int counter = 3; counter < data.size(); counter+=2)
  {
    if(data[counter] == EMAIL_KEYWORD)
    {
      email = data[counter+1];
    }
    else if(data[counter] == PASSWORD_KEYWORD)
    {
      password = data[counter+1];
    }
  }
  user = utrip->logInUser(email, password);
  throw OK_MSG;
}
void Post::logOut(vector<string> data)
{
  isUserLogin();
  user->deleteFilters();
  user = NULL;
  throw OK_MSG;
}
void Post::wallet(vector<string> data)
{
  isUserLogin();
  if(data[3]== AMOUNT_KEYWORD)
  {
    utrip->chargeUsersAccount(user,data[4]);
    throw OK_MSG;
  }
}
StarFilter* makeStarFilter(vector<string> data)
{
  int maxStar, minStar;
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == MIN_STAR_KEYWORD)
      minStar = stoi(data[counter+1]);
    else if((data[counter] == MAX_STAR_KEYWORD))
      maxStar = stoi(data[counter+1]);
  }
  validateStars(minStar,  maxStar);
  StarFilter* starFilter = new StarFilter(minStar, maxStar);
  return starFilter;
}
AveragePriceFilter* makeAveragePriceFilter(vector<string> data)
{
  int maxPrice, minPrice;
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == MIN_PRICE_KEYWORD)
      minPrice = stoi(data[counter+1]);
    else if((data[counter] == MAX_PRICE_KEYWORD))
      maxPrice = stoi(data[counter+1]);
  }
  validatePrices(minPrice, maxPrice);
  AveragePriceFilter* averagePriceFilter = new AveragePriceFilter(minPrice, maxPrice);
  return averagePriceFilter;
}
RoomFilter* makeRoomFilter(vector<string> data)
{
  string type;
  int checkIn, checkOut, quantity;
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == TYPE_KEYWORD)
      type = data[counter+1];
    else if((data[counter] == QUANTITY_KEYWORD))
      quantity = stoi(data[counter+1]);
    else if((data[counter] == CHECK_IN_KEYWORD))
      checkIn = stoi(data[counter+1]);
    else if((data[counter] == CHECK_OUT_KEYWORD))
      checkOut = stoi(data[counter+1]);
  }
  validateType(type);
  checkTimes(checkIn, checkOut);
  RoomFilter* roomFilter = new RoomFilter(type, quantity, checkIn, checkOut);
  return roomFilter;
}
void Post::doFilters(vector<string> data)
{
  Filter* filter;
  if(isUserLogin() == true)
  {
    for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
    {
      if(data[counter] == CITY_KEYWORD)
      {
        CityFilter* cityFilter = new CityFilter(data[counter+1]);
        filter = cityFilter;
      }
      else if((data[counter] == MIN_STAR_KEYWORD) || (data[counter] == MAX_STAR_KEYWORD))
      {
        filter = makeStarFilter(data);
      }
      else if((data[counter] == MIN_PRICE_KEYWORD) || (data[counter] == MAX_PRICE_KEYWORD))
      {
        filter = makeAveragePriceFilter(data);
        user->setDefaultPriceFilter(false);
      }
      else if((data[counter] == TYPE_KEYWORD) || (data[counter] == QUANTITY_KEYWORD) || (data[counter] == CHECK_IN_KEYWORD) || (data[counter] == CHECK_OUT_KEYWORD))
      {
        filter = makeRoomFilter(data);
      }
    }
    user->setFilters(filter);
    throw OK_MSG;
  }
}
void Post::reserves(vector<string> data)
{
  string hotelId, type;
  int quantity, checkIn, checkOut;
  isUserLogin();
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == HOTEL_KEYWORD)
    {
      hotelId = data[counter+1];
    }
    else if(data[counter] == TYPE_KEYWORD)
    {
      type = data[counter+1];
      validateType(type);
    }
    else if(data[counter] == QUANTITY_KEYWORD)
    {
      quantity = stoi(data[counter+1]);
    }
    else if(data[counter] == CHECK_IN_KEYWORD)
    {
      checkIn = stoi(data[counter+1]); 
    }
    else if(data[counter] == CHECK_OUT_KEYWORD)
    {
      checkOut = stoi(data[counter+1]);
    }
  }
  checkTimes(checkIn, checkOut);
  vector<Room*> foundRooms = utrip->reserve(hotelId, type, quantity, checkIn, checkOut, user);
  for (int i=0; i<foundRooms.size(); i++)
  {
    if (i != (foundRooms.size()-1))
      cout << foundRooms[i]->getId() << " ";
    else
      cout << foundRooms[i]->getId();

  }
  cout << endl;
}
void Post::comments(vector<string> data)
{
  string hotelId, text;
  isUserLogin();
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == HOTEL_KEYWORD)
      hotelId = data[counter+1];
    else if(data[counter] == COMMENT_KEYWORD)
      text = data[counter+1];
  }
  utrip->getHotel(hotelId)->addComment(text, user->getUsername());
  throw OK_MSG;
}
void Post::ratings(vector<string> data)
{
  string hotelId;
  double location, clean, staff, facilities, valueForMoney, overallRating;
  isUserLogin();
  vector<double> ratings(6);
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == HOTEL_KEYWORD)
      hotelId = data[counter+1];
    else if(data[counter] == LOCATION_KEYWORD)
      ratings[0] = stod(data[counter+1]);
    else if(data[counter] == CLEANLINESS_KEYWORD)
      ratings[1] = stod(data[counter+1]);
    else if(data[counter] == STAFF_KEYWORD)
      ratings[2] = stod(data[counter+1]);
    else if(data[counter] == FACILITIES_KEYWORD)
      ratings[3] = stod(data[counter+1]);
    else if(data[counter] == VALUE_FOR_MONEY_KEYWORD)
      ratings[4] = stod(data[counter+1]);
    else if(data[counter] == OVERALL_RATING_KEYWORD)
      ratings[5] = stod(data[counter+1]);
  }
  validateRatings(ratings);
  utrip->getHotel(hotelId)->addRatings(ratings, user->getUsername());
  user->addRatings(ratings);
  throw OK_MSG;
}
void Post::defaultPriceFilter(vector<string> data)
{
  isUserLogin();
  if (data[4] == TRUE_KEYWORD || data[4] == FALSE_KEYWORD)
  {
    user->setDefaultPriceFilter(data[4] == TRUE_KEYWORD);
    throw OK_MSG;
  }
  else
    throw BAD_REQUEST_MSG;
}
void validateSortData(string property, string order)
{
  if (order != ASCENDING_KEYWORD && order != DESCENDING_KEYWORD)
    throw BAD_REQUEST_MSG;

  string features[NUM_SORT_FEATURES] = {ID_KEYWORD, NAME_KEYWORD, STAR_RATING_KEYWORD,
                                        CITY_KEYWORD, STANDARD_ROOM_PRICE_KEYWORD,DELUXE_ROOM_PRICE_KEYWORD,
                                        LUXURY_ROOM_PRICE_KEYWORD, PREMIUM_ROOM_PRICE_KEYWORD, AVERAGE_ROOM_PRICE_KEYWORD,
                                        RATING_OVERALL_KEYWORD, RATING_PERSONAL_KEYWORD};
  for (int i=0; i<NUM_SORT_FEATURES; i++)
  {
    if (features[i] == property)
      return;
  }
  throw BAD_REQUEST_MSG;
}
void Post::sort(vector<string> data)
{
  isUserLogin();
  string property, order;
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == PROPERTY_KEYWORD)
      property = data[counter+1];
    else if(data[counter] == ORDER_KEYWORD)
      order = data[counter+1];
  }
  validateSortData(property, order);
  user->setSortParams(property, order);
  throw OK_MSG;
}
void validateWeights(vector<double> ratings)
{
  for (int i=0 ;i<ratings.size(); i++)
    if (ratings[i] < 1 || ratings[i] > 5)
      throw BAD_REQUEST_MSG;
}
void Post::manualWeights(vector<string> data)
{
  isUserLogin();
  bool active;
  vector<double> weights(NUM_WEIGHTS);
  for(int counter = FILTERS_TYPE; counter < data.size(); counter+=2)
  {
    if(data[counter] == ACTIVE_KEYWORD)
      active = data[counter+1] == TRUE_KEYWORD;
    else if(data[counter] == LOCATION_KEYWORD)
      weights[LOCATION_INDEX] = stod(data[counter+1]);
    else if(data[counter] == CLEANLINESS_KEYWORD)
      weights[CLEANLINESS_INDEX] = stod(data[counter+1]);
    else if(data[counter] == STAFF_KEYWORD)
      weights[STAFF_INDEX] = stod(data[counter+1]);
    else if(data[counter] == FACILITIES_KEYWORD)
      weights[FACILITIES_INDEX] = stod(data[counter+1]);
    else if(data[counter] == VALUE_FOR_MONEY_KEYWORD)
      weights[VALUE_FOR_MONEY_INDEX] = stod(data[counter+1]);
  }
  validateWeights(weights);
  user->setManualWeights(active, weights);
  throw OK_MSG;
}
