#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "baseCommands.h"
#include "indicatorCommands.h"

//used in showAll
int showAllMenu() {
    printf("=== Menu (type a number 1-3 to select your option) ===\n");
    printf("1 - Show all flights (30 per page)\n");
    printf("2 - Show information of 80 random flights\n");
    printf("3 - Return to main menu \n");
    int option;
    readInteger(&option);
    return option;
}

void showAll(PtList flights) {
    int selectedOption = 0;

    do {
        selectedOption = showAllMenu();
        if(selectedOption == 1) {
            int size;
            listSize(flights, &size);

            //calculate number of pages that contain 30 flights and the number of the final page
            int numPages = size / 30 + 1;
            int numFinalPage = size - (numPages * 30);  

            ListElem flight;
            int currPage = 1;
            bool quit = false;

            while(quit  == false) {
                //get max and min pages
                int max = currPage * 30;
                int min = max - 30;

                printf("Day  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Real Travel Time  Distance  Scheduled Arrival  Arrival Time  Total Delay\n");

                for(int i = min; i < max; i++) {
                    listGet(flights, i, &flight);
                    flightPrint(&flight);
                    printf("\n");
                }

                //menu for the pages
                printf("\n");
                printf("Menu Pages\n");
                printf("1 - Next Page\n");
                printf("2 - Return\n");

                int menuPagesOption;
                readInteger(&menuPagesOption);

                if(menuPagesOption == 1)
                    currPage++;
                
                else if(menuPagesOption == 2)
                    quit = true;
            }
        }
        else if(selectedOption == 2) {
            printf("----------------------------------80 Random Flights Information----------------------------------\n");
            ListElem flight;
            int size;
            listSize(flights, &size);

            /*the use of srand (generate random seed) in combo with time(0) function from c library (which gives the local time right now), will help us generate 80 random flights
            right now which will change every time we execute the command*/
            srand(time(0));
            
            //define a min, max and count
            int min = 0;
            int max = (size - 81);
            int count = 0;

            //get a random value by using the rand fuction
            int random = (rand() % (min - max + 1)) + min;

            //loop flights and print 80 random ones
            printf("Day  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Real Travel Time  Distance  Scheduled Arrival  Arrival Time  Total Delay\n");
            for(int i = random; i < random + 79; i++) {
                listGet(flights, i, &flight);
                flightPrint(&flight);
                printf("\n");
                count++;
            }
        }
    } while(selectedOption != 3);
}

//used in showF
void showFlightsWithRoute(PtList flights, char *originCode, char *destinationCode) {
    //create a new list
    PtList list = listCreate();

    //search flights for flights that have the same origin and destination as the ones we want and add them to the new list
    int size;
    listSize(flights, &size);
    Flight flight;

    for(int i = 0; i < size; i++) {
        int count = 0;
        listGet(flights, i, &flight);
        if(equalsStringIgnoreCase(flight.originAirport, originCode) == 1 && equalsStringIgnoreCase(flight.destinationAirport, destinationCode) == 1) {
            listAdd(list, count, flight);
            count++;
        }
    }

    //print information about the flights
    int newListSize;
    listSize(list, &newListSize);
    Flight elem;
    
    if(newListSize == 0) {
        printf("Flight data not available for route <%s> ==> <%s>", originCode, destinationCode);
    }

    else {  
        printf("----------------------------------Flights With Desired Route----------------------------------\n");
        printf("Day  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Real Travel Time  Distance  Scheduled Arrival  Arrival Time  Total Delay\n");
        for(int i = 0; i < newListSize; i++) {
            listGet(list, i, &elem);
            flightPrint(&elem);
            printf("\n");
        }
    }

    listDestroy(&list);
}

void showF(PtList flights, char *originCode, char *destinationCode) {
    if(flights != NULL && originCode != NULL && destinationCode != NULL) {
        showFlightsWithRoute(flights, originCode, destinationCode);
    }
}

//used in listAr, we use the code of the airline instead of the name to make sure it's unique
bool hasFlightsUnique(PtList flights, char *airlineCode) {
    int size;
    listSize(flights, &size);
    Flight flight;

    for(int i = 0; i < size; i++) {
        listGet(flights, i, &flight);
        if(equalsStringIgnoreCase(flight.airline, airlineCode) == 1)
            return true;
    }

    return false;
}

void listAr(PtList flights, PtAirline airlines) {
    printf("----------Airlines With Flights----------\n");
    printf("Iata Code  Name                            Number of Flights\n");
    for(int i = 0; i < ARRAY_CAPACITY; i++) {
        if(hasFlightsUnique(flights, airlines[i].iatacode) == true)
            airlinePrint(&airlines[i]);
    }
}

