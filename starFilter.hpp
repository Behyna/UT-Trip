#ifndef STARFILTER_HPP
#define STARFILTER_HPP "STARFILTER_HPP"

#include"filter.hpp"

#include<string>

class StarFilter:public Filter{
    public:
    StarFilter(int minStar, int maxStar);
    std::vector<Hotel*> doFilter(std::vector<Hotel*> hotels);

    private:
    int minStarRating;
    int maxStarRating;
};

#endif