/**
*	Author: Nathaniel Mendoza
*	Problem: Surviving Arizona
 A produce warehouse in Arizona has a number of Air Conditioning units 
installed in a successive manner, all in a row. Each AC unit has a light indicator 
which identifies is current operation status. Green light is turned on for a fixed 
number of seconds which indicates the unit is currently operating, then the unit 
turns Yellow for a fixed number of seconds indicating it is currently in 
temporary cool off state to prevent overheating, then turns Red for a fixed 
number of seconds indicating it has overheated. To prevent an overload on the 
main power supply this cycle is repeated for each AC unit, which have their 
own set of timings. When all units are initially turned on, they start at the 
beginning of their cycle with a Green light. Given N AC units, with their 
respective timings, compute the earliest time (in seconds) when all lights show 
Red. 
In the example above, AC unit #1 turns Red at the 5th second, but when this 
happens, AC unit #2 is Yellow. At the 8th second, AC Unit #2 is Red but AC 
unit #1 has cycled through and is Green again. You can verify that in the 18th 
second, both units are Red. You can assume the total maximum cycle (adding 
Green, Yellow and Red times) is 99 seconds. You can assume 0 < N < 5 and 
each Green, Yellow and Red time period is at least 1 second long. 

Description of Input 
 
Your program will read from standard input. The first line will contain a 
positive integer on a line by itself representing the number of AC units, N. The 
next N lines represent the lights. Each line of input will contain three positive 
integers separated by spaces – G, Y and R – representing the number of seconds 
that light is Green, then Yellow, then Red. 
 
 
Description of Output 
 
You must output a single positive integer on a line by itself representing the 
earliest time (in seconds) when all N lights show red. 

Sample Case 
 
Input 
 
2 
2 2 2 
4 3 3 
 
Output 
 
18 
*/

#include <iostream>

int getTotalTime(int content[][2], int index);
bool isRed(int content[][2], int index, int currentTime);
bool allRed(bool status[], int total);

int main(int argc, const char *argv[])
{
	
	//count for total number of AC units
    int acCount = 0;

    std::cin >> acCount;

	//array to store the AC unit (rows) and the time states
	// index 0 = time that AC is NOT red
	// index 1 = time that AC is Red
    int content[5][2];
	
	//parallel array to content, storage whether or not the AC unit is at Red status
    bool status[5];
	
	//initalize the content array
    for(int i = 0; i < acCount; ++i)
    {
	int numGreen, numYellow, numRed;
	std::cin >> numGreen;
	std::cin >> numYellow;
	std::cin >> numRed;
	
	content[i][0] = numGreen + numYellow;
	content[i][1] = numRed;
	
    }    
	
	//While loop that simulates time. 1 loop = 1 second
    int time = 1;
    while(true)
    {
	//Check the status of each AC unit (if red or not)
	for(int i = 0; i < acCount; ++i)
	{
	    status[i] = isRed(content, i, time);
	}
	
	//Check if ALL AC units are Red, if so, break loop
	if(allRed(status, acCount))
	    break;

	++time;
    }

    std::cout << time << "\n";

    return 0;
}

/**
*	getTotalTime: int
*	returns an integer value on the total cycle time of an AC unit given an index in the array
*/
int getTotalTime(int content[][2], int index)
{
    return (content[index][0] + content[index][1]);
}

/**
*	isRed: bool
*	returns a boolean value if an AC unit is red given the index of the specific AC unit
*	and the current time in seconds
*/
bool isRed(int content[][2], int index, int currentTime)
{
    int remainderTime = currentTime % getTotalTime(content, index);
	
    if(remainderTime == 0)
	return true;   
 
    if(remainderTime > content[index][0])
	return true;
    else
	return false;
}

/**
*	allRed: bool
*	given an array of boolean values, returns true if all of the values in the array are true
*/
bool allRed(bool status[], int total)
{
    int trueCount = 0;

    for(int i = 0; i < total; ++i)
    {
	if(status[i])
	    trueCount++;

    }

    return (trueCount == total);
}
