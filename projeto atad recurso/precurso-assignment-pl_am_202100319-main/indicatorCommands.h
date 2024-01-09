/**
 * @file indicatorCommands.h
 * 
 * @brief Simple indicator commands to show information of flights and airlines.
 * 
 * @author André Meseiro - 202100225
 * @author Pedro Lopes - 202100319
 * 
 * @details Turma 7 Miguel Bugalho.
 */

#pragma once

#include "airline.h"
#include "airport.h"
#include "flight.h"
#include "input.h"
#include "list.h"
#include "listElem.h"
#include "map.h"
#include "time.h"
#include "utils.h"

/**
 * @brief Shows every flight information, depending on the user's choice, either in pages of 30 max, or random 80.
 * 
 * @param flights pointer to the list that contains the flights
 */
void showAll(PtList flights);

/**
 * @brief Menu for the user to choose in which way the flights will be shown (used in showAll function).
 * 
 * @return int 
 */
int showAllMenu();

/**
 * @brief Shows information about the flights that have the desired route (origin and destination airports).
 * 
 * @param flights pointer to the list that contains the flights
 * @param originCode origin airport code
 * @param destinationCode destination airport code
 */
void showF(PtList flights, char *originCode, char *destinationCode);

/**
 * @brief Calculates a new list of flights which have the origin and destination intended and prints their information (used in showF function).
 * 
 * @param flights pointer to the list that contains the flights
 * @param origin origin airport name
 * @param destination destination airport name
 */
void showFlightsWithRoute(PtList flights, char *origin, char *destination);

/**
 * @brief Checks if a certain airline has flights or not.
 * 
 * @param flights pointer to the list that contains the flights
 * @param airlineCode code of the airline
 * @return true
 * @return false
 */
bool hasFlightsUnique(PtList flights, char *airlineCode);

/**
 * @brief Shows the list of unique airlines that contain flights.
 * 
 * @param flights pointer to the list that contains the flights
 * @param airlines pointer to the struct that contains the airlines
 */
void listAr(PtList flights, PtAirline airlines);

/**
 * @brief Sorts flights by ascending distance and descending flightNumber in the event of a tie; Prints the information of the sorted flights.
 * 
 * @param flights pointer to the list that contains the flights
 * @param n the number of flights to print
 */
void topDistN(PtList flights, int n);

/**
 * @brief Shows the list of unique airports that contain flights.
 * 
 * @param airports pointer to the map that contains the airports
 * @param flights pointer to the list that contains the flights
 */
void listAp(PtMap airports, PtList flights);

/**
 * @brief Loops flights to check if they have flights with delays above the tolerance, associated with an airline and prints them.
 * 
 * @param flights pointer to the list that contains the flights
 * @param airlineName airline name
 * @param tol tolerance
 */
void calcDelayedFlights(PtList flights, char *airlineName, int tol);

/**
 * @brief Shows airports that contain airlines with flights that have delays bigger than the given tolerance in them.
 * 
 * @param flights pointer to the list that contains the flights
 * @param airlines pointer to the struct that contains the airlines
 * @param tol tolerance
 */
void delays(PtList flights, PtAirline airlines, int tol);