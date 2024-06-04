#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


Model::Model() : modelListener(0), startTime(std::chrono::high_resolution_clock::now()), tickCounter(0)
{

}

void Model::tick() {
    #ifdef SIMULATOR
    tickCounter++;

    auto now = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedSeconds = now - startTime;

    if (elapsedSeconds.count() >= 1.0) {  // Check every second
        touchgfx_printf("Tick function is called %d times per second\n", tickCounter);
        tickCounter = 0;  // Reset the counter
        startTime = now;  // Reset the timer
    }

    #endif
}

