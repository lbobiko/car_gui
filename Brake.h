#ifndef BRAKE_H
#define BRAKE_H

class Brake
{
private:
    bool brakePressed;

public:
    Brake();
    bool getBrakePressed() const;
    void setBrakePressed(bool);
};

#endif // BRAKE_H
