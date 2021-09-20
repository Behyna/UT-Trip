#include "starFilter.hpp"
#include "hotel.hpp"

using namespace std;

StarFilter::StarFilter(int minStar, int maxStar)
{
    minStarRating = minStar;
    maxStarRating = maxStar;
}
vector<Hotel*> StarFilter::doFilter(std::vector<Hotel*> hotels)
{
    vector<Hotel*> filteredHotels;
    for(int counter = 0; counter<hotels.size(); counter++)
    {
        if(hotels[counter]->isYourRateinThisRange(minStarRating, maxStarRating) == true)
        {
            filteredHotels.push_back(hotels[counter]);
        }
    }
    return filteredHotels;
}