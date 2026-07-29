#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include <stdlib.h>
/* INITIALIZE */
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;//initialize contact count
    saveContactsToFile(addressBook);//to load previous data
}
/* LIST */
void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available!\n");
        return;
    }

    printf("\n CONTACT LIST\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d. %s | %s | %s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}
/* VALIDATIONS  TO NAME,PHONE NUMBER,EMAIL*/
int isvalidname(char name[])
{
    int count=0;
    for (int i = 0; name[i]!='\0'; i++)
    {
        if (isalpha((unsigned char)name[i]))
        {
            count++;
        }
        else if(name[i]==' ')
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    if(count<4)
    return 2;

    return 0;
}
int isvalidphone(char phone[])
{
    for (int i = 0; phone[i]; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
            return 2;
    }
    if (strlen(phone) != 10)
        return 1;    
    if (phone[0] < '6' || phone[0] > '9')
        return 3;//invalid starting digit
    return 0;//valid
}
int isvalidemail(char email[])
{
    int atCount = 0;
    int atIndex = -1;
    int dotIndex = -1;
    int len = strlen(email);

    //  Only allowed symbols
    for (int i = 0; email[i]; i++)
    {
        if (isalnum((unsigned char)email[i]))
            continue;
        else if (email[i] == '@')
        {
            atCount++;
            atIndex = i;
        }
        else if (email[i] == '.')
        {
            dotIndex = i;
        }
        else
        {
            return 1; // invalid symbol
        }
    }

    // exactly one @
    if (atCount != 1)
        return 2;

    //dot must be after @
    if (dotIndex < atIndex)
        return 3;

    //at least one char between @ and .
    if (dotIndex - atIndex <= 1)
        return 4;

    //must end with ".com"
    if (len < 5 || strcmp(&email[len - 4], ".com") != 0)
        return 5;

    //after @ and . only letters/digits
    for (int i = atIndex + 1; i < len; i++)
    {
        if (email[i] == '.')
            continue;

        if (!isalnum((unsigned char)email[i]))
            return 6;
    }

    return 0; //valid
}
/* CREATE CONTACT*/
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book full!\n");
        return;
    }

    Contact c;
    int attempts;

    /* NAME INPUT WITH VALIDATION */
    attempts = 3;
    while (attempts>0)
    {
        printf("Enter Name: ");
        scanf(" %49[^\n]", c.name);
        while (getchar() != '\n');   //IT WILL HELPS TO CLEAR BUFFER

        int res=isvalidname(c.name);
        if(res==0)
        break;
        attempts--;
        if(res == 1)
        printf("Invalid name! Name should contain only letters.\n");
        else if (res == 2)
        printf("Invalid name! Name must contain at least 4 letters.\n");

    printf("Attempts left: %d\n", attempts);
    }
    if (attempts == 0) return;

    /* PHONE INPUT WITH VALIDATION*/
    attempts = 3;
    while (attempts > 0)
{
    printf("Enter Phone: ");
    scanf("%19s", c.phone);
    while (getchar() != '\n');

    int res = isvalidphone(c.phone);

    if (res == 0)
        break;

    attempts--;

    if (res == 1)
        printf("Invalid phone! Must contain exactly 10 digits.\n");
    else if (res == 2)
        printf("Invalid phone! Symbols or characters are not allowed.\n");
    else if (res == 3)
        printf("Invalid phone! First digit must be between 6 and 9.\n");

    printf("Attempts left: %d\n", attempts);
}

if (attempts == 0)
    return;

    /* EMAIL INPUT WITH VALIDATION*/
    attempts = 3;

while (attempts > 0)
{
    printf("Enter Email: ");
    scanf("%49s", c.email);
    while (getchar() != '\n');

    int res = isvalidemail(c.email);

    if (res == 0)
        break;

    attempts--;

    if (res == 1)
        printf("Invalid email! Only '@' and '.' are allowed as symbols.\n");
    else if (res == 2)
        printf("Invalid email! Must contain exactly one '@'.\n");
    else if (res == 3)
        printf("Invalid email! '.' must come after '@'.\n");
    else if (res == 4)
        printf("Invalid email! There must be characters between '@' and '.'.\n");
    else if (res == 5)
        printf("Invalid email! Must end with '.com' and no extra characters.\n");
    else if (res == 6)
        printf("Invalid email! Domain must contain only letters or digits.\n");

    printf("Attempts left: %d\n", attempts);
}

if (attempts == 0)
    return;
//TO STORE CONTACT
    addressBook->contacts[addressBook->contactCount++] = c;
    printf("Contact saved successfully!\n");
}
void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to search!\n");
        return;
    }

    int choice;
    char input[50];
    int found = 0;

    printf("\n--- Search Contact ---\n");
    printf("1. By Name\n");
    printf("2. By Phone\n");
    printf("3. By Email\n");
    printf("4. Exit\n"); 
    printf("Enter your choice: ");

    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 4)  
        return;
