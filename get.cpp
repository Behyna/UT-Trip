#include "get.hpp"

#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef void (Get::*commandsMethod) (vector<string> data);
Get::Get(Utrip* utrip_, User* user_):Command(utrip_,user_){
}
struct CompareStruct {
    CompareStruct(PersonalRatingData* data) 
    { 
      this->data = data;
      this->property = data->sortParams.first;
    }
    bool operator()(Hotel* h1, Hotel* h2) 
    {      
      if (property == ID_KEYWORD)
        return h1->getId() < h2->getId();
      if (property == NAME_KEYWORD)
        return h1->getName() < h2->getName();
      if (property == STAR_RATING_KEYWORD)
        return h1->getStarRating() < h2->getStarRating();
      if (property == CITY_KEYWORD)
        return h1->getCity() < h2->getCity();
      if (property == STANDARD_ROOM_PRICE_KEYWORD)
        return h1->getRoomsPrices()[STANDARD_ROOM_INDEX] < h2->getRoomsPrices()[STANDARD_ROOM_INDEX];
      if (property == DELUXE_ROOM_PRICE_KEYWORD)
        return h1->getRoomsPrices()[DELUXE_ROOM_INDEX] < h2->getRoomsPrices()[DELUXE_ROOM_INDEX];
      if (property == LUXURY_ROOM_PRICE_KEYWORD)
        return h1->getRoomsPrices()[LUXURY_ROOM_INDEX] < h2->getRoomsPrices()[LUXURY_ROOM_INDEX];
      if (property == PREMIUM_ROOM_PRICE_KEYWORD)
        return h1->getRoomsPrices()[PREMIUM_ROOM_INDEX] < h2->getRoomsPrices()[PREMIUM_ROOM_INDEX];
      if (property == AVERAGE_ROOM_PRICE_KEYWORD)
        return h1->getAvragePrice() < h2->getAvragePrice();
      if (property == RATING_OVERALL_KEYWORD)
        return h1->getOverallRating() < h2->getOverallRating();
      if (property == RATING_PERSONAL_KEYWORD)
        return h1->getPersonalRating(data) < h2->getPersonalRating(data);
    }
    PersonalRatingData* data;
    string property;

};
bool compareHotelsById(Hotel* h1, Hotel* h2)
{
  return h1->getId() < h2->getId();
}
vector<Hotel*> sortHotels(vector<Hotel*> hotels, User* user)
{
  PersonalRatingData* PRData = new PersonalRatingData(user->getUsername(), user->getWeights(), user->getSortParams(), user->insufficientRatings());
  sort(hotels.begin(), hotels.end(), compareHotelsById);
  stable_sort(hotels.begin(), hotels.end(), CompareStruct(PRData));
  if (user->getSortParams().second == DESCENDING_KEYWORD)
    reverse(hotels.begin(), hotels.end());
  return hotels;
}
void Get::doCommand(vector<string> data)
{
    map<string, commandsMethod> commands;
    commands[WALLET_KEYWORD] = &Get::wallet;
    commands[HOTELS_KEYWORD] = &Get::hotels;
    commands[RESERVES_KEYWORD] = &Get::reserves;
    commands[COMMENTS_KEYWORD] = &Get::comments;
    commands[RATINGS_KEYWORD] = &Get::ratings;
    commands[MANUAL_WEIGHTS_KEYWORD] = &Get::manualWeights;
    commands[ESTIMATED_WEIGHTS_KEYWORD] = &Get::estimatedWeights;
    try{
      auto cm_itr = commands.find(data[1]);
      if(cm_itr == commands.end())
      {
        throw NOT_FOUND_MSG;
      }
      (this->*commands[data[1]]) (data);

    }
    catch(const char* msg){
      cout << msg << endl;
    }
}
void printAccountTurnovers(vector<int> turnovers)
{
  for(int i=0; i<turnovers.size(); i++)
    cout << turnovers[i] << endl;
}
void Get::wallet(vector<string> data)
{
  isUserLogin();
  int count = stoi(data[4]);
  vector<int> turnovers = user->getAccountTurnover(count);
  printAccountTurnovers(turnovers);
} 
void printSummryOfHotel(Hotel* hotel, bool defaultPriceEnabled)
{
  cout << hotel->getId() << ' ' << hotel->getName() << ' ' << hotel->getStarRating() << ' ' << hotel->getCity() 
  << ' ' << hotel->getTotalNumOfRooms() << ' ' << FIX_PRECISION hotel->getAvragePrice() << " " << endl;
}
void printAllHotels(vector<Hotel*> hotels, bool defaultPriceEnabled)
{
  if (hotels.size() == 0)
    throw EMPTY_MSG;
  if (defaultPriceEnabled)
    cout << DEFAULT_PRICE_FILTER_PRINT_MSG << endl;
  for(int i=0; i<hotels.size(); i++)
    printSummryOfHotel(hotels[i], defaultPriceEnabled);
}
void printHotel(Hotel* hotel)
{
  cout << hotel->getId() << endl;
  cout << hotel->getName() << endl;
  cout << PRINT__STAR_KEYWORD << hotel->getStarRating() << endl;
  cout << PRINT__OVERVIEW_KEYWORD << hotel->getOverview() << endl;
  cout << PRINT__AMENITIES_KEYWORD <<  hotel->getAmenities() << endl;
  cout << PRINT__CITY_KEYWORD << hotel->getCity() << endl;
  cout << PRINT__LATITUDE_KEYWORD << FIX_PRECISION hotel->getLatitude() << endl;
  cout << PRINT__LONGITUDE_KEYWORD << FIX_PRECISION hotel->getLongitude() << endl;
  cout << PRINT__ROOMS_KEYWORD;
  vector<int> roomsNumbers = hotel->getRoomsNumbers();
  for (int i=0; i<roomsNumbers.size(); i++)
    cout << " " << roomsNumbers[i];
  cout << endl;
  cout << PRINT__PRICE_KEYWORD;
  vector<int> roomsPrices = hotel->getRoomsPrices();
  for (int i=0; i<roomsPrices.size(); i++)
    cout << " " << roomsPrices[i];
  cout << endl;

}
void Get::hotels(vector<string> data)
{
  bool defaultPriceEnabled;
  isUserLogin();
  if(data.size() == 2)
  {
    defaultPriceEnabled = user->prepareDefaultPriceFilter();
    vector<Hotel*> hotels = sortHotels(utrip->doFilters(user->getFilters()), user);
    printAllHotels(hotels, defaultPriceEnabled);
  }
  else if(data.size() == 5)
  {
    Hotel* hotel = utrip->getHotel(data[4]);
    printHotel(hotel);
  }
}

