#include "luxury.hpp"

#define LUXURY_ID_PREFIX "l"

using namespace std;

Luxury::Luxury(int luxuryRoomsPrice, std::string luxuryRoomsId):Room(luxuryRoomsPrice)
{
  id = LUXURY_ID_PREFIX + luxuryRoomsId;
}
