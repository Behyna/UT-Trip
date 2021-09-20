#ifndef ROOMFILTER_HPP
#define ROOMFILTER_HPP "ROOMFILTER_HPP"

#include "filter.hpp"
#include "hotel.hpp"

#include <string>
class RoomFilter:public Filter{
    public:
    RoomFilter(std::string type, int quantity, int checkIn, int checkOut);
    std::vector<Hotel*> doFilter(std::vector<Hotel*> hotels);
    private:
    std::string type;
    int quantity;
    int checkIn;
    int checkOut;

};

#endif