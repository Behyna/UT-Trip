#include "command.hpp"


using namespace std;

Command::Command(Utrip* utrip_, User* user_)
{
  utrip = utrip_;
  user = user_;
}
bool Command::isUserLogin()
{
  if (user == NULL)
  {
    throw PERMISSION_MSG;
  }
  else
  {
    return true;
  }
}