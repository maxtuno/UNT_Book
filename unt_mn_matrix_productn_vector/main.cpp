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

#include <iostream>
#include <random>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

namespace ublas = boost::numeric::ublas;

typedef boost::multiprecision::cpp_int universal;

universal zero(0);
universal one(1);
universal two(2);

inline std::vector<char> to_binary(universal &universe, size_t width, size_t size) {
    universal bit = universe;
    std::vector<char> bits(width * size);
    for (size_t i = 0; i < width * size; i++) {
        bits[i] = (bit % two != zero);
        bit /= two;
    }
    return bits;
}

inline std::vector<universal> unt_to_mathematics(universal &universe, size_t size, size_t width) {
    std::vector<universal> standard_form;
    auto bits = to_binary(universe, size, width);
    for (size_t i = 0; i < bits.size(); i += width) {
        universal element;
        for (size_t j = 0; j < width; j++) {
            element += bits[j + i] * (one << j);
        }
        standard_form.push_back(element);
    }
    return standard_form;
}

inline void cout(universal &universe, size_t size_x, size_t width) {
    std::cout << "[";
    auto i = 0;
    for (universal &item : unt_to_mathematics(universe, size_x, width)) {
        i++;
        if (i % size_x == 0) {
            std::cout << item;
        }
    }
    std::cout << "]" << std::endl;
}


int main(int argc, char *argv[]) {

    size_t width = static_cast<size_t>(std::atoll(argv[1]));
    size_t size_x = static_cast<size_t>(std::atoll(argv[2]));

    auto a = ublas::matrix<universal>(size_x, size_x);
    auto b = ublas::matrix<universal>(size_x, 1);

    std::default_random_engine generator(static_cast<unsigned int>(std::time(NULL)));
    std::uniform_int_distribution<int> distribution(0, (1 << (width - 1)) - 1);

    for (size_t i = 0; i < size_x; i++) {
        for (size_t j = 0; j < size_x; j++) {
            a(i, j) = distribution(generator);
        }
        b(i, 0) = distribution(generator);
    }

    std::vector<universal> xx;
    universal y;
    size_t k = 0;
    for (size_t j = 0; j < size_x; j++) {
        universal x;
        for (size_t i = 0; i < size_x; i++) {
            x |= a(j, i) << (i * (2 * width + 1));
            y |= b(size_x - 1 - i, 0) << (k * (2 * width + 1));
            k++;
        }
        xx.push_back(x);
    }

    std::cout << "\nDATA =============================\n" << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << "\nTRADITIONAL MATHEMATIC =============================\n" << std::endl;
    a = ublas::prod(a, b);
    std::cout << a << std::endl;

    std::cout << "\nUNIVERSAL NUMBER THEORY =============================\n" << std::endl;
    for (auto &x : xx) { x *= y; }
    for (auto &x : xx) { cout(x, size_x, 2 * width + 1); }

    return EXIT_SUCCESS;
}
