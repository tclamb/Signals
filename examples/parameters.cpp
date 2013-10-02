#include "../Signal.h"
#include <iostream>

int main() {
    Signal<int(int)> mySignal;

    std::cout << mySignal(30) << std::endl;

    mySignal.connect([](int a) { return a; });
    mySignal.connect([](int a) { std::cout << a << std::endl; return 0; });

    std::cout << mySignal(15) << std::endl;

    /* Output:
     *     0
     *     15
     *     0
     */

    Signal<void(float)> mySignal2;

    mySignal2.connect([](float a) { std::cout << 0 << std::endl; });
    mySignal2.connect([](float a) { std::cout << a << std::endl; });

    mySignal2(15);

    /* Output:
     *     0
     *     15
     */

    return 0;
}
