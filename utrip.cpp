#include "utrip.hpp"
#include "room.hpp"
#include "standard.hpp"
#include "deluxe.hpp"
#include "luxury.hpp"
#include "premium.hpp"

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>

#define HOTELS_ID 0
#define USERS_NAME 0
#define USERS_PASSWORD 1
#define USERS_EMAIL 2
#define HOTELS_NAME 1
#define HOTELS_STAR_RATING 2
#define HOTELS_OVERVIEW 3
#define HOTELS_AMENITIES 4
#define HOTELS_CITY 5
#define HOTELS_LATITUDE 6
#define HOTELS_LONGITUDE 7
#define HOTELS_IMAGEURL 8
#define HOTELS_STANDARD_ROOMS_NUM 9
#define HOTELS_DELUXE_ROOMS_NUM 10
#define HOTELS_LUXURY_ROOMS_NUM 11
#define HOTELS_PREMIUM_ROOMS_NUM 12
#define HOTELS_STANDARD_ROOMS_PRICE 13
#define HOTELS_DELUXE_ROOMS_PRICE 14
#define HOTELS_LUXURY_ROOMS_PRICE 15
#define HOTELS_PREMIUM_ROOMS_PRICE 16

using namespace std;

vector<Room*> setStandardRoom(int roomsNumber, int price)
{
  vector<Room*> rooms;
  for(int counter = 1; counter <= roomsNumber; counter++)
  {
    Standard* room = new Standard(price, to_string(counter));
    rooms.push_back(room);
  }
  return rooms;
}
vector<Room*> setDeluxeRoom(int roomsNumber, int price)
{
  vector<Room*> rooms;
  for(int counter = 1; counter <= roomsNumber; counter++)
  {
    Deluxe* room = new Deluxe(price, to_string(counter));
    rooms.push_back(room);
  }
  return rooms;
}
vector<Room*> setLuxuryRoom(int roomsNumber, int price)
{
  vector<Room*> rooms;
  for(int counter = 1; counter <= roomsNumber; counter++)
  {
    Luxury* room = new Luxury(price, to_string(counter));
    rooms.push_back(room);
  }
  return rooms;
}
vector<Room*> setPremiumRoom(int roomsNumber, int price)
{
  vector<Room*> rooms;
  for(int counter = 1; counter <= roomsNumber; counter++)
  {
    Premium* room = new Premium(price, to_string(counter));
    rooms.push_back(room);
  }
  return rooms;
}
vector<Room*> mergeRooms(vector<Room*> allRooms, vector<Room*> rooms)
{
  for (int counter = 0; counter < rooms.size(); counter++)
  {
    allRooms.push_back(rooms[counter]);
  }
  return allRooms;
}
vector<Room*> setRoom(vector<string> hotelsData)
{
  vector<Room*> allRooms, rooms;
  if (stoi(hotelsData[HOTELS_STANDARD_ROOMS_NUM]) != 0)
  {

    rooms = setStandardRoom(stoi(hotelsData[HOTELS_STANDARD_ROOMS_NUM]), stoi(hotelsData[HOTELS_STANDARD_ROOMS_NUM + 4]));
    allRooms = mergeRooms(allRooms, rooms);
  }
  if (stoi(hotelsData[HOTELS_DELUXE_ROOMS_NUM]) != 0)
  {
    rooms = setDeluxeRoom(stoi(hotelsData[HOTELS_DELUXE_ROOMS_NUM]), stoi(hotelsData[HOTELS_DELUXE_ROOMS_NUM + 4]));
    allRooms = mergeRooms(allRooms, rooms);
  }
  if (stoi(hotelsData[HOTELS_LUXURY_ROOMS_NUM]) != 0)
  {
    rooms = setLuxuryRoom(stoi(hotelsData[HOTELS_LUXURY_ROOMS_NUM]), stoi(hotelsData[HOTELS_LUXURY_ROOMS_NUM + 4]));
    allRooms = mergeRooms(allRooms, rooms);
  }
  if (stoi(hotelsData[HOTELS_PREMIUM_ROOMS_NUM]) != 0)
  {
    rooms = setPremiumRoom(stoi(hotelsData[HOTELS_PREMIUM_ROOMS_NUM]), stoi(hotelsData[HOTELS_PREMIUM_ROOMS_NUM + 4]));
    allRooms = mergeRooms(allRooms, rooms);
  }
  return allRooms;
}
double countHotelsAvragePrice(int standaradRoomsPrice, int deluxeRoomsPrice, int luxuryRoomsPrice, int premiumRoomsPrice)
{
  double sumOfPrices = 0;
  int counter = 0;
  if(standaradRoomsPrice != 0)
  {
    sumOfPrices += standaradRoomsPrice;
    counter++;
  }
  if(deluxeRoomsPrice != 0)
  {
    sumOfPrices += deluxeRoomsPrice;
    counter++;
  }
  if(luxuryRoomsPrice != 0)
  {
    sumOfPrices += luxuryRoomsPrice;
    counter++;
  }
  if(premiumRoomsPrice != 0)
  {
    sumOfPrices += premiumRoomsPrice;
    counter++;
  }
  if (counter == 0)
    return 0;
  return sumOfPrices/counter;
}

