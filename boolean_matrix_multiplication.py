"""
        copyright (c) 2012-2017 Oscar Riveros. all rights reserved.
                           oscar.riveros@peqnp.com

    without any restriction, Oscar Riveros reserved rights, patents and
  commercialization of this knowledge or derived directly from this work.

http://twitter.com/maxtuno
http://klout.com/maxtuno
http://independent.academia.edu/oarr

https://www.academia.edu/31770840/Elements_Of_Universal_Number_Theory
https://github.com/maxtuno/UNT_Book
"""

# THIS FILE IS A PREVIEW NEEd MORE WORK!!!

import random
import time

import matplotlib.pyplot as plt
import numpy


class UNTMatrix:
    def __init__(self, bits, m, n, universe=0):
        self.universe = universe
        self.bits = bits ** 2
        self.m = m
        self.n = n
        self.beta, self.delta, self.gamma = ((1 << self.bits) - 1), ((1 << (self.bits * self.m)) - 1), self.bits * self.m

    def to_classical_mathematics(self):
        items = []
        ds = bin(self.universe)[2:]
        ds = (self.bits * self.m * self.n - len(ds)) * '0' + ds
        for idx in range(0, len(ds), self.bits):
            items += [ds[idx:idx + self.bits]]        
        out = [int(element, 2) for element in items[::-1]]
        return [sum(out[idx:idx + self.m]) for idx in range(0, len(out), self.m)]

    def __add__(self, other):
        self.universe += other.universe
        return self

    def __mul__(self, other):
        self.universe &= other.universe
        return self

    def insert(self, idx, element):
        self.universe |= (element << (idx * self.bits))


def running_time():

    sizes, unt_times, traditional_mathematics_times = [], [], []

    for n in range(1, 100):
        for m in range(n, 100):
            
            sizes.append(m * n)
            
            if n > m:
                print('SORRY: WORK IN PROGRESS!!!')
                print('m > n')
                exit(1)

            uu = [random.randint(0, 1) for _ in range(m)]
            vv = [random.randint(0, 1) for _ in range(m * n)]

            unt_uu = UNTMatrix(2, m, n)
            for idx, u in enumerate(m * uu):
                unt_uu.insert(idx, u)

            unt_vv = UNTMatrix(2, m, 1)
            for idx, v in enumerate(vv):
                unt_vv.insert(idx, v)

            ini = time.time()
            unt_uu *= unt_vv
            end = time.time()
            unt_times.append(end - ini)

            print('X:\n{}\n\nb:\n{}'.format(numpy.array(vv).reshape((n, m)), numpy.array(uu).reshape((m))))

            print(40 * '-')
            print('UNT:\n{} \ntime {}'.format(unt_uu.to_classical_mathematics(), end - ini))

            print('\n' + 40 * '=')

            ini = time.time()
            c = numpy.matmul(numpy.array(vv).reshape((n, m)), numpy.array(uu).reshape((m)))
            end = time.time()
            traditional_mathematics_times.append(end - ini)
            print('TRADITIONAL MATHEMATICS:\n{}\ntime {}'.format(c, end - ini))

            if unt_uu.to_classical_mathematics()!= c.tolist():
                raise Exception('P != NP')

    unts = sorted(zip(sizes, unt_times), key=lambda k: k[0])
    trad = sorted(zip(sizes, traditional_mathematics_times), key=lambda k: k[0])

    unts_sizes, unts_times = zip(*unts)
    trad_sizes, trad_times = zip(*trad)

    plt.title('Boolean Matrix Multiplication:\nUNT(r) v/s Traditional Mathematics(b)')
    plt.plot(unts_sizes, unts_times, 'r-', alpha=0.5)
    plt.plot(trad_sizes, trad_times, 'b-', alpha=0.5)
    plt.savefig('unt_boolean_matrix_multiplication_running_time.png')

running_time()
