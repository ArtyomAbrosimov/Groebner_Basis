#pragma once

#include <iterator>
#include <vector>
#include "polynom.h"

namespace groebner {
    template<typename T, typename TOrder>
    class SetOfPolynomials {
    public:
        using Polynomial = Polynomial<T, TOrder>;
        using PolynomList = std::vector<Polynomial>;

        SetOfPolynomials() = default;

        explicit SetOfPolynomials(PolynomList &&polynomials) : polynomials_(std::move(CleanZeros(polynomials))) {}

        friend std::ostream &operator<<(std::ostream &out, const SetOfPolynomials &set_of_polynomials) {
            for (auto it = set_of_polynomials.cbegin(); it != set_of_polynomials.cend(); ++it) {
                out << *it << "; ";
            }
            return out;
        }

        const Polynomial &operator[](size_t index) const {
            return polynomials_[index];
        }

        Polynomial &operator[](size_t index) {
            return polynomials_[index];
        }

        [[nodiscard]] size_t GetSize() const {
            return polynomials_.size();
        }

        void AddPolynomial(const Polynomial &polynomial) {
            if (!polynomial.IsZero()) {
                polynomials_.push_back(polynomial);
            }
        }

        void AddPolynomial(Polynomial &&polynomial) {
            if (!polynomial.IsZero()) {
                polynomials_.push_back(std::move(polynomial));
            }
        }

        void ErasePolynomial(size_t index) {
            polynomials_.erase(polynomials_.begin() + index);
        }

        typename PolynomList::const_iterator cbegin() const {
            return polynomials_.cbegin();
        }

        typename PolynomList::const_iterator cend() const {
            return polynomials_.cend();
        }

        typename PolynomList::const_iterator begin() const {
            return polynomials_.begin();
        }

        typename PolynomList::const_iterator end() const {
            return polynomials_.end();
        }

    private:
        PolynomList &CleanZeros(PolynomList &polynomials) {
            polynomials.erase(std::remove_if(polynomials.begin(), polynomials.end(),
                                             [](Polynomial &polynomial) { return polynomial.IsZero(); }),
                              polynomials.end());
            return polynomials;
        }

        PolynomList polynomials_;
    };
}
