#include "averagePriceFilter.hpp"
#include "hotel.hpp"

using namespace std;

AveragePriceFilter::AveragePriceFilter(int minPrice, int maxPrice)
{
    minAveragePrice = minPrice;
    maxAveragePrice = maxPrice;
}
vector<Hotel*> AveragePriceFilter::doFilter(std::vector<Hotel*> hotels)
{
    vector<Hotel*> filteredHotels;
    for(int counter = 0; counter<hotels.size(); counter++)
    {
        if(hotels[counter]->isYourAveragePriceInThisRange(minAveragePrice, maxAveragePrice) == true)
        {
            filteredHotels.push_back(hotels[counter]);
        }
    }
    return filteredHotels;
}