#ifndef Signals_Signal_hpp
#define Signals_Signal_hpp

#include <functional>
#include <vector>
#include <type_traits>

template<typename T> class Signal {};

template<typename ReturnType, typename... ArgTypes>
class Signal<ReturnType(ArgTypes...)>
{
public:
    typedef std::function<ReturnType(ArgTypes...)> FunctionType;

    void connect(FunctionType f) {
        slots.push_back(f);
    };

    template<typename = typename std::enable_if<std::is_void<ReturnType>::value>::type>
    void operator()(ArgTypes... args) const {
        for(auto const& f : slots) {
            f(std::forward<ArgTypes...>(args)...);
        }
    };

    template<typename RetType = typename std::enable_if<!std::is_void<ReturnType>::value, ReturnType>::type>
    RetType operator()(ArgTypes... args) const {
        if(slots.size() == 0)
            return {};
        for(auto f = slots.cbegin();; ++f) {
            if(next(f) == slots.cend())
                return (*f)(std::forward<ArgTypes...>(args)...);
            (*f)(std::forward<ArgTypes...>(args)...);
        }
    };

private:
    std::vector<FunctionType> slots;
};

#endif
