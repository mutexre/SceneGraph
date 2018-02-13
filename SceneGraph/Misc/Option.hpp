//
//  Created by mutexre on 09/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <functional>

template <typename T>
class Option
{
public:
    bool defined;
    T value;

    Option() : defined(false)
    {}

    Option(const T& val) : defined(true), value(val)
    {}

    Option(T&& val) : defined(true), value(move(val))
    {}

    void define(const T& value) {
        defined = true;
        this->value = value;
    }

    void define(T&& value) {
        defined = true;
        this->value = move(value);
    }

    void undefine() {
        defined = false;
    }

    const T& get() const {
        return value;
    }

    T& get() {
        return value;
    }

    const T* operator->() const {
        return &value;
    }

    T* operator->() {
        return &value;
    }

    bool operator==(const Option<T>& o) const
    {
        if (defined == o.defined) {
            if (defined)
                return value == o.value;
            else
                return true;
        }

        return false;
    }

    bool operator!=(const Option<T>& o) const {
        return !operator==(o);
    }

    operator bool() const {
        return defined;
    }
    
    Option<T>& operator=(const T& x) {
        define(x);
        return *this;
    }
    
    Option<T>& operator=(T&& x) {
        define(move(x));
        return *this;
    }
};
