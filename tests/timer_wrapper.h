#pragma once

#include <ctime>
#include <iostream>
#include <string>

namespace groebner {
    template<typename TFunction>
    class TimerWrapper {
    public:
        TimerWrapper(TFunction function) : call(function), start_(std::clock()) {}

        operator TFunction() {
            return call;
        }

        ~TimerWrapper() {
            const clock_t end = std::clock();
            std::cout << end - start_;
        }

        TFunction call;

    private:
        const clock_t start_;
    };

    template<typename TFunction>
    TimerWrapper<TFunction> TestTime(TFunction function) {
        return TimerWrapper < TFunction > (function);
    }
}
