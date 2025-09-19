#include<stdio.h>
int main(){
    int i,j,k;
    printf("Enter value of i,j & k \n");
    scanf("%d %d %d",&i,&j,&k);
    if (i < j) {
    if (j < k)
        i = j;
}
else {
    j = k;

    if (j > k)
        j = i;
    else
        i = k;
}

printf("%d %d %d\n", i, j, k);
    return 0;
}