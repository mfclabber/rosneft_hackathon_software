// #ifdef L298_MOTOR_DRIVER
#define RIGHT_MOTOR_BACKWARD 8
#define LEFT_MOTOR_BACKWARD  9
#define RIGHT_MOTOR_FORWARD  7
#define LEFT_MOTOR_FORWARD   5
#define RIGHT_MOTOR_ENABLE 6
#define LEFT_MOTOR_ENABLE 12
// #endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
