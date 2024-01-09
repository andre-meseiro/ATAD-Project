#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "utils.h"
#include "list.h"
#include "map.h"
#include "input.h"
#include "airline.h"
#include "baseCommands.h"
#include "indicatorCommands.h"

void printCommandsMenu();
void waitFunction();

int main()
{

	srand(time(NULL));

	/* commands interpreter */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");

	PtMap airports = NULL;
	PtList flights = NULL;
	PtAirline airlines = NULL;

	while (!quit)
	{

		printCommandsMenu();
		readString(command,sizeof(command));

		if (equalsStringIgnoreCase(command, "LOADAP"))
		{
			airports = loadAirports();
		}
		else if (equalsStringIgnoreCase(command, "LOADF"))
		{
			if(airports == NULL) {
				printf("Please load airport data first");
				waitFunction();
			}
			else {
				flights = loadFlights(airports);
			}
		}
		else if (equalsStringIgnoreCase(command, "LOADAR"))
		{	
			if(flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}
			else {
				airlines = loadAirlines(flights);
			}
		}
		else if (equalsStringIgnoreCase(command, "CLEAR"))
		{
			clear(flights, airports, airlines);

			airports = NULL;
			flights = NULL;
			airlines = NULL;
		}	
		else if (equalsStringIgnoreCase(command, "SHOWALL"))
		{
			if(flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}
			else
				showAll(flights);
		}
		else if (equalsStringIgnoreCase(command, "SHOWF"))
		{
			if(flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}
			else {
				char originCode[5];
				char destinationCode[5];

				printf("Insert origin airport code: ");
				readString(originCode, 5);

				printf("Insert destination airport code: ");
				readString(destinationCode, 5);
				printf("\n");

				showF(flights, originCode, destinationCode);
			}
		}
		else if (equalsStringIgnoreCase(command, "LISTAR"))
		{
			if (flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}
			else if (airlines == NULL) {
				printf("Please load airline information first");
				waitFunction();
			}
			else
				listAr(flights, airlines);
		}
		else if (equalsStringIgnoreCase(command, "TOPDISTN"))
		{
			if (flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}

			int number;

			printf("Insert a value N positive below 11515: ");
			readInteger(&number);
			printf("\n");

			if (number <= 0 || number >= 11515) {
				printf("Invalid value");
				waitFunction();
			}
			else 
				topDistN(flights, number);

		}
		else if(equalsStringIgnoreCase(command, "LISTAP"))
		{
			if(airports == NULL) {
				printf("Please load airport information first");
				waitFunction();
			}
			else if(flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}
			else
				listAp(airports, flights);
		}
		else if(equalsStringIgnoreCase(command, "DELAYS"))
		{
			if(flights == NULL) {
				printf("Please load flight information first");
				waitFunction();
			}
			else if(airlines == NULL) {
				printf("Please load airline information first");
				waitFunction();
			}

			int tolerance;

			printf("Insert a tolerance (between 0 and 30 minutes): ");
			readInteger(&tolerance);
			printf("\n");

			if (tolerance < 0 || tolerance > 30) {
				printf("Invalid value");
				waitFunction();
			}
			else
				delays(flights, airlines, tolerance);
		}
		else if (equalsStringIgnoreCase(command, "QUIT"))
		{	
			clear(flights, airports, airlines);

			airports = NULL;
			flights = NULL;
			airlines = NULL;

			quit = 1; /* vai provocar a saída do interpretador */
		}
		else
		{
			printf("Command not found!\n");
			waitFunction();
		}
	}

	printf("Good Bye! ...\n");
}


void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. Base commands (LOADAR, LOADAP, LOADF, CLEAR).");
	printf("\nB. Aggregated info about flights (SHOWALL, SHOWF, LISTAR, LISTAP, DELAYS, AVERAGEDELAY,");
    printf("\n   SHOWAP, TOPDISTN).");
	printf("\nC. Complex Indicators require airports and flights data (AIRPORT_S, AIRLINES).");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}

void waitFunction() {
	printf("\nPress enter to continue ...");
	getchar();
}
