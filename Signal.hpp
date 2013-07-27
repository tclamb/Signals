#ifndef Signals_Signal_hpp
#define Signals_Signal_hpp

#include <functional>
#include <vector>

template<typename T> class Signal {};

template<typename ReturnType, typename... ArgTypes>
class Signal<ReturnType(ArgTypes...)>
{
public:
    typedef std::function<ReturnType(ArgTypes...)> FunctionType;

    void connect(FunctionType f);

    ReturnType operator()(ArgTypes...) const;

private:
    std::vector<FunctionType> slots;
};

template<typename ReturnType, typename... ArgTypes>
void Signal<ReturnType(ArgTypes...)>::connect(FunctionType f)
{
    slots.push_back(f);
}

template<typename ReturnType, typename... ArgTypes>
ReturnType Signal<ReturnType(ArgTypes...)>::operator()(ArgTypes... args) const
{
    ReturnType result = {};
    for(auto const& f : slots)
        result = f(std::forward<ArgTypes...>(args)...);
    return result;
}

// gotta partially specialize for void functions :(

template<typename... ArgTypes>
class Signal<void(ArgTypes...)>
{
public:
    typedef std::function<void(ArgTypes...)> FunctionType;
    void connect(FunctionType f);
    void operator()(ArgTypes...) const;
private:
    std::vector<FunctionType> slots;
};

template<typename... ArgTypes>
void Signal<void(ArgTypes...)>::connect(FunctionType f)
{
    slots.push_back(f);
}

template<typename... ArgTypes>
void Signal<void(ArgTypes...)>::operator()(ArgTypes... args) const
{
    for(auto const& f : slots)
        f(std::forward<ArgTypes...>(args)...);
}

#endif
