#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

Airport airportCreate(char* code, char* designation, char* city, char* state, int timeZone) {
    Airport ap;
    strcpy(ap.iataCode, code);
    strcpy(ap.airport, designation);
    strcpy(ap.city, city);
    strcpy(ap.state, state);
    ap.timeZone = timeZone;

    return ap;
}

void airportPrint(PtAirport ptAirport) {
    printf("%-6s  %-50s  %-30s  %-4s  %d\n", ptAirport->iataCode, ptAirport->airport, ptAirport->city, ptAirport->state, ptAirport->timeZone);
}