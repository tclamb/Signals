#include "../Signal.h"
#include <iostream>

int main()
{
    Signal<void()> simpleSignal;

    auto hello = []() { std::cout << "Hello" << std::endl; };
    auto world = []() { std::cout << "World" << std::endl; };

    simpleSignal.connect(hello);
    simpleSignal.connect(world);

    simpleSignal();

    /* Output:
     *    hello
     *    world
     */

    return 0;
}
