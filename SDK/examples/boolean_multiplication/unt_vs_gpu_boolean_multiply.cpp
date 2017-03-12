/*
            copyright (cc) 2012-2017 Oscar Riveros. all rights reserved.
                                oscar.riveros@peqnp.com

        without any restriction, Oscar Riveros reserved rights, patents and
        commercialization of this knowledge or derived directly from this work.

    http://twitter.com/maxtuno
    http://klout.com/maxtuno
    http://independent.academia.edu/oarr

    https://www.academia.edu/31770840/Elements_Of_Universal_Number_Theory
    https://github.com/maxtuno/UNT_Book
*/

#include <ctime>
#include <algorithm>
#include <random>
#include <fstream>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

#include "peqnp/unt.hpp"

template<typename T>
inline void print(std::vector<T> binary) {
    std::cout << "[";
    std::for_each(binary.begin(), binary.end(),
                  [&](auto bits) {
                      std::cout << bits << ", ";
                  });
    std::cout << "]" << std::endl;
}

template<typename U, typename V>
inline void compare(std::vector<U> uu, std::vector<V> vv, size_t size) {
    for (size_t idx = 0; idx < size; idx++) {
        if (uu[idx] != vv[idx]) {
            std::cout << "\nP != NP\n" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {

    std::ofstream data_unt("gpu_vs_unt.txt");

    compute::vector<int> aa, bb, cc;

    for (size_t size = 1; size < 250; size++) {

        unt::matrix uu(2, size, 1);
        unt::matrix vv(2, size, 1);

        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> ds(0, 1);

        aa.clear();
        bb.clear();

        for (size_t idx = 0; idx < size; idx++) {
            auto a = ds(eng);
            auto b = ds(eng);
            uu.insert(idx, a);
            vv.insert(idx, b);
            aa.push_back(a);
            bb.push_back(b);
        }

        std::cout << "\nVECTORS:" << std::endl;
        print(uu.to_classical_mathematics());
        print(vv.to_classical_mathematics());

        auto ini_unt = std::clock();
        uu &= vv;
        auto end_unt = std::clock();
        auto unt_time = (end_unt - ini_unt) / static_cast<float>(CLOCKS_PER_SEC) * 1000;

        std::cout << "\nUNIVERSAL NUMBER THEORY" << std::endl;
        print(uu.to_classical_mathematics());

        cc.clear();
        cc.resize(size);

        auto ini_gpu = std::clock();
        compute::transform(
                aa.begin(),
                aa.end(),
                bb.begin(),
                cc.begin(),
                compute::multiplies<int>()
        );
        auto end_gpu = std::clock();
        auto gpu_time = (end_gpu - ini_gpu) / static_cast<float>(CLOCKS_PER_SEC) * 1000;

        std::vector<int> gpu_vector;
        compute::copy(cc.begin(), cc.end(), std::back_inserter(gpu_vector));

        std::cout << "\nGPU" << std::endl;
        print(gpu_vector);

        data_unt << size << " " << gpu_time / unt_time << std::endl;

        compare<integer, int>(uu.to_classical_mathematics(), gpu_vector, size);

        std::cout << "\nUNT " << gpu_time / unt_time << "X FASTER THAT THE GPU" << std::endl;
    }

    return EXIT_SUCCESS;
}