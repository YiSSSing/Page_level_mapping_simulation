#pragma once


/*
* This class is to simulate the memory and mapping table
*/

struct PhysicalPage
{
	int data;
	bool isFree;
};

// Use an array as mapping table, index is LPN
struct MappingTable
{
	int PPN;
	bool isAlive;
};

// Define of physical pages and Mapping table, supposed 15 pages only
MappingTable mapping_table[15]; // Stored in RAM
PhysicalPage Pages[15];