/*
-------------------------------------------------------
Program    : Question 4
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Ranjan kumar Nandi
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/
#include <stdio.h>

int moves = 0;

void hanoi(int n, char L, char M, char R)
{
    if (n == 1)
    {
        printf("Move Disk 1 from %c to %c\n", L, R);
        moves++;
        return;
    }

    hanoi(n - 1, L, R, M);

    printf("Move Disk %d from %c to %c\n", n, L, R);
    moves++;

    hanoi(n - 1, M, L, R);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    hanoi(n, 'L', 'M', 'R');

    printf("\nTotal Moves = %d\n", moves);

    return 0;
}
