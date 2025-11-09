#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//load contacts from file after closing and opening later
void initialize(AddressBook *addressBook)
{
    loadContactsFromFile(addressBook);
}

// Create Contact
void createContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount >= 100) 
    {
         printf("\nAddress book is full\n"); 
         return;
    }

    Contact newContact;

    do 
    {
        printf("Enter the contact name: ");
        scanf(" %[^\n]", newContact.name);
        if (!is_validname(newContact.name))
            printf("Name must contain only alphabets and spaces.\n");
    } while (!is_validname(newContact.name));

    do 
    {
        printf("Enter the contact number: ");
        scanf(" %[^\n]", newContact.phone);
        if (!is_validnumber(addressBook, newContact.phone))
            printf("Invalid number! Must be 10 digits.\n");

        else if (is_duplicate_number(addressBook, newContact.phone))
            printf("Mobile number already exists!\n");

    } while (!is_validnumber(addressBook, newContact.phone) || is_duplicate_number(addressBook, newContact.phone));

    do 
    {
        printf("Enter the Email-ID: ");
        scanf(" %[^\n]", newContact.email);
        if (!is_validemail(addressBook, newContact.email))
            printf("Invalid format! Email must be in format\n");

        else if (is_duplicate_email(addressBook, newContact.email))
            printf("Email-ID already exists!\n");

    } while (!is_validemail(addressBook, newContact.email) || is_duplicate_email(addressBook, newContact.email));

    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("\nContact created successfully\n");
}

// Search contact
void searchContact(AddressBook *addressBook) 
{
    int choice;
    while (1) 
    {
        print_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number (1-4).\n");
            while (getchar() != '\n');//clear the input buffer
            continue;
        }
        if (choice == 4) 
            return;
        if (choice < 1 || choice > 4) 
        {
            printf("Invalid choice! Please try again.\n");
            continue;
        }
        if (choice == 1) 
            search_by_name(addressBook, SEARCH);
        else if (choice == 2) 
            search_by_number(addressBook, SEARCH);
        else if (choice == 3) 
            search_by_email(addressBook, SEARCH);
            break;
    }
}

//Edit contact
void editContact(AddressBook *addressBook) 
{
    int choice;
    while (1) 
    {
        print_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number (1-4).\n");
            while (getchar() != '\n');// clear the input buffer
            continue;
        }
        if (choice == 4) return;
        if (choice < 1 || choice > 4) 
        {
            printf("Invalid choice! Please try again.\n");
            continue;
        }
        if (choice == 1) 
            search_by_name(addressBook, EDIT);
        else if (choice == 2) 
            search_by_number(addressBook, EDIT);
        else if (choice == 3) 
            search_by_email(addressBook, EDIT);
            break;
    }
}

//Delete contact
void deleteContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    { 
        printf("No contacts to delete\n"); 
        return; 
    }

    int choice;
    while (1) 
    {
        print_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number (1-4).\n");
            while (getchar() != '\n');//clear input buffer
            continue;
        }
        if (choice == 4) 
            return;
        if (choice < 1 || choice > 4) 
        {
            printf("Invalid choice! Please try again.\n");
            continue;
        }
        if (choice == 1) 
                search_by_name(addressBook, DELETE);
        else if (choice == 2) 
                search_by_number(addressBook, DELETE);
        else if (choice == 3) 
                search_by_email(addressBook, DELETE);
                break;
    }
}

// List Contacts 
void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    { 
        printf("\nNo contacts found.\n"); 
        return;
    }
    printf("\n%-5s %-20s %-15s %-30s\n", "Sno.", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
        printf("%-5d %-20s %-15s %-30s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Total contacts: %d\n", addressBook->contactCount);
}

// Save and exit
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook);
    printf("Saving and exiting...\n");
    exit(EXIT_SUCCESS);
}

int main() {
    AddressBook addressBook;
    initialize(&addressBook);
    int choice;
    do {
        printf("\n**Address Book Menu**\n1. Create contact\n2. Search contact\n3. Edit contact\n4. Delete contact\n5. List contacts\n6. Save & Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) 
        `{
            printf("Invalid input! Please enter a number (1-6).\n");
            while (getchar() != '\n');// clear input buffer
            continue;
        }
        switch (choice) 
        {
            case 1: createContact(&addressBook); 
                    break;
            case 2: searchContact(&addressBook);
                    break;
            case 3: editContact(&addressBook); 
                    break;
            case 4: deleteContact(&addressBook); 
                    break;
            case 5: listContacts(&addressBook); 
                    break;
            case 6: saveAndExit(&addressBook); 
                    break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);
    return 0;
}
