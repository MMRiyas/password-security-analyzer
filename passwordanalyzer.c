#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>   // EXIT_SUCCESS, EXIT_FAILURE, rand, srand
#include <math.h>     // log() for entropy calculation
#include <time.h>     // time() for random seed

// Maximum number of dictionary words
#define MAX_WORD 100

// Maximum length of passwords and dictionary entries
#define MAX_LEN 100


/* --------------------------------------------------
   Utility Function: Convert string to lowercase
   --------------------------------------------------
*/
void toLowerCase(char str[])
{
    for (int i = 0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);
}


/* --------------------------------------------------
   Load Dictionary Function
   --------------------------------------------------
   Reads common weak passwords from dictionary.txt
   Stores them in a 2D array
   Returns the number of words loaded
*/
int load_dictionary(char dictionary[][MAX_LEN])
{
    FILE *file = fopen("dictionary.txt", "r");
    if (file == NULL)
    {
        perror("Error opening dictionary");
        return 0;
    }

    int count = 0;

    // Read each line (one password per line)
    while (count < MAX_WORD && fgets(dictionary[count], MAX_LEN, file))
    {
        // Remove newline character
        dictionary[count][strcspn(dictionary[count], "\n")] = '\0';
        count++;
    }

    fclose(file);
    return count;
}


/* --------------------------------------------------
   Analyze Password Function
   --------------------------------------------------
   Performs:
   - Dictionary check
   - Length analysis
   - Pattern detection
   - Character type checks
   - Entropy calculation
   - Final strength scoring
*/
void analyze_password(char dictionary[][MAX_LEN], int dict_count)
{
    char password[MAX_LEN];

    // Read password from user
    printf("Enter a password to analyze: ");
    scanf("%99s", password);

    // Convert to lowercase for dictionary checking
    toLowerCase(password);


    /* ---------- Dictionary Check ---------- */
    int found = 0;
    for (int i = 0; i < dict_count; i++)
    {
        // Check if dictionary word is a substring
        if (strstr(password, dictionary[i]) != NULL)
        {
            found = 1;
            break;
        }
    }

    printf("Dictionary word detected: %s\n", found ? "Yes" : "No");


    /* ---------- Length Check ---------- */
    int length = strlen(password);
    printf("Password length: %d\n", length);

    if (length < 8)
        printf("Length Strength: Weak\n");
    else if (length <= 12)
        printf("Length Strength: Moderate\n");
    else
        printf("Length Strength: Strong\n");


    /* ---------- Repeated Character Detection ---------- */
    int repeated = 0;
    for (int i = 0; password[i + 2]; i++)
    {
        if (password[i] == password[i + 1] &&
            password[i] == password[i + 2])
        {
            repeated = 1;
            break;
        }
    }
    printf("Repeated pattern: %s\n", repeated ? "Yes" : "No");


    /* ---------- Sequential Pattern Detection ---------- */
    int sequential = 0;
    for (int i = 0; password[i + 2]; i++)
    {
        if (password[i + 1] == password[i] + 1 &&
            password[i + 2] == password[i] + 2)
        {
            sequential = 1;
            break;
        }
    }
    printf("Sequential pattern: %s\n", sequential ? "Yes" : "No");


    /* ---------- Character Type Analysis ---------- */
    int has_upper = 0, has_lower = 0, has_digit = 0, has_symbol = 0;

    for (int i = 0; password[i]; i++)
    {
        if (isupper((unsigned char)password[i]))
            has_upper = 1;
        else if (islower((unsigned char)password[i]))
            has_lower = 1;
        else if (isdigit((unsigned char)password[i]))
            has_digit = 1;
        else
            has_symbol = 1;
    }

    printf("--- Character Analysis ---\n");
    printf("Uppercase: %s\n", has_upper ? "Yes" : "No");
    printf("Lowercase: %s\n", has_lower ? "Yes" : "No");
    printf("Digits: %s\n", has_digit ? "Yes" : "No");
    printf("Symbols: %s\n", has_symbol ? "Yes" : "No");


    /* ---------- Entropy Calculation ---------- */
    int charset = 0;
    if (has_upper)  charset += 26;
    if (has_lower)  charset += 26;
    if (has_digit)  charset += 10;
    if (has_symbol) charset += 33;

    double entropy = 0.0;
    if (charset > 0)
        entropy = length * log(charset) / log(2);

    printf("Estimated Entropy: %.2f bits\n", entropy);


    /* ---------- Final Scoring ---------- */
    int score = 0;

    // Length contribution
    if (length >= 12) score += 30;
    else if (length >= 8) score += 20;
    else score += 5;

    // Character variety contribution
    int variety = has_upper + has_lower + has_digit + has_symbol;
    score += variety * 7;

    // Entropy contribution
    if (entropy >= 60) score += 20;
    else if (entropy >= 40) score += 10;

    // Penalties
    if (repeated) score -= 10;
    if (sequential) score -= 10;
    if (found) score -= 20;

    // Clamp score to range 0–100
    if (score < 0) score = 0;
    if (score > 100) score = 100;

    // Final strength verdict
    if (score < 40)
        printf("Overall Strength: Weak (%d/100)\n", score);
    else if (score < 70)
        printf("Overall Strength: Moderate (%d/100)\n", score);
    else
        printf("Overall Strength: Strong (%d/100)\n", score);
}


