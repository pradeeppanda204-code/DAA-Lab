/*
-------------------------------------------------------
Program    : Question 2
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Ranjan kumar Nandi
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, i;
    int fairHeads = 0, biasedHeads = 0;
    double p = 0.7;  

    printf("Enter number of tosses: ");
    scanf("%d", &n);

    srand(time(NULL));
    for(i = 0; i < n; i++) {
        if(rand() % 2 == 0)
            fairHeads++;
    }
    for(i = 0; i < n; i++) {
        double r = (double)rand() / RAND_MAX;
        if(r < p)
            biasedHeads++;
    }

    printf("\n--- Results ---\n");
    printf("Fair Coin:\n");
    printf("Heads = %d\n", fairHeads);
    printf("Probability of Heads = %.4f\n", (double)fairHeads / n);

    printf("\nBiased Coin (P(H)=%.2f):\n", p);
    printf("Heads = %d\n", biasedHeads);
    printf("Probability of Heads = %.4f\n", (double)biasedHeads / n);

    return 0;
}
