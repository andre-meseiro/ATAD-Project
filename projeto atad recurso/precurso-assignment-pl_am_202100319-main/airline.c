#include "airline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Airline airlineCreate(char *code, char *designation, int numFlights) {
    Airline al;
    strcpy(al.iatacode, code);
    strcpy(al.airline, designation);
    al.nFlights = numFlights;

    return al;
}

void airlinePrint(PtAirline ptAirline) {
    printf("%-9s  %-30s  %d\n"    , ptAirline->iatacode, ptAirline->airline, ptAirline->nFlights);
}