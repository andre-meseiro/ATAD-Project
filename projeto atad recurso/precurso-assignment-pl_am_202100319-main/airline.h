#pragma once

typedef struct airline {
    char iatacode[3];
    char airline[100];
    int nFlights; //to calculate
} Airline;

typedef Airline *PtAirline;

/**
 * @brief Creates an airline with the code, designation and number of flights.
 *
 * @param code airline code
 * @param designation airline designation
 * @param numFlights number of flights
 * @return Airline
 */
Airline airlineCreate(char *code, char *designation, int numFlights);

/**
 * @brief Prints the information of an airline.
 *
 * @param ptAirline pointer to the airline
 */
void airlinePrint(PtAirline ptAirline);