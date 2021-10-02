#pragma once

#include <iostream>
#include "SSDoperations.h"


int main()
{
    initPhysicalPageSimulator();

    Write(3, 4);
    printf("doing write 3 4 \n");
    printMappingTableAndPages();
    Write(6, 9);
    printf("doing write 6 9 \n");
    printMappingTableAndPages();
    Write(12, 92);
    printf("doing write 12 92  \n");
    printMappingTableAndPages();
    Write(14, 2);
    printf("doing write 14 2 \n");
    printMappingTableAndPages();
    Write(14, 6);
    printf("doing write 14 6 \n");
    printMappingTableAndPages();
    printVictimList();
    Write(6, 5);
    printf("doing write 6  5\n");
    printMappingTableAndPages();
    printVictimList();
    Free(3);
    printf("doing free 3\n");
    printMappingTableAndPages();
    printVictimList();
    Free(12);
    printf("doing free 12\n");
    printMappingTableAndPages();
    printVictimList();
    startErasePages();
    printf("Erasing the physical pages\n");
    printMappingTableAndPages();
    printVictimList();
}

