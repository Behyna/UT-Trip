#ifndef COMMENT_HPP
#define COMMENT_HPP "COMMENT_HPP"

#include <string>
#include <vector>

class Comment{
public:
    Comment(std::string _text, std::string _username);
    std::string getText(){return text;};
    std::string getUsername(){return username;};
    
private:
    std::string username;
    std::string text;
    
};

#endif