/* --------------------------------------------------
   Password Generator Function
   --------------------------------------------------
   Generates a secure random password
   Ensures all character categories are used
*/
void generate_password(void)
{
    int length;
    printf("Enter desired password length (min 8): ");

    // Validate numeric input
    if (scanf("%d", &length) != 1)
    {
        printf("Invalid input. Enter a number.\n");
        while (getchar() != '\n');
        return;
    }

    // Validate length range
    if (length < 8 || length > 64)
    {
        printf("Invalid length. Choose between 8 and 64.\n");
        return;
    }

    const char upper[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lower[]   = "abcdefghijklmnopqrstuvwxyz";
    const char digits[]  = "0123456789";
    const char symbols[] = "!@#$%^&*()-_=+[]{};:,.<>?";

    const char all[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:,.<>?";

    char password[MAX_LEN];

    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Ensure at least one character from each category
    password[0] = upper[rand() % 26];
    password[1] = lower[rand() % 26];
    password[2] = digits[rand() % 10];
    password[3] = symbols[rand() % 30];

    // Fill remaining characters randomly
    for (int i = 4; i < length; i++)
        password[i] = all[rand() % (sizeof(all) - 1)];

    // Shuffle password characters
    for (int i = 0; i < length; i++)
    {
        int j = rand() % length;
        char temp = password[i];
        password[i] = password[j];
        password[j] = temp;
    }

    password[length] = '\0';

    printf("Generated Secure Password:\n%s\n", password);
}


/* --------------------------------------------------
   Main Function
   --------------------------------------------------
*/
int main(void)
{
    char dictionary[MAX_WORD][MAX_LEN];

    // Load dictionary once
    int dict_count = load_dictionary(dictionary);
    if (dict_count == 0)
        return EXIT_FAILURE;

    int choice;

    do
    {
        printf("\n--- Password Security Analyzer ---\n");
        printf("1. Generate a secure password\n");
        printf("2. Analyze a password\n");
        printf("3. Password security guidelines\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");

        // Validate menu input
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                generate_password();
                break;

            case 2:
                analyze_password(dictionary, dict_count);
                break;

            case 3:
                printf("\nPassword Guidelines:\n");
                printf("- Use at least 12 characters\n");
                printf("- Mix uppercase, lowercase, digits, symbols\n");
                printf("- Avoid dictionary words\n");
                printf("- Avoid repeated or sequential patterns\n");
                printf("- Do not reuse passwords\n");
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return EXIT_SUCCESS;
}
