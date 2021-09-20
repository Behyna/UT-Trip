#ifndef USER_RATINGS_HPP
#define USER_RATINGS_HPP "USER_RATINGS_HPP"

#include <string>
#include <vector>

class UserRatings{
public:
    UserRatings(std::vector<double> _ratings, std::string _username);
    std::vector<double> getRating(){return ratings;};
    std::string getUsername(){return username;};
    
private:
    std::string username;
    std::vector<double> ratings;
};

#endif