#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "header.h"

void print_menu() {
    printf("\nSelect one to search\n1. Name\n2. Number\n3. Email\n4. Back to Main Menu\n");
}

//Validation
int is_validname(char *name) {
    for (int i = 0; name[i]; i++)
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
            return 0;
    return 1;
}

int is_validnumber(AddressBook *addressBook, char *number) {
    int len = strlen(number);
    if (len != 10) return 0;
    for (int i = 0; i < len; i++)
        if (!isdigit((unsigned char)number[i])) 
        return 0;
    return 1;
}

int is_validemail(AddressBook *addressBook, char *mail) {
    int len = strlen(mail);
    if (len < 7) return 0;
    char *at = strchr(mail, '@');
    if (!at || strcmp(mail + len - 4, ".com") != 0)
        return 0;

    for (int i = 0; i < len; i++) {
        if (mail[i] == '@') 
            continue;
        if (!isalnum((unsigned char)mail[i]) && mail[i] != '.' && mail[i] != '_')
            return 0;
    }

    if (at == mail || *(at + 1) == '.' || *(at + 1) == '\0')
        return 0;
    return 1;
}

int is_duplicate_number(AddressBook *addressBook, char *number) {
    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].phone, number) == 0)
            return 1;
    return 0;
}

int is_duplicate_email(AddressBook *addressBook, char *mail) {
    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].email, mail) == 0)
            return 1;
    return 0;
}


static void print_one_contact(AddressBook *addressBook, int i) 
{
    printf("%-5d %-20s %-15s %-30s\n", i + 1,
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
}

//Search by name
void search_by_name(AddressBook *addressBook, int mode) 
{
    char new_name[50];
    int name_index[100], count = 0;

    printf("Enter the contact name: ");
    scanf(" %[^\n]", new_name);

    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcasecmp(addressBook->contacts[i].name, new_name) == 0)
            name_index[count++] = i;

    if (!count) 
    { 
        printf("Invalid Name! or Contact not found.\n"); 
        return; 
    }

    if (mode == SEARCH) 
    {
        printf("\n%-5s %-20s %-15s %-30s\n", "Sno.", "Name", "Phone", "Email");
        printf("-------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) 
        print_one_contact(addressBook, name_index[i]);
    } 
    else if (mode == EDIT)
        edit_contact(addressBook, name_index, count);
    else if (mode == DELETE)
        delete_contact(addressBook, name_index, count);
}

//Search by number
void search_by_number(AddressBook *addressBook, int mode) 
{
    char new_number[20];
    printf("Enter the contact number: ");
    scanf(" %[^\n]", new_number);

    if (!is_validnumber(addressBook, new_number)) 
    { 
        printf("Invalid number format!\n"); 
        return; 
    }

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, new_number) == 0) 
        {
            if (mode == SEARCH) 
            { 
              printf("\n%-5s %-20s %-15s %-30s\n", "Sno.", "Name", "Phone", "Email");
              printf("-------------------------------------------------------------------------------------------------------\n");
              print_one_contact(addressBook, i); 
            }
            else if (mode == EDIT) 
                edit_contact(addressBook, &i, 1);
            else if (mode == DELETE) 
                delete_contact(addressBook, &i, 1);
            return;
        }
    }
    printf("Contact number not found\n");
}

//Search by email
void search_by_email(AddressBook *addressBook, int mode) 
{
    char new_email[50];
    printf("Enter the contact email: ");
    scanf(" %[^\n]", new_email);

    if (!is_validemail(addressBook, new_email)) 
    { 
        printf("Invalid email format!\n"); 
        return; 
    }

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, new_email) == 0) 
        {
            if (mode == SEARCH) 
            { 
                printf("\n%-5s %-20s %-15s %-30s\n", "Sno.", "Name", "Phone", "Email");
                printf("-------------------------------------------------------------------------------------------------------\n");
                print_one_contact(addressBook, i); 
            }
            else if (mode == EDIT) 
                edit_contact(addressBook, &i, 1);
            else if (mode == DELETE) 
                delete_contact(addressBook, &i, 1);
            return;
        }
    }
    printf("Contact Email-ID not found\n");
}

//Edit contact
void edit_contact(AddressBook *addressBook, int *index, int count) 
{
    int select = 1, choice;

    if (count > 1) 
    {
        printf("\nMultiple contacts found with the same name:\n");
        printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
        printf("--------------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            int idx = index[i];
            printf("%-5d %-20s %-15s %-30s\n", i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }
        printf("\nSelect one contact to edit (1 to %d): ", count);
        
        if (scanf("%d", &select) != 1 || select < 1 || select > count) 
        {
            while (getchar() != '\n');
            printf("Invalid selection.\n");
            return;
        }
    }

    int selected_index = index[select - 1];

    // ask until valid edit choice
    while (1) 
    {
        printf("Select what to edit:\n1. Name\n2. Number\n3. Email\nEnter choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number (1-3).\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice < 1 || choice > 3) 
        {
            printf("Invalid choice! Please try again.\n");
            continue;
        }
        break;
    }

    switch (choice) 
    {
        case 1:
            do 
            {
                printf("Enter the new name: ");
                scanf(" %[^\n]", addressBook->contacts[selected_index].name);
                if (!is_validname(addressBook->contacts[selected_index].name))
                    printf("Name must contain only alphabets and spaces.\n");
            } while (!is_validname(addressBook->contacts[selected_index].name));
                break;

        case 2:
            do 
            {
                printf("Enter the new contact number: ");
                char temp[20];
                scanf(" %[^\n]", temp);
                
                if (!is_validnumber(addressBook, temp))
                    printf("Invalid number format!\n");

                else 
                {
                    int duplicate = 0;
                    for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                        if (i != selected_index && strcmp(addressBook->contacts[i].phone, temp) == 0) 
                        {
                            duplicate = 1;
                            printf("Mobile number already exists!\n");
                            break;
                        }
                    }
                    if (!duplicate) 
                    {
                        strcpy(addressBook->contacts[selected_index].phone, temp);
                        break;
                    }
                }
            } while (1);
            break;

        case 3:
            do 
            {
                printf("Enter the new Email-ID: ");
                char temp[50];
                scanf(" %[^\n]", temp);

                if (!is_validemail(addressBook, temp))
                    printf("Invalid email format!\n");

                else {
                    int duplicate = 0;
                    for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                        if (i != selected_index && strcmp(addressBook->contacts[i].email, temp) == 0) 
                        {
                            duplicate = 1;
                            printf("Email-ID already exists!\n");
                            break;
                        }
                    }
                    if (!duplicate) 
                    {
                        strcpy(addressBook->contacts[selected_index].email, temp);
                        break;
                    }
                }
            } while (1);
            break;
    }

    printf("Contact updated successfully.\n");
}

// Delete contact
void delete_contact(AddressBook *addressBook, int *index, int count) 
{
    int select = 1;

    if (count > 1) 
    {
        printf("\nMultiple contacts found with the same name:\n");
        printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
        printf("--------------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) 
        {
            printf("%-5d %-20s %-15s %-30s\n", i + 1,
                   addressBook->contacts[index[i]].name,
                   addressBook->contacts[index[i]].phone,
                   addressBook->contacts[index[i]].email);
        }
        printf("--------------------------------------------------------------------------\n");
        printf("Select one contact to delete (1 to %d): ", count);
        scanf("%d", &select);
        if (select < 1 || select > count) 
        {
             printf("Invalid selection.\n"); 
             return; 
        }
    }

    int selected_index = index[select - 1];
    for (int i = selected_index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    printf("Contact deleted Successfully.\n");
    addressBook->contactCount--;
}
