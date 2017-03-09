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

import numpy


class UNTMatrixMultiply:
    def __init__(self, bits, size):
        self.universe = 0
        self.bits = 2 * bits
        self.size = size

    def __str__(self):
        items = []
        ds = bin(self.universe)[2:]
        ds = (self.bits * self.size - len(ds)) * '0' + ds
        for idx in range(0, len(ds), self.bits):
            items += [ds[idx:idx + self.bits]]
        return '[{}]'.format(', '.join([str(int(element, 2)) for element in items[::-1]]))

    def __mul__(self, other):
        self.universe &= other.universe
        return self

    def insert(self, idx, element):
        self.universe |= (element << (idx * self.bits))


def example_a():
    bits = 2
    m, n = 2, 4

    aa = [random.randint(0, 2 ** (bits - 1) - 1) for _ in range(m * n)]
    bb = [random.randint(0, 2 ** (bits - 1) - 1) for _ in range(m * n)]

    out = '{}\n*\n{}\n'.format(numpy.array(aa).reshape((m, n)), numpy.array(bb).reshape((m, n)))

    unt_aa = UNTMatrixMultiply(bits, m * n)
    unt_bb = UNTMatrixMultiply(bits, m * n)
    for idx, (a, b) in enumerate(zip(aa, bb)):
        unt_aa.insert(idx, a)
        unt_bb.insert(idx, b)

    unt_cc = unt_aa * unt_bb

    out += '\nUNT: {}\n{}\n'.format(unt_cc.universe, numpy.array(eval(str(unt_cc))).reshape((m, n)))
    out += '\nTraditional Mathematics:\n{}'.format(numpy.array(aa).reshape((m, n)) * numpy.array(bb).reshape((m, n)))

    return out


def example_b():
    bits = 2
    m, n = 7, 3

    aa = [random.randint(0, 2 ** (bits - 1) - 1) for _ in range(m * n)]
    bb = [random.randint(0, 2 ** (bits - 1) - 1) for _ in range(m * n)]

    out = '{}\n*\n{}\n'.format(numpy.array(aa).reshape((m, n)), numpy.array(bb).reshape((m, n)))

    unt_aa = UNTMatrixMultiply(bits, m * n)
    unt_bb = UNTMatrixMultiply(bits, m * n)
    for idx, (a, b) in enumerate(zip(aa, bb)):
        unt_aa.insert(idx, a)
        unt_bb.insert(idx, b)

    unt_cc = unt_aa * unt_bb

    out += '\nUNT: {}\n{}\n'.format(unt_cc.universe, numpy.array(eval(str(unt_cc))).reshape((m, n)))
    out += '\nTraditional Mathematics:\n{}'.format(numpy.array(aa).reshape((m, n)) * numpy.array(bb).reshape((m, n)))

    return out


print(example_a())
print(example_b())
