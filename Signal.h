#ifndef Signals_Signal_hpp
#define Signals_Signal_hpp

#include <functional>
#include <type_traits>
#include <vector>
#include <map>

template<typename T> class Signal {};

enum class SlotLocation
{
    Front,
    Back
};

template<typename ReturnType, typename... ArgTypes>
class Signal<ReturnType(ArgTypes...)>
{
public:
    typedef std::function<ReturnType(ArgTypes...)> FunctionType;

    void connect(FunctionType f, SlotLocation location = SlotLocation::Back)
    {
        if(location == SlotLocation::Front) {
            frontSlots.push_back(f);
        } else if(location == SlotLocation::Back) {
            backSlots.push_back(f);
        }
    };

    void connect(int group, FunctionType f)
    {
        groupedSlots[group].push_back(f);
    };

    template<typename = typename std::enable_if<std::is_void<ReturnType>::value>::type>
    void operator()(ArgTypes&&... args) const
    {
        for(auto const& f : frontSlots) {
            f(std::forward<ArgTypes>(args)...);
        }

        for(auto const& v : groupedSlots) {
            for(auto const& f : v.second) {
                f(std::forward<ArgTypes>(args)...);
            }
        }

        for(auto const& f : backSlots) {
            f(std::forward<ArgTypes>(args)...);
        }
    };

    template<typename RetType = typename std::enable_if<!std::is_void<ReturnType>::value, ReturnType>::type>
    RetType operator()(ArgTypes&&... args) const
    {
        auto last = RetType{};

        for(auto const& f : frontSlots) {
            last = f(std::forward<ArgTypes>(args)...);
        }

        for(auto const& v : groupedSlots) {
            for(auto const& f : v.second) {
                last = f(std::forward<ArgTypes>(args)...);
            }
        }

        for(auto const& f : backSlots) {
            last = f(std::forward<ArgTypes>(args)...);
        }

        return last;
    };

private:
    std::vector<FunctionType> frontSlots;
    std::map<int, std::vector<FunctionType>> groupedSlots;
    std::vector<FunctionType> backSlots;
};

#endif
