#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for rand() function
#include <unistd.h> // Include unistd.h for usleep() function

#define WHEEL_SIZE 10

int rules(); // Function prototype for rules

int round1(char name[], int *deposit); // Function prototype for round1

void spinWheel(); // Function prototype for spinWheel

int main()
{
    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);

    printf("\n\n");

    int deposit;
    printf("Enter the amount of money to deposit for the game:$ ");
    scanf("%d", &deposit);

    printf("\n\n");

    rules(); // Print the rules

    printf("\n\n");

    round1(name, &deposit); // Start round 1 with player's name and balance

    return 0;
}

int round1(char name[], int *deposit) 
{
    int new_deposit; // Declare new_deposit at the beginning of the function

    printf("Hello, %s!\n", name);
    printf("Your current balance is $%d\n\n", *deposit);

    int bet;
    printf("Enter the amount of money to bet: $");
    scanf("%d", &bet);

    printf("\n\n");

    while (bet > *deposit)
    {
        printf("Bet exceeds your balance. Please enter a valid bet: $");
        scanf("%d", &bet);
        printf("\n");
    }

    int computer = rand() % WHEEL_SIZE + 1; // Generate a random number from 1 to WHEEL_SIZE

    int guess;
    printf("Guess a number from 1 to %d: ", WHEEL_SIZE);
    scanf("%d", &guess);

    printf("\n\n");

    if (guess < 1 || guess > WHEEL_SIZE)
    {
        printf("Number exceeds the range. Please enter a number between 1 and %d.\n", WHEEL_SIZE);
        return 1; // Return 1 to indicate error
    }

    spinWheel(); // Call the spinning wheel animation

    if (guess == computer)
    {
        printf("Congratulations! You have won $%d\n", bet);
        *deposit = *deposit + bet * 10;
        printf("Your new balance is $%d\n", *deposit);
    }
    else
    {
        printf("Sorry, you have lost $%d\n", bet);
        printf("The correct number was %d\n", computer);
        *deposit = *deposit - bet;
        printf("Your new balance is $%d\n", *deposit);
    }

    if (*deposit == 0) // Check if the balance is zero
    {
        int option;
        printf("\nYour balance is zero. What would you like to do?\n");
        printf("1. Add more money and continue betting\n");
        printf("2. Exit from betting\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        if (option == 1)
        {
            printf("Enter the amount of money to add: $");
            scanf("%d", &new_deposit);
            *deposit = new_deposit;
            printf("Your new balance is $%d\n", *deposit);
        }
        else if (option == 2)
        {
            printf("Exiting from betting. Thank you for playing, %s! Have a nice day.\n", name);
            return 0;
        }
        else
        {
            printf("Invalid option. Exiting from betting.\n");
            return 0;
        }
    }

    int decision;
    printf("Do you want to continue playing? (1 for Yes, 2 for No): ");
    scanf("%d", &decision);
    printf("\n\n");

    if (decision == 1)
    {
        round1(name, deposit); // Continue playing with updated balance
    }
    else if (decision == 2)
    {
        printf("Thank you for playing, %s! Have a nice day.\n", name);
    }

    return 0;
}

void spinWheel()
{
    printf("Spinning wheel...\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\\");
        fflush(stdout);
        usleep(500000); // 0.5 seconds
        printf("\r|");
        fflush(stdout);
        usleep(500000);
    }
}

int rules()
{
    printf("------------------------------------------------------------------\n");
    printf("RULES\n");
    printf("------------------------------------------------------------------\n");
    printf("Choose any number from 1 to %d\n", WHEEL_SIZE);
    printf("If you win, you will get 10 times the money you bet\n");
    printf("If you bet on the wrong number, you will lose your betting amount\n");
    printf("------------------------------------------------------------------\n");
}