void topDistN(PtList flights, int n) {
    int size;
    PtList sorted = listCreate();
    Flight aux, f1, f2;
    listSize(flights, &size);

    //copy of array list flights
    for(int i = 0; i < size; i++) {
        listGet(flights, i, &aux);
        listAdd(sorted, i, aux);       
    }
    
    //sort flights by ascending distance; in the event of a tie, sorts by descending flight number
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size-1-i; j++) {
            listGet(sorted, j, &f1);
            listGet(sorted, j+1, &f2);
            if(f1.distance > f2.distance) {
                listSet(sorted, j, f2, &f1);
                listSet(sorted, j+1, f1, &f2);
            }
            else if(f1.distance == f2.distance) {
                if(f1.flightNumber < f2.flightNumber) {
                    listSet(sorted, j, f2, &f1);
                    listSet(sorted, j+1, f1, &f2);
                }
            }
        }
    }
    
    printf("----------TOPDISTN----------\n");
    printf("Day  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Real Travel Time  Distance  Scheduled Arrival  Arrival Time  Total Delay\n");
    for(int i = 0; i < n; i++) {
        listGet(sorted, i, &aux);
        flightPrint(&aux);
        printf("\n");
    }
}

void listAp(PtMap airports, PtList flights) {
    int size1, size2;
    int count;

    mapSize(airports, &size1);
    listSize(flights, &size2);

    ListElem flight;

    //get airport map keys
    MapKey *airportKeys;
    airportKeys = mapKeys(airports);

    //create new map with airports that contain flights
    PtMap airportsWithFlights = mapCreate(20);

    Airport airport;

    //loop flights list to find flights associated with an airport and put them in the new map
    for(int i = 0; i < size1; i++) {
        for(int j = 0; j < size2; j++) {
            listGet(flights, j, &flight);

            StringCode originCode = stringCodeCreate(flight.originAirport);
            StringCode destinationCode = stringCodeCreate(flight.destinationAirport);
            StringCode airportCode = airportKeys[i];

            if(equalsStringIgnoreCase(airportCode.code, originCode.code) || equalsStringIgnoreCase(airportCode.code, destinationCode.code)) {
                if(!mapContains(airportsWithFlights, airportCode)) {
                    mapGet(airports, airportCode, &airport);
                    mapPut(airportsWithFlights, airportCode, airport);
                }
            }
        }
    }

    mapSize(airportsWithFlights, &count);

    printf("--------- Airports List ---------\n");

    //get new map keys and values
    MapKey *awfKeys = mapKeys(airportsWithFlights);
    MapValue *awfValues = mapValues(airportsWithFlights);
    //loop and print information on the requested format
    for(int i = 0; i < count; i++) 
        printf("%-3s: %-50s %-20s %-4s UTC%d:00\n", awfKeys[i].code, awfValues[i].airport, awfValues[i].city, awfValues[i].state, awfValues[i].timeZone);
    
    printf("----------------------------------\n");
    printf("%d airports were found on the records\n", count);

    //manage alocated memory to the new map
    mapValues(airportsWithFlights);
    mapDestroy(&airportsWithFlights);
}

//used in delays
void calcDelayedFlights(PtList flights, char *airlineName, int tol) {
    int size;
    int depDelay = 0;
    int arrDelay = 0;

    listSize(flights, &size);

    Flight aux;

    /*loop flights to check if the current flight is associated with the airline passed in the arguments; 
    In the case of it being true, calculates the departure and arrival delay to check if it's bigger than the given tolerance and increments the respective counts
    */
    for(int i = 0; i < size; i++) {
        listGet(flights, i, &aux);
        if(equalsStringIgnoreCase(airlineName, aux.airline)) {
            if(timeDiffSpecial(aux.scheduledDeparture, aux.departureTime) > tol) 
                depDelay++;
            
            if(timeDiffSpecial(aux.scheduledArrival, aux.arrivalTime) > tol) 
                arrDelay++;
        }
    }

    //check if the counts are bigger than 0, and prints the information
    if(depDelay > 0 && arrDelay > 0) 
        printf("%7s %19d %17d\n", airlineName, depDelay, arrDelay);
}

void delays(PtList flights, PtAirline airlines, int tol) {
    printf("Airline  Delayed_Departures  Delayed_Arrivals\n");  
    for (int i = 0; i < ARRAY_CAPACITY; i++)
        calcDelayedFlights(flights, airlines[i].iatacode, tol);
}