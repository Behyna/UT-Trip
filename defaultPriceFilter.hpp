#ifndef DEFAULT_PRICE_FILTER_HPP
#define DEFAULT_PRICE_FILTER_HPP "DEFAULT_PRICE_FILTER_HPP"

#include<string>

#include"filter.hpp"

class DefaultPriceFilter:public Filter{
    public:
    DefaultPriceFilter(std::pair<double, double> _stats);
    std::vector<Hotel*> doFilter(std::vector<Hotel*> hotels);

    private:
    std::pair<double, double> stats;
};

#endif