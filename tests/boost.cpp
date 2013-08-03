#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Signal.hpp"

#include <sstream>

struct HelloWorld
{
    std::ostream& out;

    void operator()() const
    {
        out << "Hello, World!\n";
    }
};

TEST_CASE("boost/1", "Boost Example 1: Hello World!")
{
    std::stringstream out;

    Signal<void()> sig;

    HelloWorld hello{out};
    sig.connect(hello);

    sig();

    CHECK(out.str() == "Hello, World!\n");
}

struct Hello
{
    std::ostream& out;

    void operator()() const
    {
        out << "Hello";
    }
};

struct World
{
    std::ostream& out;

    void operator()() const
    {
        out << ", World!\n";
    }
};

TEST_CASE("boost/2", "Boost Example 2: Connecting Multiple Slots")
{
    std::stringstream out;

    Signal<void()> sig;
    
    sig.connect(Hello{out});
    sig.connect(World{out});

    sig();

    CHECK(out.str() == "Hello, World!\n");
}

#ifdef EXAMPLE3
struct GoodMorning
{
    std::ostream& out;

    void operator()() const
    {
        out << "... and good morning!\n"
    }
};

TEST_CASE("boost/3", "Boost Example 3: Ordering Slot Call Groups")
{
    std::stringstream out;

    Signal<void()> sig;
    
    sig.connect(GoodMorning{out});
    sig.connect(1, World{out});
    sig.connect(0, Hello{out});

    sig();

    CHECK(out.str() == "Hello, World!\n... and good morning!\n");
}
#endif

std::stringstream out4;

void print_args(float x, float y)
{
  out4 << "The arguments are " << x << " and " << y << '\n';
}

void print_sum(float x, float y)
{
  out4 << "The sum is " << x + y << '\n';
}

void print_product(float x, float y)
{
  out4 << "The product is " << x * y << '\n';
}

void print_difference(float x, float y)
{
  out4 << "The difference is " << x - y << '\n';
}

void print_quotient(float x, float y)
{
  out4 << "The quotient is " << x / y << '\n';
}

TEST_CASE("boost/4", "Boost Example 4: Slot Arguments")
{
    Signal<void(float, float)> sig;

    sig.connect(&print_args);
    sig.connect(&print_sum);
    sig.connect(&print_product);
    sig.connect(&print_difference);
    sig.connect(&print_quotient);

    sig(5., 3.);

    CHECK(out4.str() == "The arguments are 5 and 3\nThe sum is 8\n"
                        "The product is 15\nThe difference is 2\n"
                        "The quotient is 1.66667\n");
}
