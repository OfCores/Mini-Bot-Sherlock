class MotorControl
{
private:
    public:
    static void setup();
    static void loop();
    
public:
    static void setLeftMotor(int speed);
    static void setRightMotor(int speed);
};

