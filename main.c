// 🔐 Password Manager (Console-Based)
// 💡 Description:

// Create a simple console-based password manager that stores website credentials (website name, username/email, password). It should let users:

// Add new credentials
// View saved credentials
// Search for credentials by website
// Update or delete entries
// Save and load data using file handling (binary or text file)

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_CREDENTIAL_AMOUNT 10
#define MAX_WORD_LENGTH 70
#define MAX_PASSWORD_LENGTH 28

//declare struct 
typedef struct {
    char websites[MAX_WORD_LENGTH];
    char usernames[MAX_WORD_LENGTH];
    char passwords[MAX_PASSWORD_LENGTH];
} CREDENTIAL;

typedef enum {
    ADD_CREDENTIAL = 1,
    VIEW_CREDENTIAL,
    SEARCH_BY_WEBSITE,
    UPDATE_ENTRY,
    DELETE_ENTRY,
    SAVE,
    LOAD,
    EXIT = 0
} CHOICE;

//function prototype for choice
void DisplayChoice(int *choice);
void AddCredential (CREDENTIAL credential[], int *count);

//function prototype for validation
int WebsiteValidation(const char *website);
int UsernameValidation(const char *username);
int PasswordValidation(const char *password);

//function prototype for system
void ClearInputBuffer();
void PauseScreen();
void ClearScreen();

int main(void) {
    //call out struct
    CREDENTIAL credential[MAX_CREDENTIAL_AMOUNT];

    //declare useful variable
    int choice_one = 1, credential_count = 0;

    while (choice_one != EXIT) {

        DisplayChoice(&choice_one);

        switch (choice_one) {
            case ADD_CREDENTIAL: AddCredential(credential, &credential_count); break;
            case VIEW_CREDENTIAL: break;
            case SEARCH_BY_WEBSITE: break;
            case UPDATE_ENTRY: break;
            case DELETE_ENTRY: break;
            case SAVE: break;
            case LOAD: break;
            case EXIT: break;
            default: printf("Invalid choice\n"); break;
        }
    }

    return 0;
}

void DisplayChoice(int *choice_one) {
    ClearScreen();
    printf("\n--- Password Manager Menu ---\n");
    printf("1. Add New Credential\n");
    printf("2. View All Credentials\n");
    printf("3. Search by website\n");
    printf("4. Update an entry\n");
    printf("5. Delete an entry\n");
    printf("6. Save to file\n");
    printf("7. Load from file\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
    scanf("%d", choice_one);
    ClearInputBuffer();
}

void AddCredential (CREDENTIAL credential[], int *count) {

    int current_website = *count; //for better readability
    char temp_input_website[MAX_WORD_LENGTH]; //set a temp input 
    char temp_input_username[MAX_WORD_LENGTH];
    char temp_input_password[MAX_PASSWORD_LENGTH];

    if(*count >= MAX_CREDENTIAL_AMOUNT) { //
        ClearScreen();
        printf("You've reached maximum credential count\n");
        return;
    } else {

        while(1) {

            ClearScreen();
            ClearInputBuffer(); //clear buffer before fgets

            printf("Enter website: ");

            fgets(temp_input_website , MAX_WORD_LENGTH, stdin);
            temp_input_website[strcspn(temp_input_website, "\n")] = '\0'; //newline remover

            //website validation  
            if  (!WebsiteValidation(temp_input_website)) { 
                printf("Invalid website. Try again\n");
                PauseScreen();
            } else {
                printf("Website added successfully\n");
                strcpy(credential[current_website].websites, temp_input_website);
                PauseScreen();
                break; 
            }
        }
        

        while(1) {

            ClearScreen();
            ClearInputBuffer(); //for next input 

            printf("Enter username: ");

            fgets(temp_input_username, MAX_WORD_LENGTH, stdin);
            temp_input_username[strcspn(temp_input_username, "\n")] = '\0'; //new line remover

            if (UsernameValidation(temp_input_username)) {
                printf("Username added succesfully\n");
                strcpy(credential[current_website].usernames, temp_input_username);
                PauseScreen();
                break;
            }

        }

        while(1) {
            ClearScreen();
            ClearInputBuffer(); //for next input 

            printf("Enter password: ");

            fgets(temp_input_password,MAX_PASSWORD_LENGTH, stdin);
            temp_input_password[strcspn(temp_input_password,"\n")] = '\0';

            if (PasswordValidation(temp_input_password)) {
                printf("Password added successfully\n");
                strcpy(credential[current_website].passwords, temp_input_password);
                PauseScreen();
                break;
            }
        }
        
    }

    



}

int WebsiteValidation(const char *website) {
    int length = strlen(website);
    
    if (length < 4) return 0;

    // Allow domain extensions of 2 to 6 characters
    char *dot_position = strrchr(website, '.');
    if (dot_position == NULL || (length - (dot_position - website)) < 4) {
        return 0;  // Invalid extension length
    }

    // Check for valid characters before the dot
    for (int i = 0; i < dot_position - website; i++) {
        if (!isalnum(website[i]) && website[i] != '.' && website[i] != '-') {
            return 0;
        }
    }

    // Validate if the extension is a valid domain extension
    if (strlen(dot_position) < 4) {
        return 0;  // Ensure extension is at least 2 characters long after the dot
    }

    return 1;
}


int UsernameValidation(const char *username) {
    int length = strlen(username);

    if (length < 12) { // at least something + "@gmail.com"
        printf("Username too short\n");
        PauseScreen();
        return 0;
    }

    // Check if it ends with "@gmail.com"
    const char *ending = "@gmail.com";
    int ending_len = strlen(ending);

    if (strcmp(username + (length - ending_len), ending) != 0) {
        printf("Invalid Username: must end with @gmail.com\n");
        PauseScreen();
        return 0;
    }

    // Check if all characters before '@' are valid
    for (int i = 0; i < length - ending_len; i++) {
        if (!isalnum(username[i]) && username[i] != '.' && username[i] != '-') {
            printf("Invalid username: Only alphanumeric, dot, and dash allowed before @\n");
            PauseScreen();
            return 0;
        }
    }

    return 1;
}

int PasswordValidation(const char *password) {
    int length = strlen(password);

    // Check for minimum length
    if (length < 8) {
        printf("Invalid password: Too short\n");
        PauseScreen();
        return 1;
    }

    // Flags for checking different criteria
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    // Iterate through the password to check for required characters
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            has_upper = 1;  // Found uppercase letter
        } else if (islower(password[i])) {
            has_lower = 1;  // Found lowercase letter
        } else if (isdigit(password[i])) {
            has_digit = 1;  // Found digit
        } else if (ispunct(password[i])) {
            has_special = 1;  // Found special character
        }
    }

    // Check if all conditions are met
    if (!has_upper) {
        printf("Invalid password: No uppercase letter\n");
        PauseScreen();
        return 0;
    }
    if (!has_lower) {
        printf("Invalid password: No lowercase letter\n");
        PauseScreen();
        return 0;
    }
    if (!has_digit) {
        printf("Invalid password: No digit\n");
        PauseScreen();
        return 0;
    }
    if (!has_special) {
        printf("Invalid password: No special character\n");
        PauseScreen();
        return 0;
    }

    return 1;
}

void ClearScreen() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void PauseScreen() { 

    printf("Press enter to continue...");
    getchar();

}

void ClearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
