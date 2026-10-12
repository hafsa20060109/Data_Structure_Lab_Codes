#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//==================================================
// STRUCTURE
//==================================================

struct Contact
{
    char name[100];
    char phone[20];
    char email[100];
    int favourite;
};


//==================================================
// FUNCTION PROTOTYPE
//==================================================

void addContact();
void viewContact();
void searchContact();
void editContact();
void deleteContact();
void favouriteContact();
void viewFavouriteContact();

int nameCompare(char a[], char b[]);
void clearInputBuffer();
int duplicateName(char name[]);
void cleanString(char str[]);

//==================================================
// MAIN FUNCTION
//==================================================

int main()
{
    int choice;

    while(1)
    {
        printf("\n=====================================\n");
        printf("       CONTACT MANAGEMENT SYSTEM\n");
        printf("=====================================\n");

        printf("1. Add Contact\n");
        printf("2. View Contact\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Mark/Remove Favourite\n");
        printf("7. View Favourite Contact\n");
        printf("0. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                viewContact();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                editContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                favouriteContact();
                break;

            case 7:
                viewFavouriteContact();
                break;

            case 0:
                printf("\nProgram Closed.\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}


//==================================================
// CLEAR INPUT BUFFER
//==================================================

void clearInputBuffer()
{
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}


//==================================================
// REMOVE SPACE / NEWLINE / CARRIAGE RETURN
//==================================================

void cleanString(char str[])
{
    int start = 0;
    int end;

    // Remove leading spaces
    while(str[start] == ' ' ||
          str[start] == '\t')
    {
        start++;
    }

    // Shift string left
    if(start > 0)
    {
        int i = 0;

        while(str[start] != '\0')
        {
            str[i] = str[start];
            i++;
            start++;
        }

        str[i] = '\0';
    }

    // Remove trailing spaces, \n, \r, \t
    end = strlen(str) - 1;

    while(end >= 0 &&
         (str[end] == ' ' ||
          str[end] == '\t' ||
          str[end] == '\n' ||
          str[end] == '\r'))
    {
        str[end] = '\0';
        end--;
    }
}


//==================================================
// NAME COMPARE
// CASE INSENSITIVE
//==================================================

int nameCompare(char a[], char b[])
{
    int i = 0;

    cleanString(a);
    cleanString(b);

    while(a[i] != '\0' && b[i] != '\0')
    {
        if(tolower((unsigned char)a[i]) !=
           tolower((unsigned char)b[i]))
        {
            return 0;
        }

        i++;
    }

    if(a[i] == '\0' && b[i] == '\0')
    {
        return 1;
    }

    return 0;
}

//==================================================
// DUPLICATE NAME CHECK
//==================================================

int duplicateName(char name[])
{
    FILE *file;
    struct Contact c;

    file = fopen("contact.txt", "r");

    if(file == NULL)
    {
        return 0;
    }

    while(fgets(c.name, sizeof(c.name), file) &&
          fgets(c.phone, sizeof(c.phone), file) &&
          fgets(c.email, sizeof(c.email), file) &&
          fscanf(file, "%d", &c.favourite))
    {
        c.name[strcspn(c.name, "\n")] = '\0';

        c.phone[strcspn(c.phone, "\n")] = '\0';

        c.email[strcspn(c.email, "\n")] = '\0';


        fgetc(file);

        if(nameCompare(name, c.name))
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}


//==================================================
// ADD CONTACT
//==================================================

void addContact()
{
    FILE *file;

    struct Contact c;

    int choice;


    while(1)
    {
        clearInputBuffer();

        printf("\nEnter Name: ");

        fgets(c.name, sizeof(c.name), stdin);

        c.name[strcspn(c.name, "\n")] = '\0';


        //==================================================
        // DUPLICATE CHECK
        //==================================================

        if(duplicateName(c.name))
        {
            printf("\n=====================================\n");
            printf("       DUPLICATE CONTACT\n");
            printf("=====================================\n");

            printf("This name already exists.\n");

            printf("\n1. Try Again");
            printf("\n2. Go to Main Menu");

            printf("\n\nEnter Choice: ");
            scanf("%d", &choice);

            if(choice == 2)
            {
                return;
            }

            continue;
        }


        printf("Enter Phone: ");

        fgets(c.phone, sizeof(c.phone), stdin);

        c.phone[strcspn(c.phone, "\n")] = '\0';


        printf("Enter Email: ");

        fgets(c.email, sizeof(c.email), stdin);

        c.email[strcspn(c.email, "\n")] = '\0';


        // New contact initially Normal

        c.favourite = 0;


        //==================================================
        // OPEN FILE
        //==================================================

        file = fopen("contact.txt", "a");

        if(file == NULL)
        {
            printf("\nFile could not be opened.\n");
            return;
        }


        //==================================================
        // SAVE CONTACT
        //==================================================

        fprintf(file, "%s\n", c.name);
        fprintf(file, "%s\n", c.phone);
        fprintf(file, "%s\n", c.email);
        fprintf(file, "%d\n", c.favourite);


        fclose(file);


        printf("\nContact Added Successfully.\n");


        printf("\n1. Add Another Contact");
        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}


//==================================================
// VIEW CONTACT
// A-Z SORTING
//==================================================

void viewContact()
{
    FILE *file;

    struct Contact contacts[100];
    struct Contact temp;

    int count = 0;
    int i, j;
    int choice;


    file = fopen("contact.txt", "r");

    if(file == NULL)
    {
        printf("\nNo Contact Available.\n");
        return;
    }


    //==================================================
    // READ ALL CONTACTS
    //==================================================

    while(count < 100 &&
          fgets(contacts[count].name,
                sizeof(contacts[count].name), file) &&

          fgets(contacts[count].phone,
                sizeof(contacts[count].phone), file) &&

          fgets(contacts[count].email,
                sizeof(contacts[count].email), file) &&

          fscanf(file, "%d", &contacts[count].favourite))
    {
        contacts[count].name[
            strcspn(contacts[count].name, "\n")
        ] = '\0';

        contacts[count].phone[
            strcspn(contacts[count].phone, "\n")
        ] = '\0';

        contacts[count].email[
            strcspn(contacts[count].email, "\n")
        ] = '\0';


        // Remove newline after favourite

        fgetc(file);

        count++;
    }

    fclose(file);


    if(count == 0)
    {
        printf("\nNo Contact Available.\n");
        return;
    }


    while(1)
    {
        //==================================================
        // A-Z SORTING
        //==================================================

        for(i = 0; i < count - 1; i++)
        {
            for(j = i + 1; j < count; j++)
            {
                int k = 0;
                int result = 0;


                while(contacts[i].name[k] != '\0' &&
                      contacts[j].name[k] != '\0')
                {
                    char a =
                        tolower(
                            (unsigned char)
                            contacts[i].name[k]
                        );

                    char b =
                        tolower(
                            (unsigned char)
                            contacts[j].name[k]
                        );


                    if(a < b)
                    {
                        result = -1;
                        break;
                    }

                    if(a > b)
                    {
                        result = 1;
                        break;
                    }

                    k++;
                }


                if(result == 0)
                {
                    if(contacts[i].name[k] == '\0' &&
                       contacts[j].name[k] != '\0')
                    {
                        result = -1;
                    }

                    else if(contacts[i].name[k] != '\0' &&
                            contacts[j].name[k] == '\0')
                    {
                        result = 1;
                    }
                }


                if(result > 0)
                {
                    temp = contacts[i];

                    contacts[i] = contacts[j];

                    contacts[j] = temp;
                }
            }
        }


        //==================================================
        // TABLE OUTPUT
        //==================================================

        printf("\n");
        printf("====================================================================\n");

        printf("| %-3s | %-20s | %-15s | %-25s |\n",
               "No.",
               "Name",
               "Phone",
               "Email");

        printf("====================================================================\n");


        for(i = 0; i < count; i++)
        {
            printf("| %-3d | %-20s | %-15s | %-25s |\n",
                   i + 1,
                   contacts[i].name,
                   contacts[i].phone,
                   contacts[i].email);
        }


        printf("====================================================================\n");


        printf("\n1. Refresh Contact List");
        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}


void searchContact()
{
    FILE *file;

    struct Contact c;

    char searchName[100];

    int found;
    int choice;


    while(1)
    {
        found = 0;


        //==================================================
        // OPEN FILE
        //==================================================

        file = fopen("contact.txt", "r");

        if(file == NULL)
        {
            printf("\nNo Contact Available.\n");
            return;
        }


        //==================================================
        // SEARCH NAME INPUT
        //==================================================

        clearInputBuffer();

        printf("\nEnter Name to Search: ");

        fgets(searchName,
              sizeof(searchName),
              stdin);

        searchName[
            strcspn(searchName, "\n")
        ] = '\0';


        //==================================================
        // READ CONTACTS
        //==================================================

        while(fgets(c.name, sizeof(c.name), file) &&

              fgets(c.phone, sizeof(c.phone), file) &&

              fgets(c.email, sizeof(c.email), file) &&

              fscanf(file, "%d", &c.favourite))
        {
            // Remove newline from name

            c.name[
                strcspn(c.name, "\n")
            ] = '\0';


            // Remove newline from phone

            c.phone[
                strcspn(c.phone, "\n")
            ] = '\0';


            // Remove newline from email

            c.email[
                strcspn(c.email, "\n")
            ] = '\0';


            //==================================================
            // REMOVE NEWLINE AFTER FAVOURITE
            //==================================================

            fgetc(file);


            //==================================================
            // CASE-INSENSITIVE SEARCH
            //==================================================

            if(nameCompare(searchName, c.name))
            {
                printf("\n=====================================\n");
                printf("          CONTACT FOUND\n");
                printf("=====================================\n");


                //==================================================
                // DISPLAY CONTACT INFORMATION
                //==================================================

                printf("Name      : %s\n", c.name);

                printf("Phone     : %s\n", c.phone);

                printf("Email     : %s\n", c.email);


                //==================================================
                // DISPLAY FAVOURITE STATUS
                //==================================================

                if(c.favourite == 1)
                {
                    printf("Favourite : Yes\n");
                }
                else
                {
                    printf("Favourite : No\n");
                }


                found = 1;

                break;
            }
        }


        //==================================================
        // CLOSE FILE
        //==================================================

        fclose(file);


        //==================================================
        // NOT FOUND
        //==================================================

        if(found == 0)
        {
            printf("\nContact Not Found.\n");
        }


        //==================================================
        // SEARCH MENU
        //==================================================

        printf("\n1. Search Another Contact");

        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");

        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}
//==================================================
// EDIT CONTACT
//==================================================

void editContact()
{
    FILE *file;
    FILE *tempFile;

    struct Contact c;

    char editName[100];

    int found;
    int choice;


    while(1)
    {
        found = 0;


        file = fopen("contact.txt", "r");

        if(file == NULL)
        {
            printf("\nNo Contact Available.\n");
            return;
        }


        tempFile = fopen("temp.txt", "w");

        if(tempFile == NULL)
        {
            printf("\nTemporary File Error.\n");

            fclose(file);

            return;
        }


        clearInputBuffer();

        printf("\nEnter Contact Name to Edit: ");

        fgets(editName,
              sizeof(editName),
              stdin);

        editName[
            strcspn(editName, "\n")
        ] = '\0';


        //==================================================
        // READ CONTACTS
        //==================================================

        while(fgets(c.name, sizeof(c.name), file) &&

              fgets(c.phone, sizeof(c.phone), file) &&

              fgets(c.email, sizeof(c.email), file) &&

              fscanf(file, "%d", &c.favourite))
        {
            c.name[
                strcspn(c.name, "\n")
            ] = '\0';

            c.phone[
                strcspn(c.phone, "\n")
            ] = '\0';

            c.email[
                strcspn(c.email, "\n")
            ] = '\0';


            // Remove newline after favourite

            fgetc(file);


            //==================================================
            // FIND CONTACT
            //==================================================

            if(nameCompare(editName, c.name))
            {
                printf("\n========== CURRENT INFORMATION ==========\n");

                printf("Name  : %s\n", c.name);
                printf("Phone : %s\n", c.phone);
                printf("Email : %s\n", c.email);


                clearInputBuffer();

                printf("\nEnter New Name: ");

                fgets(c.name,
                      sizeof(c.name),
                      stdin);

                c.name[
                    strcspn(c.name, "\n")
                ] = '\0';


                /*
                    Check whether new name already exists.
                    Here we are keeping the implementation simple.
                */

                printf("Enter New Phone: ");

                fgets(c.phone,
                      sizeof(c.phone),
                      stdin);

                c.phone[
                    strcspn(c.phone, "\n")
                ] = '\0';


                printf("Enter New Email: ");

                fgets(c.email,
                      sizeof(c.email),
                      stdin);

                c.email[
                    strcspn(c.email, "\n")
                ] = '\0';


                found = 1;
            }


            //==================================================
            // SAVE TO TEMP FILE
            //==================================================

            fprintf(tempFile, "%s\n", c.name);
            fprintf(tempFile, "%s\n", c.phone);
            fprintf(tempFile, "%s\n", c.email);
            fprintf(tempFile, "%d\n", c.favourite);
        }


        fclose(file);
        fclose(tempFile);


        if(found)
        {
            remove("contact.txt");

            rename("temp.txt", "contact.txt");

            printf("\nContact Updated Successfully.\n");
        }

        else
        {
            remove("temp.txt");

            printf("\nContact Not Found.\n");
        }


        printf("\n1. Edit Another Contact");
        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");

        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}


//==================================================
// DELETE CONTACT
//==================================================

void deleteContact()
{
    FILE *file;
    FILE *tempFile;

    struct Contact c;

    char deleteName[100];

    int found;
    int choice;
    int confirm;


    while(1)
    {
        found = 0;
        confirm = 0;


        file = fopen("contact.txt", "r");

        if(file == NULL)
        {
            printf("\nNo Contact Available.\n");
            return;
        }


        tempFile = fopen("temp.txt", "w");

        if(tempFile == NULL)
        {
            printf("\nTemporary File Error.\n");

            fclose(file);

            return;
        }


        clearInputBuffer();

        printf("\nEnter Contact Name to Delete: ");

        fgets(deleteName,
              sizeof(deleteName),
              stdin);

        deleteName[
            strcspn(deleteName, "\n")
        ] = '\0';


        //==================================================
        // READ CONTACTS
        //==================================================

        while(fgets(c.name, sizeof(c.name), file) &&

              fgets(c.phone, sizeof(c.phone), file) &&

              fgets(c.email, sizeof(c.email), file) &&

              fscanf(file, "%d", &c.favourite))
        {
            c.name[
                strcspn(c.name, "\n")
            ] = '\0';

            c.phone[
                strcspn(c.phone, "\n")
            ] = '\0';

            c.email[
                strcspn(c.email, "\n")
            ] = '\0';


            // Remove newline after favourite

            fgetc(file);


            //==================================================
            // FIND CONTACT
            //==================================================

            if(nameCompare(deleteName, c.name))
            {
                found = 1;


                printf("\n========== CONTACT INFORMATION ==========\n");

                printf("Name  : %s\n", c.name);
                printf("Phone : %s\n", c.phone);
                printf("Email : %s\n", c.email);


                printf("\nAre you sure you want to delete this contact?\n");

                printf("1. Yes\n");
                printf("2. No\n");

                printf("\nEnter Choice: ");
                scanf("%d", &confirm);


                if(confirm == 1)
                {
                    // Do not save this contact

                    continue;
                }

                else
                {
                    printf("\nDelete Cancelled.\n");
                }
            }


            //==================================================
            // SAVE OTHER CONTACTS
            //==================================================

            fprintf(tempFile, "%s\n", c.name);
            fprintf(tempFile, "%s\n", c.phone);
            fprintf(tempFile, "%s\n", c.email);
            fprintf(tempFile, "%d\n", c.favourite);
        }


        fclose(file);
        fclose(tempFile);


        if(found && confirm == 1)
        {
            remove("contact.txt");

            rename("temp.txt", "contact.txt");

            printf("\nContact Deleted Successfully.\n");
        }

        else
        {
            remove("temp.txt");

            if(found == 0)
            {
                printf("\nContact Not Found.\n");
            }
        }


        printf("\n1. Delete Another Contact");
        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");

        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}


//==================================================
// MARK / REMOVE FAVOURITE
//==================================================

void favouriteContact()
{
    FILE *file;
    FILE *tempFile;

    struct Contact c;

    char favName[100];

    int found;
    int choice;


    while(1)
    {
        found = 0;


        file = fopen("contact.txt", "r");

        if(file == NULL)
        {
            printf("\nNo Contact Available.\n");
            return;
        }


        tempFile = fopen("temp.txt", "w");

        if(tempFile == NULL)
        {
            printf("\nTemporary File Error.\n");

            fclose(file);

            return;
        }


        clearInputBuffer();

        printf("\nEnter Contact Name: ");

        fgets(favName,
              sizeof(favName),
              stdin);

        favName[
            strcspn(favName, "\n")
        ] = '\0';


        //==================================================
        // READ CONTACTS
        //==================================================

        while(fgets(c.name, sizeof(c.name), file) &&

              fgets(c.phone, sizeof(c.phone), file) &&

              fgets(c.email, sizeof(c.email), file) &&

              fscanf(file, "%d", &c.favourite))
        {
            c.name[
                strcspn(c.name, "\n")
            ] = '\0';

            c.phone[
                strcspn(c.phone, "\n")
            ] = '\0';

            c.email[
                strcspn(c.email, "\n")
            ] = '\0';


            // Remove newline after favourite

            fgetc(file);


            //==================================================
            // FIND CONTACT
            //==================================================

            if(nameCompare(favName, c.name))
            {
                found = 1;


                if(c.favourite == 0)
                {
                    c.favourite = 1;

                    printf("\nContact Marked as Favourite.\n");
                }

                else
                {
                    c.favourite = 0;

                    printf("\nFavourite Removed.\n");
                }
            }


            //==================================================
            // SAVE CONTACT
            //==================================================

            fprintf(tempFile, "%s\n", c.name);
            fprintf(tempFile, "%s\n", c.phone);
            fprintf(tempFile, "%s\n", c.email);
            fprintf(tempFile, "%d\n", c.favourite);
        }


        fclose(file);
        fclose(tempFile);


        if(found)
        {
            remove("contact.txt");

            rename("temp.txt", "contact.txt");
        }

        else
        {
            remove("temp.txt");

            printf("\nContact Not Found.\n");
        }


        printf("\n1. Mark/Remove Another Contact");
        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");

        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}


//==================================================
// VIEW FAVOURITE CONTACT
//==================================================

void viewFavouriteContact()
{
    FILE *file;

    struct Contact c;

    int found;
    int choice;
    int serial;


    while(1)
    {
        found = 0;
        serial = 1;


        file = fopen("contact.txt", "r");

        if(file == NULL)
        {
            printf("\nNo Contact Available.\n");
            return;
        }


        //==================================================
        // TABLE HEADER
        //==================================================

        printf("\n");

        printf("====================================================================\n");

        printf("| %-3s | %-20s | %-15s | %-25s |\n",
               "No.",
               "Name",
               "Phone",
               "Email");

        printf("====================================================================\n");


        //==================================================
        // READ CONTACTS
        //==================================================

        while(fgets(c.name, sizeof(c.name), file) &&

              fgets(c.phone, sizeof(c.phone), file) &&

              fgets(c.email, sizeof(c.email), file) &&

              fscanf(file, "%d", &c.favourite))
        {
            c.name[
                strcspn(c.name, "\n")
            ] = '\0';

            c.phone[
                strcspn(c.phone, "\n")
            ] = '\0';

            c.email[
                strcspn(c.email, "\n")
            ] = '\0';


            // Remove newline after favourite

            fgetc(file);


            if(c.favourite == 1)
            {
                printf("| %-3d | %-20s | %-15s | %-25s |\n",
                       serial,
                       c.name,
                       c.phone,
                       c.email);

                serial++;

                found = 1;
            }
        }


        printf("====================================================================\n");


        fclose(file);


        if(found == 0)
        {
            printf("\nNo Favourite Contact Available.\n");
        }


        printf("\n1. Refresh Favourite List");
        printf("\n2. Go to Main Menu");

        printf("\n\nEnter Choice: ");

        scanf("%d", &choice);


        if(choice == 2)
        {
            return;
        }
    }
}
