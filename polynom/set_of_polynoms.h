#pragma once

#include "polynom.h"
#include <iterator>
#include <vector>

namespace groebner {
    template<typename T, typename Order>
    class SetOfPolynomials {
    public:
        using Polynomial = Polynomial<T, Order>;

        SetOfPolynomials() = default;

        explicit SetOfPolynomials(std::vector<Polynomial> &&polynomials) : polynomials_(std::move(polynomials)) {}

        friend std::ostream &operator<<(std::ostream &out, const SetOfPolynomials &set_of_polynomials) {
            for (auto it = set_of_polynomials.cbegin(); it != set_of_polynomials.cend(); ++it) {
                out << *it << "; ";
            }
            return out;
        }

        const Polynomial &operator[](size_t index) const {
            return polynomials_[index];
        }

        [[nodiscard]] size_t GetSize() const {
            return polynomials_.size();
        }

        typename std::vector<Polynomial>::const_iterator cbegin() const {
            return polynomials_.cbegin();
        }

        typename std::vector<Polynomial>::const_iterator cend() const {
            return polynomials_.cend();
        }

        typename std::vector<Polynomial>::const_iterator begin() const {
            return polynomials_.begin();
        }

        typename std::vector<Polynomial>::const_iterator end() const {
            return polynomials_.end();
        }

        void AddPolynomial(const Polynomial &polynomial) {
            polynomials_.push_back(polynomial);
        }

        void CleanZeros() {
            polynomials_.erase(std::remove_if(polynomials_.begin(), polynomials_.end(),
                                              [](Polynomial &polynomial) { return polynomial.IsZero(); }),
                               polynomials_.end());
        }

    private:
        std::vector<Polynomial> polynomials_;
    };
}
