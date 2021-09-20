#ifndef AVERAGEPRICEFILTER_HPP
#define AVERAGEPRICEFILTER_HPP "AVERAGEPRICEFILTER_HPP"

#include"filter.hpp"

#include<string>

class AveragePriceFilter:public Filter{
    public:
    AveragePriceFilter(int minPrice, int maxPrice);
    std::vector<Hotel*> doFilter(std::vector<Hotel*> hotels);

    private:
    int minAveragePrice;
    int maxAveragePrice;
};

#endif