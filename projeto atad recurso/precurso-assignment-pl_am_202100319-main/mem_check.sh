!#/bin/sh

make
valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./prog