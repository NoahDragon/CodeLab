#include <stdio.h>
/*
    It's the Insertation sort algorithm
    From <Introduction to Algorithms> 3rd ed. T.H. Cormen, C.E. Leiserson,
        R.L. Rivest, and C. Stein. 2009.
*/

void main(){
    int a[11] = {34,32,51,67,29,85,91,55,73,12,46};
    int key = -1;
    int i,j, temp;
    for( j=1 ; j<11; j++){
        key = a[j];
        i = j-1;
        while(i>=0 && a[i]>key){
            a[i+1] = a[i];
            i = i-1;
        }
        a[i+1] = key;
    }
    
    for(i=0; i<11; i++){
        printf("%d ", a[i]);
    }
}
