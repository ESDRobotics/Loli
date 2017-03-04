/*

Author : Nathaniel Mann (except for drive up ramp method)
TO-DO :
        X move the fucntions to a library file




NOTES
      How to //print accel values
        //printf("%i\n",accel_y());
        //printf("%i\n",accel_y());

*/

#include <kipr/botball.h>
#include <Lolipop_Header.h>



///////////////////////////////////////////////////////////////////////////////
//main method
///////////////////////////////////////////////////////////////////////////////

int main()
{

    set_servo_position(raise_robot, low);
    enable_servos();
    moveServo(2, 350, 50);
    moveBasket
    /*
    //drive(100, 30, backward);
    motor (left_motor, -100*l_motor_factor);
    motor (right_motor, -100*r_motor_factor);
msleep(1500);

        set_servo_position(raise_robot, rampPosition);
    msleep(2000);
    driveUpTheRamp();
    drive(75, 5, forward);
    twoStepTurn(75, 860, right, backward);// this is a place that it could go wrong bc I changed it to backward from forward
    // initial two stage turn procedure
    drive(75, 5, forward);
    twoStepTurn(75, 860, right, backward);// this is a place that it could go wrong bc I changed it to backward from forward

    */
    return 0;
}
