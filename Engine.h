#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
private:
    bool engineStatus;

public:
    Engine();
    bool getEngineStatus();
    void setEngineStatus(bool);

};

#endif // ENGINE_H
