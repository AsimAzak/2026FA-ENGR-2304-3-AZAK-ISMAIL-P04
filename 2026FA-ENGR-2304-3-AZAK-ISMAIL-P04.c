/*
2026FA-ENGR-2304-3-AZAK-ISMAIL-P04
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int Vs;
    int R1;
    int R2;
    int R3;
} Circuit;

typedef struct
{
    double i1;
    double i2;
    double v1;
    double v2;
    double v3;
} Results;

double truncate3(double value)
{
    return (double)((long long)(value * 1000.0)) / 1000.0;
}

void clearInput(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

Circuit generateCircuit(void)
{
    Circuit c;
    c.Vs = rand() % 10 + 1;
    c.R1 = rand() % 20 + 1;
    c.R2 = rand() % 20 + 1;
    c.R3 = rand() % 20 + 1;
    return c;
}

Results solveCircuit(Circuit c)
{
    Results r;
    double determinant, i1, i2;

    determinant = (double)(c.R1 + c.R2) * (c.R2 + c.R3) - (double)c.R2 * c.R2;

    i1 = ((double)c.Vs * (c.R2 + c.R3)) / determinant;
    i2 = ((double)c.Vs * c.R2) / determinant;

    r.i1 = truncate3(i1);
    r.i2 = truncate3(i2);
    r.v1 = truncate3(i1 * c.R1);
    r.v2 = truncate3((i1 - i2) * c.R2);
    r.v3 = truncate3(i2 * c.R3);

    return r;
}

void printCircuit(Circuit c)
{
    printf("\n--------------------------------------------\n");
    printf("Circuit Values\n");
    printf("--------------------------------------------\n");
    printf("Vs = %d V\n", c.Vs);
    printf("R1 = %d ohms\n", c.R1);
    printf("R2 = %d ohms\n", c.R2);
    printf("R3 = %d ohms\n", c.R3);
}

int readAnswer(const char *label, double *value)
{
    int status;

    printf("%s: ", label);
    status = scanf("%lf", value);

    if (status == EOF)
    {
        return -1;
    }
    if (status != 1)
    {
        printf("Invalid input. Please enter a numeric value.\n");
        clearInput();
        return 0;
    }

    *value = truncate3(*value);
    return 1;
}

int readUserResults(Results *user)
{
    int status;

    if ((status = readAnswer("i1 (A)", &user->i1)) != 1) return status;
    if ((status = readAnswer("i2 (A)", &user->i2)) != 1) return status;
    if ((status = readAnswer("v1 (V)", &user->v1)) != 1) return status;
    if ((status = readAnswer("v2 (V)", &user->v2)) != 1) return status;
    if ((status = readAnswer("v3 (V)", &user->v3)) != 1) return status;
    return 1;
}

int resultsMatch(Results a, Results b)
{
    return a.i1 == b.i1 && a.i2 == b.i2 &&
           a.v1 == b.v1 && a.v2 == b.v2 && a.v3 == b.v3;
}

void printFeedback(int correct, Results correctResults)
{
    printf("\n============================================\n");

    if (correct)
    {
        printf("SUCCESS: All answers are correct.\n");
    }
    else
    {
        printf("FAILURE: One or more answers are incorrect.\n");
        printf("\nCorrect answers:\n");
        printf("i1 = %.3f A\n", correctResults.i1);
        printf("i2 = %.3f A\n", correctResults.i2);
        printf("v1 = %.3f V\n", correctResults.v1);
        printf("v2 = %.3f V\n", correctResults.v2);
        printf("v3 = %.3f V\n", correctResults.v3);
    }

    printf("============================================\n");
}

int readMenuChoice(void)
{
    int choice;
    printf("\nEnter 1 to generate a new circuit or 0 to exit: ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice. Program will exit.\n");
        choice = 0;
    }
    clearInput();
    return choice;
}

int main(void)
{
    int choice = 1;

    srand((unsigned int)time(NULL));

    printf("============================================\n");
    printf("        ENGR 2304 - Circuit Analysis P04\n");
    printf("============================================\n");

    while (choice == 1)
    {
        Circuit circuit = generateCircuit();
        Results correctResults = solveCircuit(circuit);
        Results userResults;
        int status;

        printCircuit(circuit);
        printf("\nEnter your answers (3 decimal places):\n");

        status = readUserResults(&userResults);
        if (status == -1)
        {
            break;
        }
        if (status == 0)
        {
            continue;
        }

        printFeedback(resultsMatch(userResults, correctResults), correctResults);

        choice = readMenuChoice();
    }

    printf("\nProgram terminated.\n");

    return 0;
}