//TAKE INPUT BASED ON CHOICE
    switch (choice)
    {
        case 1:
            printf("Enter Name: ");
            scanf(" %49[^\n]", input);
            while (getchar() != '\n');
            break;

        case 2:
            printf("Enter Phone: ");
            scanf("%19s", input);
            while (getchar() != '\n');
            break;

        case 3:
            printf("Enter Email: ");
            scanf("%49s", input);
            while (getchar() != '\n');
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("\n--- Search Results ---\n");  
//SEARCH ALL MATCHES
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, input) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, input) == 0))
        {
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No matching contact found!\n");  
    }
}
void editContact(AddressBook *addressBook) 
{
    int choice;
    char input[50];
    int index[50], count = 0;

    printf("\n--- Edit Contact ---\n");
    printf("1. By Name\n");
    printf("2. By Phone Number\n");
    printf("3. By Email ID\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 4)
        return;

    /* SEARCH INPUT */
    if (choice == 1)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", input);
    }
    else if (choice == 2)
    {
        printf("Enter Phone Number: ");
        scanf("%s", input);
    }
    else if (choice == 3)
    {
        printf("Enter Email ID: ");
        scanf("%s", input);
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    /* FIND ALL MATCHES */
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, input) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, input) == 0))
        {
            index[count++] = i;
        }
    }

    if (count == 0)
    {
        printf("Contact not found!\n");
        return;
    }

    /* HANDLE DUPLICATES */
    int found;
    if (count > 1)
    {
        printf("\nMultiple contacts found:\n");
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[index[i]].name,
                   addressBook->contacts[index[i]].phone,
                   addressBook->contacts[index[i]].email);
        }

        printf("Select contact: ");
        int sel;
        scanf("%d", &sel);

        if (sel < 1 || sel > count)
        {
            printf("Invalid selection!\n");
            return;
        }

        found = index[sel - 1];
    }
    else
    {
        found = index[0];
    }

    printf("\nContact Found:\n");
    printf("%s | %s | %s\n",
           addressBook->contacts[found].name,
           addressBook->contacts[found].phone,
           addressBook->contacts[found].email);

    /* EDIT MENU */
    printf("\nWhat do you want to edit?\n");
    printf("1. Name\n2. Phone\n3. Email\n0. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 4)
        return;

    int attempts = 3;

    switch (choice)
    {
        case 1:
        {
            char newName[50];
            while (attempts > 0)
            {
                printf("Enter new Name: ");
                scanf(" %[^\n]", newName);

                int res = isvalidname(newName);
                if (res == 0)
                {
                    strcpy(addressBook->contacts[found].name, newName);
                    printf("Name updated successfully!\n");
                    return;
                }

                attempts--;
                if (res == 1)
                    printf("Only letters allowed.\n");
                else if (res == 2)
                    printf("At least 4 letters required.\n");

                printf("Attempts left: %d\n", attempts);
            }
            break;
        }

        case 2:
        {
            char newPhone[20];
            while (attempts > 0)
            {
                printf("Enter new Phone: ");
                scanf("%s", newPhone);

                int res = isvalidphone(newPhone);
                if (res == 0)
                {
                    strcpy(addressBook->contacts[found].phone, newPhone);
                    printf("Phone updated successfully!\n");
                    return;
                }

                attempts--;
                if (res == 1)
                    printf("Must be exactly 10 digits.\n");
                else if (res == 2)
                    printf("Only digits allowed.\n");
                else if (res == 3)
                    printf("First digit must be 6–9.\n");

                printf("Attempts left: %d\n", attempts);
            }
            break;
        }

        case 3:
        {
            char newEmail[50];
            while (attempts > 0)
            {
                printf("Enter new Email: ");
                scanf("%s", newEmail);

                int res = isvalidemail(newEmail);
                if (res == 0)
                {
                    strcpy(addressBook->contacts[found].email, newEmail);
                    printf("Email updated successfully!\n");
                    return;
                }

                attempts--;
                printf("Invalid email format!\n");
                printf("Attempts left: %d\n", attempts);
            }
            break;
        }

        default:
            printf("Invalid edit choice!\n");
    }
}
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete!\n");
        return;
    }

    int choice;
    char input[50];
    int index[50], count = 0;

    printf("\n--- Delete Contact ---\n");
    printf("1. By Name\n2. By Phone\n3. By Email\n4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 4)  
        return;

    /* TAKE INPUT */
    if (choice == 1)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", input);
    }
    else if (choice == 2)
    {
        printf("Enter Phone: ");
        scanf("%s", input);
    }
    else if (choice == 3)
    {
        printf("Enter Email: ");
        scanf("%s", input);
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    /* SEARCH ALL MATCHES */
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, input) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, input) == 0))
        {
            index[count++] = i;
        }
    }

    if (count == 0)
    {
        printf("Contact not found!\n");
        return;
    }

    /* HANDLE DUPLICATES */
    int found;
    if (count > 1)
    {
        printf("\nMultiple contacts found:\n");
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[index[i]].name,
                   addressBook->contacts[index[i]].phone,
                   addressBook->contacts[index[i]].email);
        }

        printf("Select contact to delete: ");
        int sel;
        scanf("%d", &sel);

        if (sel < 1 || sel > count)
        {
            printf("Invalid selection!\n");
            return;
        }

        found = index[sel - 1];
    }
    else
    {
        found = index[0];
    }
    /* SHOW CONTACT */
    printf("\nSelected Contact:\n");
    printf("%s | %s | %s\n",
           addressBook->contacts[found].name,
           addressBook->contacts[found].phone,
           addressBook->contacts[found].email);

    /* CONFIRMATION TO DELETE */
    char confirm;
    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    /* DELETE (SHIFT LEFT) */
    for (int i = found; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}
void saveContactsToFile(AddressBook *addressBook)
{
    //save contacts to file
    FILE *fptr=fopen("contacts.txt","w");//opened in write mode
    if(fptr==NULL)
    {
        printf("Error Opening File!");
        return;
    }
    fprintf(fptr,"#%d\n",addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    //load contacts from file
    if(fptr==NULL)
    return;//if cantacts are zero
    while(fscanf(fptr,"%[^,],%[^,], %[^\n]\n",
        addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].phone,
        addressBook->contacts[addressBook->contactCount].email)==3)
        {
            addressBook->contactCount++;
        }
        fclose(fptr);
}  