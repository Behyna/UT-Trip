all:utrip.out

utrip.out: main.o userInterFace.o post.o get.o command.o utrip.o user.o hotel.o room.o \
		   standard.o deluxe.o luxury.o premium.o filter.o cityFilter.o\
		   starFilter.o averagePriceFilter.o roomFilter.o reservation.o comment.o userRatings.o\
		   defaultPriceFilter.o delete.o
	g++ -std=c++11 main.o userInterFace.o post.o get.o command.o utrip.o user.o hotel.o room.o\
		   standard.o deluxe.o luxury.o premium.o filter.o cityFilter.o\
		   starFilter.o averagePriceFilter.o roomFilter.o reservation.o comment.o userRatings.o\
		   defaultPriceFilter.o delete.o -o utrip.out
main.o: main.cpp userInterFace.hpp utrip.hpp
	g++ -std=c++11 -c main.cpp
userInterFace.o: userInterFace.cpp userInterFace.hpp utrip.hpp post.hpp
	g++ -std=c++11 -c userInterFace.cpp
post.o: post.cpp post.hpp command.hpp filter.hpp cityFilter.hpp starFilter.hpp averagePriceFilter.hpp utils.hpp roomFilter.hpp
	g++ -std=c++11 -c post.cpp
get.o: get.cpp get.hpp command.hpp 
	g++ -std=c++11 -c get.cpp
command.o: command.cpp command.hpp utrip.hpp
	g++ -std=c++11 -c command.cpp
utrip.o: utrip.cpp utrip.hpp hotel.hpp user.hpp utils.hpp
	g++ -std=c++11 -c utrip.cpp
user.o: user.cpp user.hpp reservation.hpp defaultPriceFilter.hpp defines.hpp
	g++ -std=c++11 -c user.cpp
hotel.o: hotel.cpp hotel.hpp room.hpp comment.hpp userRatings.hpp user.hpp
	g++ -std=c++11 -c hotel.cpp
filter.o: filter.cpp filter.hpp hotel.hpp
	g++ -std=c++11 -c filter.cpp
cityFilter.o: cityFilter.cpp cityFilter.hpp filter.hpp
	g++ -std=c++11 -c cityFilter.cpp
starFilter.o: starFilter.cpp starFilter.hpp filter.hpp
	g++ -std=c++11 -c starFilter.cpp
averagePriceFilter.o: averagePriceFilter.cpp averagePriceFilter.hpp filter.hpp
	g++ -std=c++11 -c averagePriceFilter.cpp
defaultPriceFilter.o: defaultPriceFilter.cpp defaultPriceFilter.hpp filter.hpp
	g++ -std=c++11 -c defaultPriceFilter.cpp
roomFilter.o: roomFilter.cpp roomFilter.hpp filter.hpp hotel.hpp
	g++ -std=c++11 -c roomFilter.cpp
room.o: room.cpp room.hpp
	g++ -std=c++11 -c room.cpp
standard.o: standard.cpp room.hpp
	g++ -std=c++11 -c standard.cpp
deluxe.o: deluxe.cpp room.hpp
	g++ -std=c++11 -c deluxe.cpp
luxury.o: luxury.cpp room.hpp
	g++ -std=c++11 -c luxury.cpp
premium.o: premium.cpp room.hpp
	g++ -std=c++11 -c premium.cpp
reservation.o: reservation.cpp reservation.hpp
	g++ -std=c++11 -c reservation.cpp
comment.o: comment.cpp comment.hpp
	g++ -std=c++11 -c comment.cpp
userRatings.o: userRatings.cpp userRatings.hpp
	g++ -std=c++11 -c userRatings.cpp
delete.o: delete.cpp delete.hpp command.hpp
	g++ -std=c++11 -c delete.cpp



clean:
	rm *.out
	rm *.o
