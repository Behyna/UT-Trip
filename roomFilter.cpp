#include "roomFilter.hpp"
#include <iostream>

using namespace std;

RoomFilter::RoomFilter(string _type, int _quantity, int _checkIn, int _checkOut)
{
    type = _type;
    quantity = _quantity;
    checkIn = _checkIn;
    checkOut = _checkOut;
}
vector<Hotel*> RoomFilter::doFilter(vector<Hotel*> hotels)
{
    vector<Hotel*> filteredHotels;
    for(int i = 0; i < hotels.size(); i++)
    {
        try
        {
            hotels[i]->reserveRooms(type, quantity, checkIn, checkOut);
            filteredHotels.push_back(hotels[i]);
        }
        catch(const char* msg)
        {
            msg;
        }
        
    }
    return filteredHotels;
}