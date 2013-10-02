#include "../Signal.h"
#include <iostream>

struct HelloWorld
{
    void operator()() const
    {
        std::cout << "Hello, World!" << std::endl;
    }
};

int main() {
    Signal<void()> sig;

    HelloWorld hello;
    sig.connect(hello);

    sig();

    return 0;
}
