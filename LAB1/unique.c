/*
-------------------------------------------------------
Program    : Question 6
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Ranjan kumar Nandi
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/
#include <stdio.h>

int main()
{
    int n, i, j;
    int arr[100];
    int found = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nDuplicate elements are:\n");

    for(i = 0; i < n; i++)
    {
        int alreadyPrinted = 0;

        for(j = 0; j < i; j++)
        {
            if(arr[i] == arr[j])
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if(alreadyPrinted)
            continue;

        for(j = i + 1; j < n; j++)
        {
            if(arr[i] == arr[j])
            {
                printf("%d\n", arr[i]);
                found = 1;
                break;
            }
        }
    }

    if(found == 0)
    {
        printf("No duplicate elements found.");
    }

    return 0;
}
