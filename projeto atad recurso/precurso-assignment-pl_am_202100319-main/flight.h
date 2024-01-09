#pragma once
#include "time.h"

typedef struct flight {
    int day;
    int dayOfWeek;
    char airline[3];
    int flightNumber;
    char originAirport[4];
    char destinationAirport[4];
    Time scheduledDeparture;
    Time departureTime;
    int realTravelTime; //to calculate
    int distance;
    Time scheduledArrival;
    Time arrivalTime;
    int totalDelay; //to calculate
} Flight;

typedef Flight* PtFlight;

/**
 * @brief Creates a flight with the day, day of the week, airline, flight number, origin airport, destination airport, scheduled departure time, departure time, real travel time,
 * distance travelled, scheduled arrival time, arrival time and total delay.
 * 
 * @param day day
 * @param dayOfWeek day of the week
 * @param airline airline
 * @param flightNumber flight number
 * @param originAirport origin airport
 * @param destinationAirport destination airport
 * @param scheduledDeparture scheduled departure time
 * @param departureTime departure time
 * @param realTravelTime real travel time
 * @param distance distance travelled
 * @param scheduledArrival scheduled arrival time
 * @param arrivalTime arrival time
 * @param totalDelay total delay
 * @return Flight 
 */
Flight flightCreate(int day, int dayOfWeek, char airline[3], int flightNumber, char originAirport[4], char destinationAirport[4], Time scheduledDeparture, Time departureTime,
int realTravelTime, int distance, Time scheduledArrival, Time arrivalTime, int totalDelay);

/**
 * @brief Prints the information of a flight.
 * 
 * @param ptFlight pointer to the flight
 */
void flightPrint(PtFlight ptFlight);