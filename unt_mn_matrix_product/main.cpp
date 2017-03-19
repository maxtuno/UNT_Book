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
#include <fstream>
#include <random>

#include <boost/progress.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <boost/multiprecision/tommath.hpp>

namespace mp = boost::multiprecision;

namespace ublas = boost::numeric::ublas;

typedef boost::multiprecision::tom_int universal;

boost::timer timer;

inline std::vector<char> to_binary(universal &universe, size_t width, size_t size) {
    universal bit = universe;
    std::vector<char> bits(width * size);
    for (size_t i = 0; i < width * size; i++) {
        bits[i] = (bit % 2 != 0);
        bit /= 2;
    }
    return bits;
}

inline std::vector<universal> unt_to_mathematics(universal &universe, size_t size, size_t width) {
    std::vector<universal> standard_form;
    auto bits = to_binary(universe, size, width);
    for (size_t i = 0; i < bits.size(); i += width) {
        universal element;
        for (size_t j = 0; j < width; j++) {
            element += bits[j + i] * (universal(1) << j);
        }
        standard_form.push_back(element);
    }
    return standard_form;
}

inline void cout(universal &universe, size_t size_x, size_t size_y, size_t width) {
    std::cout << "[";
    auto i = 0;
    for (universal &item : unt_to_mathematics(universe, size_x * size_y, width)) {
        i++;
        if (i % size_y == 0) { std::cout << item << ", "; }
    }
    std::cout << "]" << std::endl;
}


int main(int argc, char *argv[]) {

    std::ofstream unt("size_vs_unt.txt");
    std::ofstream std("size_vs_std.txt");

    size_t width = static_cast<size_t>(std::atoll(argv[1]));

    bool log = std::string(argv[3]).compare("log") == 0;

    for (size_t size_x = 2; size_x < static_cast<size_t>(std::atoll(argv[2])); size_x++) {
        size_t size_y = size_x;

        //size_t size_x = static_cast<size_t>(std::atoll(argv[2]));
        //size_t size_y = static_cast<size_t>(std::atoll(argv[3]));

        auto a = ublas::matrix<universal>(size_x, size_y);
        auto b = ublas::matrix<universal>(size_y, size_x);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, (1 << (width - 1)) - 1);

        for (size_t i = 0; i < size_x; i++) {
            for (size_t j = 0; j < size_y; j++) {
                a(i, j) = distribution(generator);
                b(j, i) = distribution(generator);
            }
        }

        std::vector<universal> xx;
        universal y;
        size_t k = 0;
        for (size_t j = 0; j < size_x; j++) {
            universal x;
            for (size_t i = 0; i < size_y; i++) {
                x |= a(j, i) << (i * (2 * width + 1));
                y |= b(size_y - 1 - i, j) << (k * (2 * width + 1));
                k++;
            }
            xx.push_back(x);
        }

        if (log) {
            std::cout << "\nDATA =============================\n" << std::endl;
            std::cout << a << std::endl;
            std::cout << b << std::endl;
        }

        timer.restart();
        a = ublas::prod(a, b);
        auto elapsed_ublas = timer.elapsed();

        timer.restart();
        for (auto &x : xx) { mp_karatsuba_mul(&x.backend().data(), &y.backend().data(), &x.backend().data()); }
        auto elapsed_unt = timer.elapsed();

        if (log) {
            std::cout << "\nTRADITIONAL MATHEMATIC =============================\n" << std::endl;
            std::cout << a << std::endl;

            std::cout << "\nUNIVERSAL NUMBER THEORY =============================\n" << std::endl;
            for (auto &x : xx) { cout(x, size_x, size_y, 2 * width + 1); }

            std::cout << "\nRESULT =============================\n";
        }

        std::cout << "\nUNT " << elapsed_unt << " (s)" << std::endl;
        std::cout << "uBLAS " << elapsed_ublas << " (s)" << std::endl;

        unt << size_x << " " << elapsed_unt << std::endl;
        std << size_x << " " << elapsed_ublas << std::endl;

        std::cout << "\nUNT is " << elapsed_ublas / elapsed_unt << "X FASTER THAN uBLAS" << std::endl;
    }

    return EXIT_SUCCESS;
}
