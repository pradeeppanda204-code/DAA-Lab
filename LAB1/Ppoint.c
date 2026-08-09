/*
-------------------------------------------------------
Program    : Question 5
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Ranjan kumar Nandi
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/
#include <stdio.h>

int findPartition(int arr[], int n)
{
    int low = 0, high = n - 1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (arr[mid] == 1 && (mid == 0 || arr[mid - 1] == 0))
            return mid;

        if (arr[mid] == 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements (0's followed by 1's):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int index = findPartition(arr, n);

    if (index == -1)
        printf("No partition point found.\n");
    else
        printf("Partition point is at index %d\n", index);

    return 0;
}
