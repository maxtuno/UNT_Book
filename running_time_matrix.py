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

import random
import time

import matplotlib.pyplot as plt
import numpy


class UNTMatrixAddition:
    def __init__(self, bits, size):
        self.universe = 0
        self.bits = bits
        self.size = size

    def __str__(self):
        items = []
        ds = bin(self.universe)[2:]
        ds = (self.bits * self.size - len(ds)) * '0' + ds
        for idx in range(0, len(ds), self.bits):
            items += [ds[idx:idx + self.bits]]
        return '[{}]'.format(', '.join([str(int(element, 2)) for element in items[::-1]]))

    def __add__(self, other):
        self.universe += other.universe
        return self

    def insert(self, idx, element):
        self.universe |= (element << (idx * self.bits))


def running_time():
    sizes, unt_times, traditional_mathematics_times = [], [], []
    for bits in [8, 16, 32, 60]:
        for m in range(1, 100):
            for n in range(m, 100):

                sizes.append(bits * m * n)

                aa = [random.randint(0, 2 ** (bits - 1) - 1) for _ in range(m * n)]
                bb = [random.randint(0, 2 ** (bits - 1) - 1) for _ in range(m * n)]

                unt_aa = UNTMatrixAddition(bits, m * n)
                unt_bb = UNTMatrixAddition(bits, m * n)
                for idx, (a, b) in enumerate(zip(aa, bb)):
                    unt_aa.insert(idx, a)
                    unt_bb.insert(idx, b)

                ini = time.time()
                unt_cc = unt_aa + unt_bb
                end = time.time()
                unt_times.append(end - ini)

                aa = numpy.array(aa).reshape((m, n))
                bb = numpy.array(bb).reshape((m, n))

                ini = time.time()
                cc = aa + bb
                end = time.time()
                traditional_mathematics_times.append(end - ini)

                if eval(str(unt_cc)) != cc.reshape(m * n).tolist():
                    raise Exception('P != NP')

    unts = sorted(zip(sizes, unt_times), key=lambda k: k[0])
    trad = sorted(zip(sizes, traditional_mathematics_times), key=lambda k: k[0])

    unts_sizes, unts_times = zip(*unts)
    trad_sizes, trad_times = zip(*trad)

    plt.title('Matrix Addition:\nUNT(r) v/s Traditional Mathematics(b)')
    plt.plot(unts_sizes, unts_times, 'r-', alpha=0.5)
    plt.plot(trad_sizes, trad_times, 'b-', alpha=0.5)
    plt.savefig('unt_matrix_addition_running_time.png')


running_time()
