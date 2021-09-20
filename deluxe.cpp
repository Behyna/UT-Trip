#include "deluxe.hpp"

#define DELUXE_ID_PREFIX "d"

using namespace std;

Deluxe::Deluxe(int deluxeRoomsPrice, string deluxeRoomsId):Room(deluxeRoomsPrice)
{
  id = DELUXE_ID_PREFIX + deluxeRoomsId;
}
