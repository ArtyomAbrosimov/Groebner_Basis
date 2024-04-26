#pragma once

#include "polynom.h"
#include <iterator>
#include <vector>

namespace groebner {
    using VectorIndex = size_t;
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

        const Polynomial &operator[](VectorIndex index) const {
            return polynomials_[index];
        }

        Polynomial &operator=(const Polynomial &other) {
            if (this != &other) {
                this = other;
            }
            return *this;
        }

        [[nodiscard]] VectorIndex GetSize() const {
            return polynomials_.size();
        }

        void AddPolynomial(const Polynomial &polynomial) {
            polynomials_.push_back(polynomial);
        }

        void ErasePolynomial(VectorIndex index) {
            polynomials_.erase(polynomials_.begin() + index);
        }

        void ChangePolynomial(VectorIndex index, const Polynomial &polynomial) {
            polynomials_[index] = polynomial;
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

    private:
        void CleanZeros() {
            polynomials_.erase(std::remove_if(polynomials_.begin(), polynomials_.end(),
                                              [](Polynomial &polynomial) { return polynomial.IsZero(); }),
                               polynomials_.end());
        }

        std::vector<Polynomial> polynomials_;
    };
}
