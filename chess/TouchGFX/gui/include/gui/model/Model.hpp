#ifndef MODEL_HPP
#define MODEL_HPP

#include <chrono>
#include <iostream>
#include <touchgfx/utils.hpp>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;

    unsigned int tickCounter;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};

#endif // MODEL_HPP
