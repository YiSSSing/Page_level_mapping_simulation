#pragma once

/*
* This is a class to simulate garbage collection algorithm for page level mapping
*/

#include "PhysicalPage.h"

#include <stdio.h>

// The targets for garbage collection
struct Victim
{
	int victimList[15] = { 0 };
	int vicitims = 0;
};


// Data
Victim VictimList;


/// <summary>
/// Add a physical page to victim list.
/// </summary>
/// <param name="PPN">The PPN of target page </param>
void addToVictimList(int PPN)
{
	VictimList.victimList[VictimList.vicitims] = PPN;
	VictimList.vicitims++;
}


// Garbage Collection methods

/// <summary>
/// Erase the physical pages to free spaces.
/// </summary>
void startErasePages() 
{
	for ( int i = 0; i < VictimList.vicitims; i++ ) 
	{
		Pages[VictimList.victimList[i]].data = 0;
		Pages[VictimList.victimList[i]].isFree = true;
	}
	VictimList.vicitims = 0;
}


void printVictimList() 
{
	printf("The victims are : ");
	for (int i = 0; i < VictimList.vicitims; i++) printf("%d  ", VictimList.victimList[i]);
	printf("\n");
}