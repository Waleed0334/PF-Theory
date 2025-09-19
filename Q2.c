#include<stdio.h>
int main () {
    int x , y;
    printf("Enter value of x ");
    scanf("%d",&x);
    printf("Enter value of y ");
    scanf("%d",&y);
    if (x>0 && y>0)
    {
        printf("The point (%d, %d) lies in quadrant I", x, y);
    } else if (x<0 && y>0)
    {
                printf("The point (%d, %d) lies in quadrant II", x, y);
    } else if (x<0 && y<0)
    {
                printf("The point (%d, %d) lies in quadrant III", x, y);
    } else if (x>0 && y<0)
    {
                printf("The point (%d, %d) lies in quadrant IV", x, y);
    }else{ 
                printf("The point (%d, %d) lies on axis", x, y);
    }
    return 0;
}
