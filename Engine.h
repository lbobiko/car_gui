#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
private:
    bool engineStatus;

public:
    Engine();
    bool getEngineStatus() const;
    void setEngineStatus(bool);

};

#endif // ENGINE_H
