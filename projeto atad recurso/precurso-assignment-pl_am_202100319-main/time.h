#pragma once

typedef struct time {
	int hour, min;
} Time;

Time createTime(int hour, int min);
int timeDiff(Time time1,Time time2);
int timeDiffSpecial(Time time1,Time time2);

/**
 * @brief Formats the time inserted in the parameters into a string - hh:mm.
 *
 * @param time the time to format.
 * @param str the string to hold the value of the time in string format.
 */
void timeFormatToString(Time time, char* str);