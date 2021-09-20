#ifndef RESERVATION_HPP
#define RESERVATION_HPP "RESERVATION_HPP"

#include <string>
#include <vector>
#include "room.hpp"

class Reservation{
public:
    Reservation(int _id, std::string _hotelId, std::string _type, int _quantity, int _cost, int _checkIn,
                int _checkOut, std::vector<Room*> rooms);
    int getId();
    std::string getHotelId();
    std::string getType();
    int getQuantity();
    int getCost();
    int getCheckIn();
    int getCheckOut();
    void unreserveRooms();
    int getPrice();

private:
    int id;
    std::string hotelId;
    std::string type;
    int quantity;
    int cost;
    int checkIn;
    int checkOut;
    std::vector<Room*> rooms;
};

#endif