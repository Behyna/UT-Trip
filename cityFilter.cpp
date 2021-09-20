#include "cityFilter.hpp"

using namespace std;

CityFilter::CityFilter(string hotelsCity)
{
    city = hotelsCity;
}
vector<Hotel*> CityFilter::doFilter(vector<Hotel*> hotels)
{
    vector<Hotel*> filteredHotels;
    for(int counter = 0; counter < hotels.size(); counter++)
    {
        if(hotels[counter]->isThisYourCity(city) == true)
        {
            filteredHotels.push_back(hotels[counter]);
        }
    }
    return filteredHotels;
}