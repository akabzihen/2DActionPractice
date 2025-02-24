#pragma once

#include <assert.h>

template<class T>
class Singleton {
public:
    static T* Instance() {
        return dynamic_cast<T*>(instance_);
    };
    Singleton() {
        assert(!instance_);
        instance_ = this;
    };
    virtual ~Singleton() {};

protected:
    static Singleton* instance_;
};

template<class T>
Singleton<T>* Singleton<T>::instance_ = nullptr;