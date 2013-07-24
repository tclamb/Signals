=Signals=
A "lightweight" C++11 implementation of most of Boost.Signal2's interface.

==Example Usage==
===Hello World===
```cpp
// Create a signal accepting void(void) function objects
signal<void()> simpleSignal;

// Create a function object to output "Hello, World!"
auto helloWorld = []() { std::cout << "Hello, World!" << std::endl; };

// Connect helloWorld to simpleSignal
simpleSignal.connect(helloWorld);

// Call all function objects attached to simpleSignal
simpleSignal();
```