vector<int> countRooms(vector<string> hotelsData)
{
  vector<int> roomsNumbers;
  roomsNumbers.push_back(stoi(hotelsData[HOTELS_STANDARD_ROOMS_NUM]));
  roomsNumbers.push_back(stoi(hotelsData[HOTELS_DELUXE_ROOMS_NUM]));
  roomsNumbers.push_back(stoi(hotelsData[HOTELS_LUXURY_ROOMS_NUM]));
  roomsNumbers.push_back(stoi(hotelsData[HOTELS_PREMIUM_ROOMS_NUM]));
  return roomsNumbers;
}
vector<int> getRoomsPrices(vector<string> hotelsData)
{
  vector<int> roomsPrices;
  roomsPrices.push_back(stoi(hotelsData[HOTELS_STANDARD_ROOMS_PRICE]));
  roomsPrices.push_back(stoi(hotelsData[HOTELS_DELUXE_ROOMS_PRICE]));
  roomsPrices.push_back(stoi(hotelsData[HOTELS_LUXURY_ROOMS_PRICE]));
  roomsPrices.push_back(stoi(hotelsData[HOTELS_PREMIUM_ROOMS_PRICE]));
  return roomsPrices;
}
void Utrip::addHotel(vector<string> hotelsData, vector<double> hotelsRatings)
{
  Hotel* hotel = new Hotel(hotelsData[HOTELS_ID], hotelsData[HOTELS_NAME], stoi(hotelsData[HOTELS_STAR_RATING]),
  hotelsData[HOTELS_OVERVIEW], hotelsData[HOTELS_AMENITIES], hotelsData[HOTELS_CITY], stod(hotelsData[HOTELS_LATITUDE]),
  stod(hotelsData[HOTELS_LONGITUDE]), hotelsData[HOTELS_IMAGEURL], setRoom(hotelsData), countHotelsAvragePrice(
  stoi(hotelsData[HOTELS_STANDARD_ROOMS_PRICE]), stoi(hotelsData[HOTELS_DELUXE_ROOMS_PRICE]),
  stoi(hotelsData[HOTELS_LUXURY_ROOMS_PRICE]), stoi(hotelsData[HOTELS_PREMIUM_ROOMS_PRICE])),
  countRooms(hotelsData), getRoomsPrices(hotelsData), hotelsRatings);
  hotels.push_back(hotel);
}
User* Utrip::addUser(vector<string> usersData)
{
  User* user = new User(usersData[USERS_NAME], usersData[USERS_PASSWORD], usersData[USERS_EMAIL]);
  users.push_back(user);
  return user;
}
User* Utrip::logInUser(string email, string password)
{
  for(int counter = 0; counter < users.size(); counter++)
  {
    if(users[counter]->checkingUsersInfo(email, password) == true)
    {
      return users[counter];
    }
  }
  throw BAD_REQUEST_MSG;
}
bool Utrip::isThisEmailExistsInYourUsers(string email)
{
  for(int counter = 0; counter < users.size(); counter++)
  {
    if(users[counter]->isThisYourEmail(email) == true )
    {
      return true;
    }
  }
  return false;
}
bool Utrip::isThisUsernameExistsInYourUsers(string username)
{
  for(int counter = 0; counter < users.size(); counter++)
  {
    if(users[counter]->isThisYourUserName(username) == true)
    {
      return true;
    }
  }
  return false;
}
void Utrip::chargeUsersAccount(User* user, string money)
{
  if(stod(money) > 0)
  {
    user->chargeMyAccount(stod(money));
  }
  else
  {
    throw BAD_REQUEST_MSG;
  }
}
vector<Hotel*> Utrip::doFilters(vector<Filter*> filters)
{
  vector<Hotel*> filteredHotels = hotels;
  for (int i=0; i<filters.size(); i++)
  {
    filteredHotels = filters[i]->doFilter(filteredHotels);
  }
  return filteredHotels;
}
Hotel* Utrip::getHotel(std::string id)
{
  for(int i=0; i<hotels.size(); i++)
    if (hotels[i]->getId() == id)
      return hotels[i];
  throw NOT_FOUND_MSG;
}
vector<Room*> Utrip::reserve(string hotelId, string type, int quantity, int checkIn, int checkOut, User* user)
{
  Hotel* hotel = getHotel(hotelId);
  vector<Room*> foundRooms = hotel->reserveRooms(type, quantity, checkIn, checkOut);
  int cost = quantity * foundRooms[0]->getPrice();
  user->payCredit(cost);

  for (int i=0; i<foundRooms.size(); i++)
    foundRooms[i]->reserve(checkIn, checkOut);
  user->addReserve(hotelId, type, quantity, cost, checkIn, checkOut, foundRooms);
  return foundRooms;

}