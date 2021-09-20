#include "premium.hpp"

#define PREMIUM_ID_PREFIX "p"

using namespace std;

Premium::Premium(int premiumRoomsPrice, std::string premiumRoomsId):Room(premiumRoomsPrice)
{
  id = PREMIUM_ID_PREFIX + premiumRoomsId;
}
