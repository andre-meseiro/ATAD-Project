#pragma once

typedef struct airport {
    char iataCode[4];
    char airport[100];
    char city[35];
    char state[3];
    int timeZone;
} Airport;

typedef Airport *PtAirport;

/**
 * @brief Creates an airport with the code, designation, city, state and time zone.
 * 
 * @param code airport code
 * @param designation airport designation
 * @param city city
 * @param state state
 * @param timeZone time zone
 * @return Airport 
 */
Airport airportCreate(char code[4], char airportName[100], char city[35], char state[3], int timeZone);

/**
 * @brief Prints the information of an airport.
 * 
 * @param ptAirport pointer to the airport.
 */
void airportPrint(PtAirport ptAirport);
