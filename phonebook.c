#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50
#define MAX_PHONE 25
#define MAX_CATEGORY 20
#define MAX_PHONE 25
#define MAX_SOCIALS 5
#define MAX_SOCIAL_NAME 20

#define MAX_USERNAME_LENGTH 49
#define MAX_PASSWORD_LENGTH 49
#define MAX_ATTEMPTS 5

typedef struct
{
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char category[MAX_CATEGORY];
    bool favorite;
    char social_links[MAX_SOCIALS][MAX_SOCIAL_NAME];
    int social_count;
    int linked_contacts[MAX_CONTACTS];
    int linked_count;
} Contact;

Contact contacts[MAX_CONTACTS];
int contact_count = 0;




bool authenticate() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    int attempts = 0;

    printf("Welcome to the Phonebook Authentication!\n");

    while (attempts < MAX_ATTEMPTS) {
        printf("username: ");
        if (scanf("%49s", username) != 1) {
            printf("Invalid input for username. Please try again.\n");

            while (getchar() != '\n');
            continue;
        }

        printf("password: ");
        if (scanf("%49s", password) != 1) {
            printf("Invalid input for password. Please try again.\n");

            while (getchar() != '\n');
            continue;
        }


        printf("\nYou are entered:\n");
        printf("username: %s\n", username);
        printf("password: %s\n", password);


        printf("\nLogin successful! Welcome to the Phonebook application.\n");
        return true;


    }
    return false;
}
// Add Contact
void add_contact()
{
    if (contact_count >= MAX_CONTACTS)
    {
        printf("Contact list is full.\n");
        return;
    }

    Contact new_contact;
    char country_code[5];

    printf("Enter Name: ");
    scanf(" %[^\n]", new_contact.name);

    while (1)
    {
        printf("Enter Country (USA, IND, BAN): ");
        scanf(" %[^\n]", new_contact.category);

        if (strcmp(new_contact.category, "USA") == 0)
        {
            strcpy(country_code, "+1");
            break;
        }
        else if (strcmp(new_contact.category, "IND") == 0)
        {
            strcpy(country_code, "+91");
            break;
        }
        else if (strcmp(new_contact.category, "BAN") == 0)
        {
            strcpy(country_code, "+880");
            break;
        }
        else
        {
            printf("Invalid category! Please enter 'USA', 'IND', or 'BAN'.\n");
        }
    }
    while (1)
    {
        printf("Enter 10-digit Phone Number: ");
        scanf(" %[^\n]", new_contact.phone);

        if (strlen(new_contact.phone) == 10)
        {
            break;
        }
        else
        {
            printf("Invalid number! Please enter exactly 10 digits.\n");
        }
    }
    char full_phone[MAX_PHONE];
    snprintf(full_phone, MAX_PHONE, "%s-%s", country_code, new_contact.phone);
    strcpy(new_contact.phone, full_phone);


// Category Selection (Family, Friends, etc.)
    int cat_choice;
    printf("\nSelect Contact Category:\n");
    printf("1. Family\n");
    printf("2. Friends\n");
    printf("3. Work\n");
    printf("4. Gym Buddies\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &cat_choice);

    switch (cat_choice)
    {
    case 1:
        strcpy(new_contact.category, "Family");
        break;
    case 2:
        strcpy(new_contact.category, "Friends");
        break;
    case 3:
        strcpy(new_contact.category, "Work");
        break;
    case 4:
        strcpy(new_contact.category, "Gym Buddies");
        break;
    default:
        printf("Invalid category choice. Setting to 'Uncategorized'.\n");
        strcpy(new_contact.category, "Uncategorized");
    }
    char fav_choice;
    printf("Mark as favorite? (y/n): ");
    scanf(" %c", &fav_choice);
    new_contact.favorite = (fav_choice == 'y' || fav_choice == 'Y');

    printf("\nLink social media accounts to this contact (e.g., Facebook, WhatsApp):\n");
    printf("How many platforms to link (max %d)? ", MAX_SOCIALS);
    scanf("%d", &new_contact.social_count);

// Validate
    if (new_contact.social_count > MAX_SOCIALS)
    {
        new_contact.social_count = MAX_SOCIALS;
    }

    for (int i = 0; i < new_contact.social_count; i++)
    {
        printf("Enter platform %d: ", i + 1);
        scanf(" %[^\n]", new_contact.social_links[i]);
    }
    contacts[contact_count++] = new_contact;
    printf("Contact added successfully!\n");
}

// Edit Contact
void edit_contact()
{
    char name[MAX_NAME];
    printf("Enter name of contact to edit: ");
    scanf(" %s", name);

    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            printf("New Name: ");
            char new_name[MAX_NAME];
            scanf(" %s", new_name);
            if (strlen(new_name) > 0)
            {
                strcpy(contacts[i].name, new_name);
            }
            printf("Contact edited.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

// Delete Contact
void delete_contact()
{
    char name[MAX_NAME];
    printf("Enter name of contact to delete: ");
    scanf(" %s", name);

    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            for (int j = i; j < contact_count - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            contact_count--;
            printf("Contact deleted.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

// Search Contacts
void search_contacts()
{
    char search_term[MAX_NAME];
    printf("Enter search term: ");
    scanf(" %s", search_term);

    for (int i = 0; i < contact_count; i++)
    {
        if (strstr(contacts[i].name, search_term) != NULL ||
                strstr(contacts[i].category, search_term) != NULL)

;    }
}

// View Contacts
void view_contacts()
{
    if (contact_count == 0)
    {
        printf("No contacts.\n");
        return;
    }

    for (int i = 0; i < contact_count; i++)
    {
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Category: %s\n", contacts[i].category);
        printf("Favorite: %s\n", contacts[i].favorite ? "Yes" : "No");
        printf("Linked Social Media: ");
        if (contacts[i].social_count == 0)
        {
            printf("None\n");
        }
        else
        {
            for (int j = 0; j < contacts[i].social_count; j++)
            {
                printf("%s", contacts[i].social_links[j]);
                if (j < contacts[i].social_count - 1) printf(", ");
            }
            printf("\n");
        }
    }
    printf("\n");
}
//link_contacts
void link_contacts()
{
    char name1[MAX_NAME], name2[MAX_NAME];
    printf("Enter the name of the main contact: ");
    scanf(" %[^\n]", name1);
    printf("Enter the name of the contact to link: ");
    scanf(" %[^\n]", name2);

    int index1 = -1, index2 = -1;
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, name1) == 0)
            index1 = i;
        if (strcmp(contacts[i].name, name2) == 0)
            index2 = i;
    }

    if (index1 == -1 || index2 == -1)
    {
        printf("One or both contacts not found.\n");
        return;
    }

    if (index1 == index2)
    {
        printf("A contact cannot be linked to itself.\n");
        return;
    }

    // Check for duplicates
    for (int i = 0; i < contacts[index1].linked_count; i++)
    {
        if (contacts[index1].linked_contacts[i] == index2)
        {
            printf("These contacts are already linked.\n");
            return;
        }
    }

    contacts[index1].linked_contacts[contacts[index1].linked_count++] = index2;
    printf("Contact '%s' linked to '%s'.\n", contacts[index1].name, contacts[index2].name);
}
//categorize_contacts
void categorize_contacts()
{
    if (contact_count == 0)
    {
        printf("No contacts available.\n");
        return;
    }

    char category[MAX_CATEGORY];
    printf("Enter category to filter by (e.g., Family, Friends, Work): ");
    scanf(" %[^\n]", category);

    bool found = false;

    printf("\n--- Contacts in Category: %s ---\n", category);
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].category, category) == 0)
        {
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Favorite: %s\n", contacts[i].favorite ? "Yes" : "No");

            // Show linked social media if any
            if (contacts[i].social_count > 0)
            {
                printf("Linked Social Media: ");
                for (int j = 0; j < contacts[i].social_count; j++)
                {
                    printf("%s", contacts[i].social_links[j]);
                    if (j < contacts[i].social_count - 1) printf(", ");
                }
                printf("\n");
            }

            printf("\n");
            found = true;
        }
    }

    if (!found)
    {
        printf("No contacts found in category '%s'.\n", category);
    }
}
//sort_contacts
void sort_contacts()
{
    for (int i = 0; i < contact_count - 1; i++)
    {
        for (int j = i + 1; j < contact_count; j++)
        {
            if (strcmp(contacts[i].name, contacts[j].name) > 0)
            {
                Contact temp = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temp;
            }
        }
    }

    printf("Contacts sorted by name.\n");
}
// filter_by_category
void filter_by_category()
{
    char category[MAX_CATEGORY];
    printf("Enter category to filter (e.g., Family, Work, Gym): ");
    scanf(" %[^\n]", category);

    bool found = false;
    printf("\n--- Contacts in Category: %s ---\n", category);

    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].category, category) == 0)
        {
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Favorite: %s\n\n", contacts[i].favorite ? "Yes" : "No");
            found = true;
        }
    }

    if (!found)
    {
        printf("No contacts found in category '%s'.\n", category);
    }
}
//filter_by_favorites
void filter_by_favorites()
{
    printf("\n--- Favorite Contacts ---\n");
    bool found = false;

    for (int i = 0; i < contact_count; i++)
    {
        if (contacts[i].favorite)
        {
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Category: %s\n\n", contacts[i].category);
            found = true;
        }
    }
    if (!found)
    {
        printf("No favorite contacts found.\n");
    }
}
//backup_contacts
void backup_contacts() {
    FILE *file = fopen("contacts_backup.txt", "w");
    if (file == NULL) {
        printf("Error creating backup file.\n");
        return;
    }

    for (int i = 0; i < contact_count; i++) {
        // Write basic contact info
        fprintf(file, "%s|%s|%s|%s|%d|%d|%d",
                contacts[i].name,
                contacts[i].phone,
                contacts[i].category,
                contacts[i].favorite,
                contacts[i].social_count,
                contacts[i].linked_count);

        // Write social media links
        for (int j = 0; j < contacts[i].social_count; j++) {
            fprintf(file, "|%s", contacts[i].social_links[j]);
        }

        // Write linked contacts indices
        for (int j = 0; j < contacts[i].linked_count; j++) {
            fprintf(file, "|%d", contacts[i].linked_contacts[j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);
    printf("Contacts backed up successfully! (%d contacts saved)\n", contact_count);
}

void restore_contacts() {
    FILE *file = fopen("contacts_backup.txt", "r");
    if (file == NULL) {
        printf("No backup file found.\n");
        return;
    }

    contact_count = 0;
    char line[1024]; // Increased buffer size

    while (fgets(line, sizeof(line), file) && contact_count < MAX_CONTACTS) {
        // Remove newline and check for empty lines
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        Contact c;
        memset(&c, 0, sizeof(Contact));

        // First token is name
        char *token = strtok(line, "|");
        if (!token) continue;
        strncpy(c.name, token, MAX_NAME-1);

        // Subsequent tokens in fixed order
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(c.phone, token, MAX_PHONE-1);

        token = strtok(NULL, "|");
        if (!token) continue;

        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(c.category, token, MAX_CATEGORY-1);

        token = strtok(NULL, "|");
        if (!token) continue;
        c.favorite = atoi(token);

        token = strtok(NULL, "|");
        if (!token) continue;
        c.social_count = atoi(token);
        if (c.social_count > MAX_SOCIALS) c.social_count = MAX_SOCIALS;

        token = strtok(NULL, "|");
        if (!token) continue;
        c.linked_count = atoi(token);
        if (c.linked_count > MAX_CONTACTS) c.linked_count = MAX_CONTACTS;

        // Read social media links
        for (int j = 0; j < c.social_count; j++) {
            token = strtok(NULL, "|");
            if (!token) break;
            strncpy(c.social_links[j], token, MAX_SOCIAL_NAME-1);
        }

        // Read linked contacts indices
        for (int j = 0; j < c.linked_count; j++) {
            token = strtok(NULL, "|");
            if (!token) break;
            c.linked_contacts[j] = atoi(token);
        }

        contacts[contact_count++] = c;
    }

    fclose(file);
    printf("Contacts restored successfully! (%d contacts loaded)\n", contact_count);
}

// Main Part
int main()
{
    if (!authenticate())
    {
        return 1;
    }
    int choice;
    do
    {
        printf("\nPhonebook Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Edit Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Search Contacts\n");
        printf("5. View Contacts\n");
        printf("6. Link Contacts\n");
        printf("7. Categorize Contacts\n");
        printf("8 Sort Contacts by Name\n");
        printf("9. Filter by Category\n");
        printf("10. Filter  by Favorites\n");
        printf("11. Backup Contacts\n");
        printf("12. Restore Contacts\n");
        printf("13. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_contact();
            break;
        case 2:
            edit_contact();
            break;
        case 3:
            delete_contact();
            break;
        case 4:
            search_contacts();
            break;
        case 5:
            view_contacts();
            break;
        case 6:
            link_contacts();
            break;
        case 7:
            categorize_contacts();
            break;
        case 8:
            sort_contacts();
            break;
        case 9:
            filter_by_category();
            break;
        case 10:
            filter_by_favorites();
            break;
        case 11:
            backup_contacts();
            break;
        case 12:
            restore_contacts();
            break;
        case 13:
            printf("Exiting.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
    while (choice != 13);

    return 0;
}
