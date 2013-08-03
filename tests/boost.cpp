#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Signal.hpp"

#include <sstream>

namespace
{
    struct HelloWorld
    {
        std::ostream& out;

        void operator()() const
        {
            out << "Hello, World!\n";
        }
    };
}

TEST_CASE("boost/1", "Boost Example 1: Hello World!")
{
    std::stringstream out;

    Signal<void()> sig;

    HelloWorld hello{out};
    sig.connect(hello);

    sig();

    CHECK(out.str() == "Hello, World!\n");
}

namespace
{
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
}

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
namespace
{
    struct GoodMorning
    {
        std::ostream& out;

        void operator()() const
        {
            out << "... and good morning!\n";
        }
    };
}

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

namespace
{
    namespace BoostExampleFour
    {
        static std::stringstream out;

        static void print_args(float x, float y)
        {
            out << "The arguments are " << x << " and " << y << '\n';
        };

        static void print_sum(float x, float y)
        {
            out << "The sum is " << x + y << '\n';
        };

        static void print_product(float x, float y)
        {
            out << "The product is " << x * y << '\n';
        };

        static void print_difference(float x, float y)
        {
            out << "The difference is " << x - y << '\n';
        };

        static void print_quotient(float x, float y)
        {
            out << "The quotient is " << x / y << '\n';
        };
    }
}

TEST_CASE("boost/4", "Boost Example 4: Slot Arguments")
{
    using namespace BoostExampleFour;

    Signal<void(float, float)> sig;

    sig.connect(&print_args);
    sig.connect(&print_sum);
    sig.connect(&print_product);
    sig.connect(&print_difference);
    sig.connect(&print_quotient);

    sig(5., 3.);

    CHECK(out.str() == "The arguments are 5 and 3\nThe sum is 8\n"
            "The product is 15\nThe difference is 2\n"
            "The quotient is 1.66667\n");
}

/* TODO: Custom Combiners */
namespace
{
    namespace BoostExampleFive
    {
        static std::stringstream out;

        static float product(float x, float y) { return x * y; };
        static float quotient(float x, float y) { return x / y; };
        static float sum(float x, float y) { return x + y; };
        static float difference(float x, float y) { return x - y; };
    }
}

TEST_CASE("boost/5", "Boost Example 5: Signal Return Values")
{
    using namespace BoostExampleFive;

    Signal<float(float, float)> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    CHECK(sig(5, 3) == 5. - 3.);
}

