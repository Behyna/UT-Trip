#ifndef HOTEL_HPP
#define HOTEL_HPP "HOTEL_HPP"

#include<string>
#include<vector>
#include<numeric>
#include<algorithm>

#include "room.hpp"
#include "comment.hpp"
#include "userRatings.hpp"
#include "defines.hpp"

struct PersonalRatingData{
  PersonalRatingData(std::string _username, std::vector<double> _weights, std::pair<std::string, std::string> _sortParams, bool _insufficientRatings)
  {
    username = _username;
    weights = _weights;
    sortParams = _sortParams;
    insufficientRatings = _insufficientRatings;
  }
  std::string username;
  std::vector<double> weights;
  std::pair<std::string, std::string> sortParams;
  bool insufficientRatings;
};

double predictRating(std::vector<double> weights, std::vector<double> averageRatings);
double mySum(double d1, double d2);

class Hotel{
public:
  Hotel(std::string hotelsId, std::string hotelsName, int hotelsStarRating, std::string hotelsOverView, std::string hotelsAmenities,
    std::string hotelsCity, double hotelsLatitude, double hotelsLongitude, std::string hotelsImageUrl, std::vector<Room*> hotelsRooms, 
    double hotelsAvragePrice, std::vector<int> hotelsRoomsNumbers, std::vector<int> hotelsRoomsPrices, std::vector<double> averageRatings);
  std::string getId();
  bool isThisYourCity(std::string enteredCity);
  bool isYourRateinThisRange(int min, int max);
  bool isYourAveragePriceInThisRange(double min, double max);
  std::string getName();
  int getStarRating();
  std::string getCity();
  std::string getOverview();
  int getTotalNumOfRooms();
  double getAvragePrice();
  std::string getAmenities();
  double getLatitude();
  double getLongitude();
  std::vector<int> getRoomsNumbers();
  std::vector<int> getRoomsPrices();
  std::vector<Room*> reserveRooms(std::string type, int quantity, int checkIn, int checkOut);
  void addComment(std::string text, std::string username);
  void setRatings(std::vector<double> ratings);
  std::vector<Comment*> getComments() {return comments;}
  std::vector<double> getAverageRatings();
  double getOverallRating(){return averageRatings[averageRatings.size()-1];};
  void addRatings(std::vector<double>, std::string username);
  double getPersonalRating(PersonalRatingData* personalRatingData);

private:
  std::vector<int> roomsNumbers;
  std::vector<int> roomsPrices;
  std::string id;
  std::string name;
  int starRating;
  std::string overView;
  std::string amenities;
  std::string city;
  double latitude;
  double longitude;
  std::string imageUrl;
  std::vector<Room*> rooms;
  double avragePrice;
  std::vector<Comment*> comments;
  std::vector<double> averageRatings;
  std::vector<UserRatings*> allRatings;
};
#endif
