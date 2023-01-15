#ifndef BUS_H
#define BUS_H
#include"logger.h"
#include"header.h"
#include <iostream>
#include<cstring>
using namespace std;

// CLASS BUS
class Bus
{
private:
    int maxSeats, bookedSeats;
    double busFare;
    char busNo[SIZE], source[BUFFER_SIZE], destination[BUFFER_SIZE], sourceTime[BUFFER_SIZE], destinationTime[BUFFER_SIZE];

public:
    Bus()
    {
        strcpy(busNo, "");
        maxSeats = 32;
        bookedSeats = 0;
        busFare = 0.0;
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(sourceTime, "");
        strcpy(destinationTime, "");
        LOG_INFO("Bus Default constructor invoked");
    }

    // METHODS
    void addBus();
    void showAllBus();
    void showBusDetails();
    void viewBusDetails();
    void deleteBus();
    void editBus();

    // GETTERS
    char *getBusNo();
    char *getSource();
    char *getDestination();
    char *getSourceTime();
    char *getDestinationTime();
    int getBookedSeats();
    int getMaxSeats();
    double getBusFare();
    
    // SETTERS
    void setBookedSeats();
    void setCancelTicket();
    void setSource(char*);
    void setDestination(char *);
    void setSourceTime(char*);
    void setDestinationTime(char*);
    void setBusFare(double);
    ~Bus(){
        LOG_INFO("\nBus Destructor invoked");
    }
};
#endif //BUS_H
