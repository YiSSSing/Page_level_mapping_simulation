#pragma once

/*
* This class define the basic operations for SSD
* 
*/


#include <stdio.h>
#include <assert.h>

#include "PhysicalPage.h"
#include "GarbageCollection.h"


// Init the pages
void initPhysicalPageSimulator()
{
	for (int i = 0; i < 15; i++)
	{
		mapping_table[i].isAlive = false;
		Pages[i].isFree = true;
	}
}

/// <summary>
///  Scan for a free page.
/// </summary>
/// <returns> The PPN of a physical page </returns>
int ScanForFreePage()
{
	// scan for free page
	int index = 0;
	for (index; index < 15; index++)
		if (Pages[index].isFree) break;

	// if no free page then start GC
	if (index >= 15)
	{
		// free spaces
		startErasePages();

		for (index; index < 15; index++)
			if (Pages[index].isFree) break;
	}
	return index;
}

/// <summary>
/// Move a page to another free page
/// </summary>
/// <param name="LPN">The LPN of the target page </param>
void Move(int LPN)
{
	// find free page
	if (!mapping_table[LPN].isAlive) return;
	int PPN = mapping_table[LPN].PPN;
	int dist = ScanForFreePage();

	// write data
	Pages[dist].data = Pages[PPN].data;
	Pages[dist].isFree = false;

	// update the mapping table and add the origin page to victim list
	mapping_table[LPN].PPN = dist;
	addToVictimList(PPN);
}


// Read data from SSD
int Read(int LPN, int data)
{
	assert(mapping_table[LPN].isAlive);
	return Pages[mapping_table[LPN].PPN].data;
}

// Wrtie data to SSD
void Write(int LPN, int data)
{
	// be sure the number of LPN is legal
	assert(LPN < 15);
	int PPN = ScanForFreePage();

	// if page is alive, then need to update data
	if (mapping_table[LPN].isAlive)
	{
		// set the origin page as a victim for GC, and find a new page for data
		addToVictimList(mapping_table[LPN].PPN);

		// write physical page
		Pages[PPN].data = data;
		Pages[PPN].isFree = false;

		// update mapping table
		mapping_table[LPN].PPN = PPN;
	}
	// page is not alive, find a free physical page to write
	else
	{
		// update mapping table
		mapping_table[LPN].PPN = PPN;
		mapping_table[LPN].isAlive = true;

		// write physical page
		Pages[PPN].data = data;
		Pages[PPN].isFree = false;
	}
}

/// <summary>
/// Free a virtual page, and add the physical page to victim list.
/// </summary>
/// <param name="LPN"> The LPN of target page </param>
void Free(int LPN)
{
	mapping_table[LPN].isAlive = false;
	addToVictimList(mapping_table[LPN].PPN);
}

// Print the memory status
void printMappingTableAndPages()
{
	printf("             ");
	for (int i = 0; i < 15; i++) printf("%d   ", i);
	printf("\nPages data   ");
	for (int i = 0; i < 15; i++) printf("%d   ", Pages[i].data);
	printf("\n   isFree    ");
	for (int i = 0; i < 15; i++) printf("%c   ", Pages[i].isFree ? 'O' : 'X');
	printf("\nTable PPN    ");
	for (int i = 0; i < 15; i++) printf("%d   ", mapping_table[i].PPN);
	printf("\n    isAlive  ");
	for (int i = 0; i < 15; i++) printf("%c   ", mapping_table[i].isAlive ? 'O' : 'X');
	printf("\n\n");
}