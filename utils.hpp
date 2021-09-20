#ifndef UTILS_HPP
#define UTILS_HPP "UTILS_HPP"

#include <string>
#include <sstream> 

int convertStringToInt(std::string line)
{
  int number;
  std::stringstream temp(line);
  temp >> number;
  return number;
}


#endif