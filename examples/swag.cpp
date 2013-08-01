#include "../Signal.hpp"
#include <iostream>

int main() {
    Signal<int()> mySignal;

    std::cout << mySignal() << std::endl;

    mySignal.connect([]() { return 1; });
    mySignal.connect([]() { return 2; });

    std::cout << mySignal() << std::endl;

    /* Output:
     *     0
     *     2
     */

    return 0;
}
