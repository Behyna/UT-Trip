#include "standard.hpp"

#define STANDARD_ID_PREFIX "s"

using namespace std;

Standard::Standard(int standardRoomsPrice, string standardRoomsId):Room(standardRoomsPrice)
{
  id = STANDARD_ID_PREFIX + standardRoomsId;
}
