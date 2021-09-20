#ifndef ROOM_H
#define ROOM_H "ROOM_H"

#include<string>

class Reserve{
public:
  Reserve(){reserved = false;};
  bool isReserved(){return reserved;};
  bool isReservedIn(int start, int end){ return reserved && (start >= checkIn) && (end <= checkOut); }
  void reserve(int start, int end){checkIn = start; checkOut = end; reserved = true;};
  void unreserve(){reserved = false;};
private:
  bool reserved;
  int checkIn;
  int checkOut;
};

class Room{

public:
  Room(int roomsPrice);
  std::string getId();
  bool isReserved(int start, int end);
  int getPrice();
  void reserve(int start, int end);
  void unreserve();

protected:
  std::string id;
  int price;
  Reserve reserving;

};
#endif
