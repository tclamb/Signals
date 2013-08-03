=Signals=
A "lightweight" C++11 implementation of most of Boost.Signal2's interface.

==Example Usage==
===Hello World===
```cpp
// Create a signal accepting void(void) function objects
Signal<void()> simpleSignal;

// Create a function object to output "Hello, World!"
auto helloWorld = []() { std::cout << "Hello, World!" << std::endl; };

// Connect helloWorld to simpleSignal
simpleSignal.connect(helloWorld);

// Call all function objects attached to simpleSignal
simpleSignal();
```

===Call Groups===
```cpp
// Create a signal accepting void(void) function objects
Signal<void()> simpleSignal;

// Add some function objects "out of order"
simpleSignal.connect([]() { std::cout << "... and good morning!" << std::endl; });
simpleSignal.connect(1, []() { std::cout << ", World!" << std::endl; });
simpleSignal.connect(0, []() { std::cout << "Hello"; });

// Call all function objects attached to simpleSignal
// Output is in the correct order!
simpleSignal();
```

===Return Values===
```cpp
// Create a signal accepting float(float, float) function objects
Signal<float(float, float)> mathSignal;

// Add some function objects
mathSignal.connect([](float x, float y) { return x + y; });
mathSignal.connect([](float x, float y) { return x - y; });
mathSignal.connect([](float x, float y) { return x / y; });
mathSignal.connect([](float x, float y) { return x * y; });

// Output the result of the last connected function object
std::cout << 2.0f << '*' << '5.0f' << '=' << mathSignal(2.0f, 5.0f) << std::endl;
```
