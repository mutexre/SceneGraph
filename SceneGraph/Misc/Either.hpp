//
//  Created by mutexre on 13/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

template <class A, class B>
class Either
{
public:
    using State = unsigned char;

public:
    class StateIsNotDefined : exception
    {
    public:
        virtual const char* what() const throw() {
            return "state is undefined (neither A nor B)";
        }
    };

    class ValueIsNotDefined : exception
    {
    protected:
        State state;

    public:
        ValueIsNotDefined(State state) {
            this->state = state;
        }

        virtual const char* what() const throw() {
            return state == 0 ? "member of type B is not defined" : "member of type A is not defined";
        }
    };

public:
    Option<State> state;
    A a;
    B b;

    Either() {}

    Either(A a) {
        state.define(0);
        this->a = a;
    }

    Either(B b) {
        state.define(1);
        this->b = b;
    }

    A getA() const {
        if (!state.defined) throw StateIsNotDefined();
        if (state.get() == 1) throw ValueIsNotDefined(state.get());
        return a;
    }

    B getB() const {
        if (!state.defined) throw StateIsNotDefined();
        if (state.get() == 0) throw ValueIsNotDefined(state.get());
        return b;
    }

    void setA(const A& a) {
        this->a = a;
    }

    void setB(const B& b) {
        this->b = b;
    }

    State toggle() {
        state = !state;
    }
};
