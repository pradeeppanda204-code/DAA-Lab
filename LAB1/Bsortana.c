/*
-------------------------------------------------------
Program    : Question 3
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Ranjan kumar Nandi
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/
#include <stdio.h>

void BSortana(int arr[], int n)
{
    int i, j, temp;
    int swapped;
    int comparisons = 0;

    for (i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    printf("Sorted Array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\nTotal Comparisons = %d\n", comparisons);
}

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    BSortana(arr, n);

    return 0;
}
