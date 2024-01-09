#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Flight flightCreate(int day, int dayOfWeek, char airline[3], int flightNumber, char originAirport[4], char destinationAirport[4], Time scheduledDeparture, Time departureTime, 
int realTravelTime, int distance, Time scheduledArrival, Time arrivalTime, int totalDelay) {
    Flight f;
    f.day = day;
    f.dayOfWeek = dayOfWeek;
    strcpy(f.airline, airline);
    f.flightNumber = flightNumber;
    strcpy(f.originAirport, originAirport);
    strcpy(f.destinationAirport, destinationAirport);
    f.scheduledDeparture = scheduledDeparture;
    f.departureTime = departureTime;
    f.realTravelTime = realTravelTime;
    f.distance = distance;
    f.scheduledArrival = scheduledArrival;
    f.arrivalTime = arrivalTime;
    f.totalDelay = totalDelay;

    return f;
}

void flightPrint(PtFlight ptFlight) {
    char scheduledDepartureHour[5];
    timeFormatToString(ptFlight->scheduledDeparture, scheduledDepartureHour);

    printf(" %-4d     %-4d      %-5s      %-10d   %-7s   %-7s         %-10s  ", ptFlight->day, ptFlight->dayOfWeek, ptFlight->airline,
                                                                 ptFlight->flightNumber, ptFlight->originAirport, 
                                                                 ptFlight->destinationAirport, scheduledDepartureHour);

    char departureTimeHour[5];
    timeFormatToString(ptFlight->departureTime, departureTimeHour);
    printf("        %-10s  ", departureTimeHour);

    char scheduledArrivalHour[5];
    timeFormatToString(ptFlight->scheduledArrival, scheduledArrivalHour);

    printf("   %-10d   %-10d    %-10s  ", ptFlight->realTravelTime, ptFlight->distance, scheduledArrivalHour);

    char arrivalTimeHour[5];
    timeFormatToString(ptFlight->arrivalTime, arrivalTimeHour);
    printf("    %-10s    %-10d", arrivalTimeHour, ptFlight->totalDelay);
}