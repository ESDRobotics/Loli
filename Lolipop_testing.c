
#include <Lolipop_header.h>
#include <kipr/botball.h>

///////////////////////////////////////////////////////////////////////////////
//define
///////////////////////////////////////////////////////////////////////////////
#define desired_time = 5000
#define samples = 20


///////////////////////////////////////////////////////////////////////////////
// fucntion definitons
///////////////////////////////////////////////////////////////////////////////
void moveWheels(int wheelPosition);
void driveUpTheRamp();
void twoStepTurn(int speed, int time, int turnDirection, int driveDirection);
void turn(int speed, int time, int direction);
void drive(int speed, int distance, int direction);
void moveServo(int port, int position, int speed);


///////////////////////////////////////////////////////////////////////////////
//main method
///////////////////////////////////////////////////////////////////////////////

int main()
{
    int gyro_values[samples];
    int accel_values[samples];
    int average_accel = 0;
    int average_gyro = 0;
    set_servo_position(raise_robot, low);
    enable_servos();
    moveServo(2, 350, 50);
    drive(100, 30, backward);

    int loop_counter;

    for (loop_counter = 0; loop_counter < samples; loop_counter++) {
      gyro_values[loop_counter] = accel_y();
      accel_values[loop_counter] = gyro_y();
      msleep(desired_time/samples);
    }
    for (size_t i = 0; i < samples; i++) {
      average_gyro=average_gyro+gyro_values[i];
      average_accel=average_accel+gyro_values[i];
    }
    average





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
    return 0;
}
