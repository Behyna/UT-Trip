#ifndef DELETE_HPP
#define DELETE_HPP "DELETE_HPP"

#include "command.hpp"
class Delete:public Command{
    public:
    Delete(Utrip* utrip_, User* user_);
    void doCommand(std::vector<std::string> data);
    
    private:
    void filters(std::vector<std::string> data);
    void reserves(std::vector<std::string> data);
};
#endif