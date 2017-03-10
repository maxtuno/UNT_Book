/*
            copyright (c) 2012-2017 Oscar Riveros. all rights reserved.
                                oscar.riveros@peqnp.com

        without any restriction, Oscar Riveros reserved rights, patents and
        commercialization of this knowledge or derived directly from this work.

    http://twitter.com/maxtuno
    http://klout.com/maxtuno
    http://independent.academia.edu/oarr

    https://www.academia.edu/31770840/Elements_Of_Universal_Number_Theory
    https://github.com/maxtuno/UNT_Book
*/

#ifndef PEQNP_UNT_HPP
#define PEQNP_UNT_HPP

#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int integer;


namespace unt {
    class matrix {
    public:
        matrix(size_t bits, size_t n, size_t m, integer universe = 0) : _bits(bits), _n(n), _m(m), universe(universe) {}

        inline void insert(size_t idx, integer element) {
            universe |= (element << (idx * _bits));
        }

        inline matrix operator+=(const matrix& rhs) {
            universe += rhs.universe;
            return *this;
        }

        inline std::vector<bool> binary() {
            integer bit = universe;
            std::vector<bool> bits(_bits *_n *_m);
            for (size_t idx = 0; idx < _bits * _n * _m; idx++) {
                bits[idx] = (bit % 2 != 0);
                bit /= 2;
            }
            return bits;
        }

        inline std::vector<integer> to_classical_mathematics() {
            std::vector<integer> formated;
            auto bits = binary();
            for (size_t idx = 0; idx < bits.size(); idx += _bits) {
                integer element = 0;
                for (size_t jdx = 0; jdx < _bits; jdx++) { element += bits[jdx + idx] * (1 << jdx); }
                formated.push_back(element);
            }
            return formated;
        }

        integer universe = 0;
        
    private:
        size_t _bits;
        size_t _n;
        size_t _m;
    };
}

#endif //PEQNP_UNT_HPP
