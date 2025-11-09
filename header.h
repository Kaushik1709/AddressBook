#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>

#define SEARCH 0
#define EDIT 1
#define DELETE 2

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

// main functions
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

//validation
void print_menu();
int is_validname(char *name);
int is_validnumber(AddressBook *addressBook, char *number);
int is_validemail(AddressBook *addressBook, char *mail);
int is_duplicate_number(AddressBook *addressBook, char *number);
int is_duplicate_email(AddressBook *addressBook, char *mail);

// Search / edit 
void search_by_name(AddressBook *addressBook, int mode);
void search_by_number(AddressBook *addressBook, int mode);
void search_by_email(AddressBook *addressBook, int mode);
void edit_contact(AddressBook *addressBook, int *index, int count);
void delete_contact(AddressBook *addressBook, int *index, int count);

#endif
