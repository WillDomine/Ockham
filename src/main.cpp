#include <iostream>
#include <stdexcept>

#include "core/Engine.h"

int main() {

    //Stack Allocation, because it is faster and when main dies the engine will die.
    Ockham::Engine engine;

    try
    {
        //Runs the engine
        engine.run();
    }
    catch(const std::exception& e)
    {
        //Catchs errors so the application dosen't just vanish without a trace.
        std::cerr << "Fatal Error" << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}