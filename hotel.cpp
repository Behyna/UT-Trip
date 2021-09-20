#include "hotel.hpp"
#include <iostream>
#include<vector>
#include<sstream>
#include<random>

using namespace std;

Hotel::Hotel(string hotelsId, string hotelsName, int hotelsStarRating, std::string hotelsOverView, std::string hotelsAmenities,
  std::string hotelsCity, double hotelsLatitude, double hotelsLongitude, std::string hotelsImageUrl, vector<Room*> hotelsRooms,
  double hotelsAvragePrice, vector<int> hotelsRoomsNumbers, vector<int> hotelsRoomsPrices, vector<double> _averageRatings)
  {
    id = hotelsId;
    name = hotelsName;
    starRating = hotelsStarRating;
    overView = hotelsOverView;
    amenities = hotelsAmenities;
    city = hotelsCity;
    latitude = hotelsLatitude;
    longitude = hotelsLongitude;
    imageUrl = hotelsImageUrl;
    rooms = hotelsRooms;
    avragePrice = hotelsAvragePrice;
    roomsNumbers = hotelsRoomsNumbers;
    roomsPrices = hotelsRoomsPrices;
    averageRatings = _averageRatings;
  }
string Hotel::getId()
{
  return id;
}
bool Hotel::isThisYourCity(string enteredCity)
{
  if(city == enteredCity)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}
bool Hotel::isYourRateinThisRange(int min, int max)
{
  return (starRating >= min) && (starRating <= max);
}
bool Hotel::isYourAveragePriceInThisRange(double min, double max)
{
  return (avragePrice >= min) && (avragePrice <= max);
}
string Hotel::getName()
{
  return name;
}
int Hotel::getStarRating()
{
  return starRating;
}
string Hotel::getCity()
{
  return city;
}
int Hotel::getTotalNumOfRooms()
{
  return rooms.size();
}
double Hotel::getAvragePrice()
{
  return avragePrice;
}
string Hotel::getOverview()
{
  return overView;
}
string Hotel::getAmenities()
{
  return amenities;
}
double Hotel::getLatitude()
{
  return latitude;
}
double Hotel::getLongitude()
{
  return longitude;
}

vector<int> Hotel::getRoomsNumbers()
{
  return roomsNumbers;
}

vector<int> Hotel::getRoomsPrices()
{
  return roomsPrices;
}

#define STANDARD_ROOM

vector<Room*> Hotel::reserveRooms(string type, int quantity, int checkIn, int checkOut)
{
  string prefix;
  vector<Room *> foundRooms;
  for(int i=0; i<rooms.size(); i++)
  {
    if ( type[0] == rooms[i]->getId()[0] && !(rooms[i]->isReserved(checkIn, checkOut)) )
    {
      foundRooms.push_back(rooms[i]);
    }

    if (foundRooms.size() == quantity)
    {
      return foundRooms;
    }
  }
  throw NOT_ENOUGH_ROOM_MSG;
}
void Hotel::addComment(std::string text, std::string username)
{
  comments.push_back(new Comment(text, username));
}
vector<double> Hotel::getAverageRatings()
{
  return averageRatings;
}
void Hotel::addRatings(vector<double> ratings, std::string username)
{
  for (int i=0; i<allRatings.size(); i++)
  {
    if (username == allRatings[i]->getUsername())
    {
      delete allRatings[i];
      allRatings[i] = new UserRatings(ratings, username);
      return;
    }
  }
  allRatings.push_back(new UserRatings(ratings, username));
}
double myMultiply(double d1, double d2)
{
  return d1 * d2;
}
double mySum(double d1, double d2)
{
  return d1 + d2;
}
double predictRating(vector<double> weights, vector<double> averageRatings)
{
  vector<double> tempVec(weights.size());
  transform(weights.begin(), weights.end(), averageRatings.begin(), tempVec.begin(), myMultiply);
  double sum = accumulate(tempVec.begin(), tempVec.end(), 0.0, mySum);
  double sumOfWeights = accumulate(weights.begin(), weights.end(), 0.0, mySum);
  return sum / sumOfWeights;
}

double Hotel::getPersonalRating(PersonalRatingData* data)
{
  for (int i=0; i<allRatings.size(); i++)
    if (allRatings[i]->getUsername() == data->username)
      {
        vector<double> ratings = allRatings[i]->getRating();
        return ratings[ratings.size()-1];
      }
  if (data->insufficientRatings)
    throw INSUFFICIENT_RATINGS_MSG;  
  return predictRating(data->weights, averageRatings);
}