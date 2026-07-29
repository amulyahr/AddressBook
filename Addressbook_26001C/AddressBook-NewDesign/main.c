#include <stdio.h>
#include "contact.h"
#include<unistd.h>

int main() 
{
     char temp[20];
    for(int i=0;i<=100;i++)
    {
        printf("[Loading...........%d%%]\r",i);
        usleep(30000);
        fflush(stdout);//it is used to remove the entire line and it will print once again
    }

    int choice;
    AddressBook addressBook;    

    initialize(&addressBook);

    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }
            while (getchar() != '\n');

        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                editContact(&addressBook);
                break;

            case 4:
                deleteContact(&addressBook);
                break;

            case 5:          
                listContacts(&addressBook);
                break;

            case 6:
                saveContactsToFile(&addressBook);
                printf("Saving and Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}