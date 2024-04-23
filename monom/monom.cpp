#include "monom.h"

namespace groebner {
    Monomial::Monomial(std::unordered_map<Index, Degree> &&vars) {
        for (auto &[index, degree]: vars) {
            assert(index >= 0);
        }
        vars_ = std::move(vars);
        CleanZeros();
        UpdateMaxIndex();
        UpdateSumOfDegrees();
    }

    Monomial Monomial::operator*=(const Monomial &other) {
        for (auto &[index, degree]: other.vars_) {
            vars_[index] += degree;
        }
        UpdateMaxIndex();
        UpdateSumOfDegrees();
        return *this;
    }

    Monomial Monomial::operator/=(const Monomial &other) {
        assert(other.Divides(*this));
        for (auto &[index, degree]: other.vars_) {
            vars_[index] -= degree;
            assert(vars_[index] >= 0);
        }
        CleanZeros();
        UpdateMaxIndex();
        UpdateSumOfDegrees();
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
        for (auto &[index, degree]: first.vars_) {
            if (degree != second.GetDegree(index)) {
                return false;
            }
        }
        return std::all_of(second.vars_.begin(), second.vars_.end(), [&](const auto &pair) {
            const auto [index, degree] = pair;
            return degree == first.GetDegree(index);
        });
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
            Index index = it->first;
            res.SetDegree(index, std::max(first.GetDegree(index), second.GetDegree(index)));
        }
        return res;
    }

    Monomial GCD(const Monomial &first, const Monomial &second) {
        Monomial res;
        for (auto it = first.cbegin(); it != first.cend(); ++it) {
            Index index = it->first;
            res.SetDegree(index, std::min(first.GetDegree(index), second.GetDegree(index)));
        }
        return res;
    }

    bool Monomial::Divides(const Monomial &other) const {
        return std::all_of(vars_.begin(), vars_.end(), [&](const auto &pair) {
            const auto [index, degree] = pair;
            return degree <= other.GetDegree(index);
        });
    }

    Index Monomial::GetMaxIndex() const {
        return max_index_;
    }

    Degree Monomial::GetSumOfDegrees() const {
        return sum_of_degrees_;
    }

    Degree Monomial::GetDegree(Index index) const {
        auto it = vars_.find(index);
        if (it != vars_.end()) {
            return it->second;
        } else {
            return 0;
        }
    }

    void Monomial::SetDegree(Index index, Degree degree) {
        max_index_ = std::max(max_index_, index);
        sum_of_degrees_ = sum_of_degrees_ - vars_[index] + degree;
        vars_[index] = degree;
    }

    typename std::unordered_map<Index, Degree>::const_iterator Monomial::cbegin() const {
        return vars_.cbegin();
    }

    typename std::unordered_map<Index, Degree>::const_iterator Monomial::cend() const {
        return vars_.cend();
    }

    void Monomial::CleanZeros() {
        for (auto it = vars_.begin(); it != vars_.end();) {
            if (it->second == 0) {
                it = vars_.erase(it);
            } else {
                ++it;
            }
        }
    }

    void Monomial::UpdateMaxIndex() {
        Index res = -1;
        for (auto &[index, degree]: vars_) {
            res = std::max(res, index);
        }
        max_index_ = res;
    }

    void Monomial::UpdateSumOfDegrees() {
        Degree res = 0;
        for (auto &[index, degree]: vars_) {
            res += degree;
        }
        sum_of_degrees_ = res;
    }
}