void printReservation(Reservation* reservation)
{
  cout << PRINT__ID_KEYWORD << reservation->getId() << " ";
  cout << PRINT__HOTEL_KEYWORD << reservation->getHotelId() << " ";
  cout << PRINT__ROOM_KEYWORD << reservation->getType() << " ";
  cout << PRINT__QUANTITY_KEYWORD << reservation->getQuantity() << " ";
  cout << PRINT__COST_KEYWORD << reservation->getCost() << " ";
  cout << PRINT__CHECK_IN_KEYWORD << reservation->getCheckIn() << " ";
  cout << PRINT__CHECK_OUT_KEYWORD << reservation->getCheckOut() << endl;
}

void Get::reserves(std::vector<std::string> command){
  isUserLogin();
  vector<Reservation*> reservations = user->getReservations();
  if (reservations.size() == 0)
    throw EMPTY_MSG;

  for (int i=0; i<reservations.size(); i++)
    printReservation(reservations[reservations.size() - i - 1]);  

}
void printComment(Comment* comment)
{
  cout << comment->getUsername() << ": " << comment->getText() << endl;
}
void Get::comments(std::vector<std::string> data){
  isUserLogin();
  string hotelId = data[4];
  vector<Comment*> comments =  utrip->getHotel(hotelId)->getComments();
  for (int i=0; i<comments.size(); i++)
    printComment(comments[comments.size() - i - 1]);  
}
void printRatings(vector<double> averageRatings)
{
  cout << PRINT__LOCATION_KEYWORD << FIX_PRECISION averageRatings[0] << endl;
  cout << PRINT__CLEANLINESS_KEYWORD << FIX_PRECISION averageRatings[1] << endl;
  cout << PRINT__STAFF_KEYWORD << FIX_PRECISION averageRatings[2] << endl;
  cout << PRINT__FACILITIES_KEYWORD << FIX_PRECISION averageRatings[3] << endl;
  cout << PRINT__VALUE_FOR_MONEY_KEYWORD << FIX_PRECISION averageRatings[4] << endl;
  cout << PRINT__OVERALL_RATING_KEYWORD << FIX_PRECISION averageRatings[5] << endl;
}
void Get::ratings(std::vector<std::string> data){
  isUserLogin();
  string hotelId = data[4];
  vector<double> averageRatings = utrip->getHotel(hotelId)->getAverageRatings();
  printRatings(averageRatings); 
}
void printWeights(vector<double> weights)
{
  cout << LOCATION_KEYWORD << " " << FIX_PRECISION weights[LOCATION_INDEX] << " ";
  cout << CLEANLINESS_KEYWORD << " " << FIX_PRECISION weights[CLEANLINESS_INDEX] << " ";
  cout << STAFF_KEYWORD << " " << FIX_PRECISION weights[STAFF_INDEX] << " ";
  cout << FACILITIES_KEYWORD << " " << FIX_PRECISION weights[FACILITIES_INDEX] << " ";
  cout << VALUE_FOR_MONEY_KEYWORD << " " << FIX_PRECISION weights[VALUE_FOR_MONEY_INDEX] << " " <<endl;

}
void printManualWeights(bool active, vector<double> weights)
{
  if (!active)
  {
    cout << ACTIVE_KEYWORD << " " << FALSE_KEYWORD << endl;
    return;
  }
  cout << ACTIVE_KEYWORD << " " << TRUE_KEYWORD << " ";
  printWeights(weights);
}
void Get::manualWeights(std::vector<std::string> data){
  isUserLogin();
  bool active = user->isManualWeightsActive(); 
  vector<double> weights = user->getManualWeights();
  printManualWeights(active, weights);
}
void Get::estimatedWeights(vector<string> data)
{
  isUserLogin();
  if (user->insufficientRatings())
    throw INSUFFICIENT_RATINGS_MSG;
  printWeights(user->getEstimatedWeights());
}
