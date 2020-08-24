#pragma once
#include <set>

// use this macro inside class, that inherit several listeners.
// this macro resolves methods overloading for pleasant system usage
#define RESOLVE_LISTENER_MANAGERS(ListenerInterface)\
    using ListenerManager<ListenerInterface>::InvokeListener;\
    using ListenerManager<ListenerInterface>::registerListener;\
    using ListenerManager<ListenerInterface>::unregisterListener;\


// inherit this class for usage
template<class IListener>
class ListenerManager
{
public:
        void registerListener(IListener* listener){
                listeners.insert(listener);
        }

        void unregisterListener(IListener* listener){
                listeners.erase(listener);
        }

protected:

        template<class... FuncArgs, class... InvokeArgs>
        void InvokeListener(void (IListener::* function)(FuncArgs...), InvokeArgs... args){
                for (auto listener : listeners)
                        (listener->*(function))(args...); // yes, it`s magic!
        }

private:
        std::set<IListener*> listeners;
};