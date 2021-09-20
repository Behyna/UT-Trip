#include "room.hpp"

#include <iostream>
using namespace std;

Room::Room(int roomsPrice)
{
  price = roomsPrice;
}
string Room::getId()
{
  return id;
}

bool Room::isReserved(int start, int end)
{
  return reserving.isReservedIn(start, end);
}

int Room::getPrice()
{
  return price;
}

void Room::reserve(int start, int end)
{
  reserving.reserve(start, end);
}

void Room::unreserve()
{
  reserving.unreserve();
}