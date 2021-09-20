#include "defaultPriceFilter.hpp"

using namespace std;

DefaultPriceFilter::DefaultPriceFilter(pair<double, double> _stats)
{
    stats = _stats;
}

vector<Hotel*> DefaultPriceFilter::doFilter(std::vector<Hotel*> hotels)
{
    double mean, sd, hotelMean, minPrice, maxPrice;
    mean = stats.first;
    sd = stats.second;
    vector<Hotel*> filteredHotels;
    minPrice = mean - 2 * sd;
    maxPrice = mean + 2 * sd;
    for(int counter = 0; counter<hotels.size(); counter++)
    {
        if(hotels[counter]->isYourAveragePriceInThisRange(minPrice, maxPrice))
        {
            filteredHotels.push_back(hotels[counter]);
        }
    }
    return filteredHotels;
}