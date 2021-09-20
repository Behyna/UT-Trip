#ifndef CITYFILTER_HPP
#define CITYFILTER_HPP "CITYFILTER_HPP"

#include"filter.hpp"

class CityFilter:public Filter{
    public:
    CityFilter(std::string hotelsCity);
    std::vector<Hotel*> doFilter(std::vector<Hotel*> hotels);
    private:
    std::string city;
};

#endif