/*------------------------------------------------------------------------------
Author: Abner
Wrote in C programming language
Compiled by Dev-C/C++ 4.9 & GNU C Compiler
Wrote for: CIS 6650, UoG

This program is focused on calculating the 990,000th prime number and printing 
this prime number on screen.

Reference: [1] <C++ Programming Language>,Qian, N.(2005) 

Date: 2011.01.30
------------------------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

/********************************************************************************
Funtion name: Primality
Return: Get the approximate number of prime numbers <= n
Created: 2011.02.01
********************************************************************************/

unsigned long int Primality (unsigned long int n)
{
     return (unsigned long int)(n/(log(n)-(double)(1.08366)));
}


//Program entry
int main()
{
     int n = 2; // Count the number of prime
     unsigned long int num = 3; // Initial number, program actually starting from 5. by definition 1 is not prime and composite, even number bigger than 2 is not prime, and sqrt(5) > 2.
     int i, temp;
     int flagPrime = 1; // C do not have Boolean. 
     int* prime = (int *)malloc(999999*sizeof(int)); // Storing previous primes.

     prime[0]=2;
     prime[1]=3; //Because starting from number 5.
     prime[2]=-1; //Flag node, means end of array.
     
     clock_t start, finish; //timer
     start = clock();

     while( n != 990000 )
     {
            num = num+2; //Skipping the even numbers, just check the odd numbers.
            temp = sqrt(num); //Just for storing, reducing time usage of program.
	    //temp = num/2; //for testing, the time costs amazing long showing '-211.137296s'. Obviously, it's overflowed. 
            for( i = 0; prime[i] != -1; i ++) 
            {
                 if ( prime[i] > temp) // Got this theorem for a programming book[1], if a number is prime, there is a factor smaller than square root of the number. 
                         break;
                 if ( num%prime[i] == 0) //If a number is composite, it must have one prime factor.
                    {
                         flagPrime = 0;
                         break;
                                  }
                 }
            if( flagPrime == 1 )
            {
                    prime[n] = num;      
                    n++;
                    prime[n] = -1; // Ending array flag
                    }
            else
                flagPrime = 1; // reset flag.
                }
     finish = clock();

     free(prime);       
     printf("The 990000th prime number is: %ld .\n", num);
     printf("The program consumes %4.2f s.\n", (double)(finish-start)/CLOCKS_PER_SEC); //The time consumer is different depending on CPU and OS.
     printf("The number of %ld by prime number theorm approximately is: %ld th.\n",num, Primality(num+1));
     scanf("%d"); //Just for pause program.
     
     return 0;
     }
