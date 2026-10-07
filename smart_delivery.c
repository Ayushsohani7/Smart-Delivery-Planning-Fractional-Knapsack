/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>

#define MAX 100

// Structure to store package details
struct Package
{
    int id;
    float value;
    float weight;
    float ratio;
    float fraction;
};

// Function to calculate value/weight ratio
void calculateRatio(struct Package p[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (p[i].weight > 0)
            p[i].ratio = p[i].value / p[i].weight;
        else
            p[i].ratio = 0;
    }

    printf("\nValue/Weight ratios calculated successfully.\n");
}

// Function to sort packages by decreasing ratio
void sortPackages(struct Package p[], int n)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].ratio < p[j + 1].ratio)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("\nPackages sorted by decreasing Value/Weight ratio.\n");
}

// Function to display package details
void displayPackages(struct Package p[], int n)
{
    int i;

    printf("\n------------------------------------------------------------\n");
    printf("ID\tValue\tWeight\tRatio\n");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }

    printf("------------------------------------------------------------\n");
}

// Function to find maximum value
float findMaximumValue(struct Package p[], int n, float capacity)
{
    int i;
    float remainingCapacity = capacity;
    float totalValue = 0;

    for (i = 0; i < n; i++)
    {
        p[i].fraction = 0;

        if (remainingCapacity <= 0)
            break;

        // Take complete package
        if (p[i].weight <= remainingCapacity)
        {
            p[i].fraction = 1.0;
            remainingCapacity -= p[i].weight;
            totalValue += p[i].value;
        }
        // Take required fraction
        else
        {
            p[i].fraction = remainingCapacity / p[i].weight;
            totalValue += p[i].value * p[i].fraction;
            remainingCapacity = 0;
        }
    }

    return totalValue;
}

// Function to display selected packages
void displaySelectedPackages(struct Package p[], int n)
{
    int i;

    printf("\n------------------------------------------------------------\n");
    printf("Selected Packages\n");
    printf("------------------------------------------------------------\n");
    printf("ID\tFraction\tWeight Used\tValue Obtained\n");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (p[i].fraction > 0)
        {
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   p[i].id,
                   p[i].fraction,
                   p[i].weight * p[i].fraction,
                   p[i].value * p[i].fraction);
        }
    }

    printf("------------------------------------------------------------\n");
}

int main()
{
    struct Package packages[MAX];

    int n = 0;
    int choice;
    int i;

    float capacity = 0;
    float maximumValue = 0;

    do
    {
        printf("\n========== SMART DELIVERY PLANNING ==========\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("==============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nEnter number of packages: ");
                scanf("%d", &n);

                if (n <= 0 || n > MAX)
                {
                    printf("Invalid number of packages.\n");
                    n = 0;
                    break;
                }

                for (i = 0; i < n; i++)
                {
                    packages[i].id = i + 1;
                    packages[i].fraction = 0;

                    printf("\nPackage %d\n", i + 1);

                    printf("Enter value/profit: ");
                    scanf("%f", &packages[i].value);

                    printf("Enter weight: ");
                    scanf("%f", &packages[i].weight);

                    if (packages[i].weight <= 0)
                    {
                        printf("Weight must be greater than 0.\n");
                        i--;
                        continue;
                    }
                }

                printf("\nEnter vehicle capacity: ");
                scanf("%f", &capacity);

                if (capacity <= 0)
                {
                    printf("Capacity must be greater than 0.\n");
                }
                else
                {
                    printf("\nPackage details entered successfully.\n");
                }
                break;

            case 2:
                if (n == 0)
                {
                    printf("\nPlease enter package details first.\n");
                }
                else
                {
                    displayPackages(packages, n);
                }
                break;

            case 3:
                if (n == 0)
                {
                    printf("\nPlease enter package details first.\n");
                }
                else
                {
                    calculateRatio(packages, n);
                    displayPackages(packages, n);
                }
                break;

            case 4:
                if (n == 0)
                {
                    printf("\nPlease enter package details first.\n");
                }
                else
                {
                    calculateRatio(packages, n);
                    sortPackages(packages, n);
                    displayPackages(packages, n);
                }
                break;

            case 5:
                if (n == 0)
                {
                    printf("\nPlease enter package details first.\n");
                }
                else
                {
                    calculateRatio(packages, n);
                    sortPackages(packages, n);

                    maximumValue =
                        findMaximumValue(packages, n, capacity);

                    printf("\nTotal weight capacity : %.2f\n", capacity);
                    printf("Maximum value obtained : %.2f\n",
                           maximumValue);
                }
                break;

            case 6:
                if (n == 0)
                {
                    printf("\nPlease enter package details first.\n");
                }
                else
                {
                    displaySelectedPackages(packages, n);
                }
                break;

            case 7:
                printf("\nProgram terminated successfully.\n");
                break;

            default:
                printf("\nInvalid menu choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
