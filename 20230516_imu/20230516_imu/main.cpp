#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int current = 0;
    int target = 0;
    int error = 0;
    int c_error = 0;

    printf("Input Current Angle = ");
    scanf("%d", &current);
    printf("Input Target Angle = ");
    scanf("%d", &target);

    error = target - current;

    printf("\n\n");
    printf("o. Error  : %d  =  %d  -  %d", error, target, current);


    printf("\n\n");
    if (error < 180 && error >0)
    {
        c_error = target - current;
        printf("c. Error  : %d  =  %d  -  %d", c_error, target, current);
    }
    else if (error > 180)
    {
        c_error = error - 360;
        printf("c. Error  : %d  =  %d  -  %d", c_error, target, current);
    }
    else if (error < 0 && error > -180)
    {
        c_error = error;
        printf("c. Error  : %d  =  %d  -  %d", c_error, target, current);
    }
    else if (error < -90 && error > -360)
    {
        c_error = 360 + error;
        printf("c. Error  : %d  =  %d  -  %d", c_error, target, current);
    }
    else if (error == 0 || error == 360 || error == -360)
    {
        c_error = 0;
        printf("c. Error  : %d  =  %d  -  %d", c_error, target, current);
    }
    else if (error == 180 || error == -180)
    {
        c_error = 180;
        printf("c. Error  : %d  =  %d  -  %d", c_error, target, current);
    }

}