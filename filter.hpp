#ifndef FILTER_HPP
#define FILTER_HPP "FILTER_HPP"

#include<vector>
#include"hotel.hpp"

class Hotel;

class Filter{
    public:
    virtual std::vector<Hotel*> doFilter(std::vector<Hotel*> hotels) = 0;
    Filter();
};
#endif