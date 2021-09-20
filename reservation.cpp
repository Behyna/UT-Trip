#include "reservation.hpp"

Reservation::Reservation(int _id, std::string _hotelId, std::string _type, int _quantity, int _cost,
                         int _checkIn, int _checkOut, std::vector<Room*> _rooms)
{
    id = _id;
    hotelId = _hotelId;
    type = _type;
    quantity = _quantity;
    cost = _cost;
    checkIn = _checkIn;
    checkOut = _checkOut;
    rooms = _rooms;

}

int Reservation::getId(){return id;};
std::string Reservation::getHotelId(){return hotelId;};
std::string Reservation::getType(){return type;};
int Reservation::getQuantity(){return quantity;};
int Reservation::getCost(){return cost;};
int Reservation::getCheckIn(){return checkIn;};
int Reservation::getCheckOut(){return checkOut;};
void Reservation::unreserveRooms(){
    for (int i=0; i<rooms.size(); i++)
        rooms[i]->unreserve();
}
int Reservation::getPrice(){return cost/quantity;};