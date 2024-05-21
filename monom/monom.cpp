#include <algorithm>
#include <cassert>
#include "monom.h"

namespace groebner {
    Monomial::Monomial(InitList &&vars) : vars_(std::move(CleanZeros(vars))) {
        assert(ArePositiveIndexes());
        assert(ArePositiveDegrees());
        UpdateMaxIndex();
        UpdateSumOfDegrees();
    }

    Monomial &Monomial::operator*=(const Monomial &other) {
        sum_of_degrees_ += other.sum_of_degrees_;
        for (const auto &[index, degree]: other.vars_) {
            vars_[index] += degree;
            max_index_ = std::max(max_index_, index);
        }
        return *this;
    }

    Monomial &Monomial::operator/=(const Monomial &other) {
        assert(other.IsDivisorOf(*this));
        sum_of_degrees_ -= other.sum_of_degrees_;
        for (const auto &[index, degree]: other.vars_) {
            vars_[index] -= degree;
            if (vars_[index] == 0) {
                vars_.erase(index);
            }
        }
        UpdateMaxIndex();
        return *this;
    }


    Monomial operator*(const Monomial &first, const Monomial &second) {
        Monomial res = first;
        res *= second;
        return res;
    }

    Monomial operator/(const Monomial &first, const Monomial &second) {
        Monomial res = first;
        res /= second;
        return res;
    }

    bool operator==(const Monomial &first, const Monomial &second) {
        for (const auto &[index, degree]: first.vars_) {
            if (degree != second.GetDegree(index)) {
                return false;
            }
        }

        for (const auto &[index, degree]: second.vars_) {
            if (degree != first.GetDegree(index)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Monomial &first, const Monomial &second) {
        return !(first == second);
    }

    std::ostream &operator<<(std::ostream &out, const Monomial &monomial) {
        if (monomial.cbegin() == monomial.cend()) {
            out << "1";
            return out;
        }
        for (auto it = monomial.cbegin(); it != monomial.cend(); ++it) {
            if (it != monomial.cbegin()) {
                out << ' ';
            }
            out << "x" << it->first << "^" << it->second;
        }
        return out;
    }

    Monomial LCM(const Monomial &first, const Monomial &second) {
        Monomial res = first;
        for (auto it = second.cbegin(); it != second.cend(); ++it) {
            Monomial::Index index = it->first;
            res.SetDegree(index, std::max(first.GetDegree(index), second.GetDegree(index)));
        }
        return res;
    }

    Monomial GCD(const Monomial &first, const Monomial &second) {
        Monomial res;
        for (auto it = first.cbegin(); it != first.cend(); ++it) {
            Monomial::Index index = it->first;
            res.SetDegree(index, std::min(first.GetDegree(index), second.GetDegree(index)));
        }
        return res;
    }

    bool Monomial::IsDivisorOf(const Monomial &other) const {
        return std::all_of(vars_.begin(), vars_.end(), [&](const auto &pair) {
            const auto [index, degree] = pair;
            return degree <= other.GetDegree(index);
        });
    }

    Monomial::Index Monomial::GetMaxIndex() const {
        return max_index_;
    }

    Monomial::Degree Monomial::GetSumOfDegrees() const {
        return sum_of_degrees_;
    }

    Monomial::Degree Monomial::GetDegree(Index index) const {
        auto it = vars_.find(index);
        if (it != vars_.end()) {
            return it->second;
        } else {
            return 0;
        }
    }

    void Monomial::SetDegree(Index index, Degree degree) {
        assert(index >= 0);
        assert(degree >= 0);
        max_index_ = std::max(max_index_, index);
        sum_of_degrees_ = sum_of_degrees_ - vars_[index] + degree;
        vars_[index] = degree;
    }

    typename Monomial::InitList::const_iterator Monomial::cbegin() const {
        return vars_.cbegin();
    }

    typename Monomial::InitList::const_iterator Monomial::cend() const {
        return vars_.cend();
    }

    typename Monomial::InitList::const_iterator Monomial::begin() const {
        return vars_.begin();
    }

    typename Monomial::InitList::const_iterator Monomial::end() const {
        return vars_.end();
    }

    Monomial::InitList &Monomial::CleanZeros(InitList &vars) {
        for (auto it = vars.begin(); it != vars.end();) {
            if (it->second == 0) {
                it = vars.erase(it);
            } else {
                ++it;
            }
        }
        return vars;
    }

    void Monomial::UpdateMaxIndex() {
        Index res = -1;
        for (const auto &[index, degree]: vars_) {
            res = std::max(res, index);
        }
        max_index_ = res;
    }

    void Monomial::UpdateSumOfDegrees() {
        Degree res = 0;
        for (const auto &[index, degree]: vars_) {
            res += degree;
        }
        sum_of_degrees_ = res;
    }

    bool Monomial::ArePositiveIndexes() {
        return std::all_of(vars_.begin(), vars_.end(), [](const auto &pair) {
            return pair.first >= 0;
        });
    }

    bool Monomial::ArePositiveDegrees() {
        return std::all_of(vars_.begin(), vars_.end(), [](const auto &pair) {
            return pair.second >= 0;
        });
    }
}
