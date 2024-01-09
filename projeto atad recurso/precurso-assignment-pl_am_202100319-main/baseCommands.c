#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseCommands.h"
#include "input.h"
#include "time.h"
#include "utils.h"

#define MAP_INITIAL_CAPACITY 350

//load airports
PtMap loadAirports() {
    FILE *stream = fopen("csv_data/airports.csv", "r");

    /* If file does not exist, abort */
    if(stream == NULL) {
        printf("File not found\n");
        return NULL;
    }

    PtMap map = mapCreate(MAP_INITIAL_CAPACITY);

    int count = 0;
    char line[1024];
    while(fgets(line, 1024, stream)) {
        if(count == 0) {
            count++;
            continue;
        }

        char *tmp = strdup(line);

        /* creates tokens[7] array, with tokens read from the file line */
        char **split = splitString(tmp, 7, ";");

        int timeZone = atoi(split[6]);

        MapKey key = stringCodeCreate(split[0]);
        MapValue airport = airportCreate(split[0], split[1], split[2], split[3], timeZone);

        mapPut(map, key, airport);

        count++;
        free(tmp);
        free(split);
    }

    fclose(stream);

    printf("<%d> airport records imported\n", count-1);

    return map;
}

//load flights
PtList loadFlights(PtMap airports) {
    FILE *stream = fopen("csv_data/flights.csv", "r");

    if(airports == NULL) {
        printf("Please load airport data first\n");
        return NULL;
    }

    /* If file does not exist, abort */
    if(stream == NULL) {
        printf("File not found\n");
        return NULL;
    }

    PtList list = listCreate();

    int count = 0;
    char line[1024];
    while (fgets(line, 1024, stream)) {
        if(count == 0) {
            count++;
            continue;
        }
    
        char *tmp = strdup(line);

        /* creates tokens[11] array, with tokens read from the file line */
        char **split = splitString(tmp, 11, ";");

        MapKey originAirportKey = stringCodeCreate(split[4]);
        MapKey destinationAirportKey = stringCodeCreate(split[5]);

        int day = atoi(split[0]);
        int dayOfWeek = atoi(split[1]);
        int flightNumber = atoi(split[3]);

        Time scheduledDeparture = createTime(atoi(split[6]) / 100, atoi(split[6]) % 100);
        Time departureTime = createTime(atoi(split[7]) / 100, atoi(split[7]) % 100);

        int distance = atoi(split[8]);

        Time scheduledArrival = createTime(atoi(split[9]) / 100, atoi(split[9]) % 100);
        Time arrivalTime = createTime(atoi(split[10]) / 100, atoi(split[10]) % 100);

        //get map values for the origin and destination airport keys to help calculate realTravelTime
        MapValue originAirportValue;
        MapValue destinationAirportValue;

        mapGet(airports, originAirportKey, &originAirportValue);
        mapGet(airports, destinationAirportKey, &destinationAirportValue);

        //use abs function to get the absolute value, which represents the difference between the airports' time zones
        int timeZoneDiff = abs(originAirportValue.timeZone - destinationAirportValue.timeZone);
        int realTravelTime = timeDiffSpecial(departureTime, arrivalTime) + timeZoneDiff;

        int totalDelay = abs(timeDiffSpecial(scheduledDeparture, departureTime)) + abs(timeDiffSpecial(scheduledArrival, arrivalTime));

        Flight flight = flightCreate(day, dayOfWeek, split[2], flightNumber, split[4], split[5], scheduledDeparture, departureTime, realTravelTime, distance,
                                     scheduledArrival, arrivalTime, totalDelay);

        listAdd(list, count-1, flight);

        count++;
        free(tmp);
        free(split);
    }

    fclose(stream);

    printf("<%d> flight records imported\n", count-1);

    return list;
}

//load airlines
PtAirline loadAirlines(PtList flights) {
    FILE *stream = fopen("csv_data/airlines.csv", "r");

    if(flights == NULL) {
        printf("Please load flight data first\n");
        return NULL;
    }

    /* If file does not exist, abort */
    if(stream == NULL) {
        printf("File not found\n");
        return NULL;
    }

    PtAirline airlines = (Airline*)malloc(ARRAY_CAPACITY * sizeof(Airline));

    int count = 0;
    char line[1024];
    while(fgets(line, 1024, stream)) {
        if(count == 0) {
            count++;
            continue;
        }

        char *tmp = strdup(line);

        /* creates tokens[2] array, with tokens read from the file line */
        char **split = splitString(tmp, 2, ";");
        
        //calculate number of flights for each airline
        int nFlights = 0;

        int size;
        listSize(flights, &size);
        for(int i = 0; i < size; i++) {
            Flight flight;
            listGet(flights, i, &flight);
            if(strcmp(split[0], flight.airline) == 0) {
                nFlights++;
            }
        }

        Airline airline = airlineCreate(split[0], split[1], nFlights);

        airlines[count-1] = airline;

        count++;
        free(tmp);
        free(split);
    }

    fclose(stream);

    printf("<%d> airline records imported\n", count-1);

    return airlines;
}

void clear(PtList flights, PtMap airports, PtAirline airlines) {
    int size1 = 0;
    int size2 = 0;
    int size3 = 0;
    int numRecords = 0;

    if(flights != NULL)
        listSize(flights, &size1);
        listDestroy(&flights);

    if(airports != NULL)
        mapSize(airports, &size2);
        mapDestroy(&airports);

    if(airlines != NULL)
        size3 = ARRAY_CAPACITY;
        free(airlines);

    numRecords = size1 + size2 + size3;

    printf("<%d> records deleted from <Flights | Airports | Airlines>\n", numRecords);
}