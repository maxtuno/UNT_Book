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

#include <ctime>
#include <algorithm>
#include <random>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

#include "peqnp/unt.hpp"

inline void print(std::vector<float> binary) {
    std::cout << "[";
    std::for_each(binary.begin(), binary.end(),
                  [&](auto bits) {
                      std::cout << bits << ", ";
                  });
    std::cout << "]" << std::endl;
}

inline void print(std::vector<integer> binary, float epsilon = 1.0) {
    std::cout << "[";
    std::for_each(binary.begin(), binary.end(),
                  [&](auto bits) {
                      std::cout << integer(bits).convert_to<float>() / epsilon << ", ";
                  });
    std::cout << "]" << std::endl;
}

template<typename U, typename V>
inline void compare(std::vector<U> uu, std::vector<V> vv, size_t size, float epsilon = 1.0) {
    for (size_t idx = 0; idx < size; idx++) {
        if (integer(uu[idx]).convert_to<float>() - vv[idx] * epsilon > 1.0 / epsilon) {
            std::cout << "\nP != NP\n" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {

    size_t bits = 31;

    std::ofstream data_unt("size_vs_unt.txt");
    std::ofstream data_gpu("size_vs_gpu.txt");

    float epsilon = static_cast<float>(1 << (bits - 1));

    for (size_t size = 1; size < std::atoi(argv[1]); size++) {

        unt::matrix uu(bits, size, 1);
        unt::matrix vv(bits, size, 1);

        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_real_distribution<float> ds(0, 1);

        compute::vector<float> vector_a;
        compute::vector<float> vector_b;

        for (size_t idx = 0; idx < size; idx++) {
            float a = ds(eng);
            float b = ds(eng);

            uu.insert(idx, integer(a * epsilon));
            vv.insert(idx, integer(b * epsilon));

            vector_a.push_back(a);
            vector_b.push_back(b);
        }

        compute::vector<float> vector_c(size);

        std::cout << "\nVECTORS:" << std::endl;
        print(uu.to_classical_mathematics(), epsilon);
        print(vv.to_classical_mathematics(), epsilon);

        auto ini_unt = std::clock();
        uu += vv;
        auto end_unt = std::clock();
        auto unt_time = (end_unt - ini_unt) / static_cast<float>(CLOCKS_PER_SEC) * 1000;

        std::cout << "\nUNIVERSAL NUMBER THEORY" << std::endl;
        print(uu.to_classical_mathematics(), epsilon);

        auto ini_gpu = std::clock();
        compute::transform(
                vector_a.begin(),
                vector_a.end(),
                vector_b.begin(),
                vector_c.begin(),
                compute::plus<float>()
        );
        auto end_gpu = std::clock();
        auto gpu_time = (end_gpu - ini_gpu) / static_cast<float>(CLOCKS_PER_SEC) * 1000;

        std::vector<float> gpu_vector;
        compute::copy(vector_c.begin(), vector_c.end(), std::back_inserter(gpu_vector));

        std::cout << "\nGPU" << std::endl;
        print(gpu_vector);

        data_unt << size << " " << unt_time << std::endl;
        data_gpu << size << " " << gpu_time << std::endl;

        compare<integer, float>(uu.to_classical_mathematics(), gpu_vector, size, epsilon);

        std::cout << "\nUNT " << gpu_time / unt_time << "X FASTER THAT THE GPU" << std::endl;

    }

    return EXIT_SUCCESS;
}
