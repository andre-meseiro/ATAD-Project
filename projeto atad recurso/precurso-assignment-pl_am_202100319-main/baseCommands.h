/**
 * @file baseCommands.h
 * 
 * @brief Base commands to load information from the csv files and also clear it.
 * 
 * @author André Meseiro - 202100225
 * @author Pedro Lopes - 202100319
 * 
 * @details Turma 7 Miguel Bugalho.
 */

#pragma once
#include "airport.h"
#include "flight.h"
#include "airline.h"
#include "list.h"
#include "map.h"
#define ARRAY_CAPACITY 14

/**
 * @brief Loads information from the airports csv file into an ADT Map.
 *
 * @return PtMap
 */
PtMap loadAirports();

/**
 * @brief Loads information from the flights csv file into an ADT List.
 *
 * @param airports pointer to the map that contains the airports
 * @return PtList
 */
PtList loadFlights(PtMap airports);

/**
 * @brief Loads information from the airlines csv file into an array.
 *
 * @param flights pointer to the list that contains the flights
 * @return PtAirline
 */
PtAirline loadAirlines(PtList flights);

/**
 * @brief Clears all the information.
 *
 * @param flights pointer to the list that contains the flights
 * @param airports pointer to the map that contains the airports
 * @param airlines pointer to the struct that contains the airlines
 */
void clear(PtList flights, PtMap airports, PtAirline airlines);