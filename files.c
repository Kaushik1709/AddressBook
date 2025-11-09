#include <stdio.h>
#include "header.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("Addressbook/addressBook.csv", "w");
    if (!fptr) 
    return;
    for (int i = 0; i < addressBook->contactCount; i++)
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("Addressbook/addressBook.csv", "r");
    if (!fptr)
        {
           addressBook->contactCount = 0;
           return;
        }
    int i = 0;
    while (i < 100 && fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email) == 3)
           {
                i++;
           }    
    addressBook->contactCount = i;
    fclose(fptr);
}
