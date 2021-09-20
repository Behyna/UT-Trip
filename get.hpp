#ifndef GET_HPP
#define GET_HPP "GET_HPP"

#include "command.hpp"
class Get:public Command{
    public:
    Get(Utrip* utrip_, User* user_);
    void doCommand(std::vector<std::string> data);
    
    private:
    void hotels(std::vector<std::string> data);
    void reserves(std::vector<std::string> data);
    void wallet(std::vector<std::string> data);
    void comments(std::vector<std::string> data);
    void ratings(std::vector<std::string> data);
    void manualWeights(std::vector<std::string> data);
    void estimatedWeights(std::vector<std::string> data);
};
#endif