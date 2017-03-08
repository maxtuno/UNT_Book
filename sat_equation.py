"""
        copyright (c) 2012-2017 Oscar Riveros. all rights reserved.
                           oscar.riveros@peqnp.com

    without any restriction, Oscar Riveros reserved rights, patents and
  commercialization of this knowledge or derived directly from this work.

http://twitter.com/maxtuno
http://klout.com/maxtuno
http://independent.academia.edu/oarr
"""

import string

import sage.logic.propcalc as propcalc


def bits(n, p):
    s = []
    while n:
        s = [n % 2 == 0] + s
        n //= 2
    s = (p - len(s)) * [True] + s
    return s


def sat_equation(cnf, n, m):
    sat = 0
    for j in range(m):
        v = 0
        for i in range(n):
            v += int(cnf[j][n - 1 - i] > 0) * (1 << i)
        sat += (1 << v)
    return sat


def encode(s):
    s.convert_cnf()
    cnf = str(s).replace('~', '-').replace('|', ',').replace('&', ',')
    for idx, c in enumerate(string.lowercase):
        cnf = cnf.replace(c, str(idx + 1))
    cnf = eval('[{}]'.format(cnf))
    return cnf


def example_a():
    s = propcalc.formula("a&b|~(c|a)")
    return '{}\n{}'.format(s, s.truthtable())


def example_a_unt():
    cnf = encode(propcalc.formula("a&b|~(c|a)"))

    n = len(cnf[0])
    m = len(cnf)

    return '{}\n{}'.format(cnf, ''.join('{}'.format(bits(sat_equation(cnf, n, m), (1 << n))).replace('[', '').replace(']', '')))


def example_b():
    s = propcalc.formula("(a&b|(c|a))->d")
    return '{}\n{}'.format(s, s.truthtable())


def example_b_unt():
    cnf = encode(propcalc.formula("(a&b|(c|a))->d"))

    n = len(cnf[0])
    m = len(cnf)

    return '{}\n{}'.format(cnf, ''.join('{}'.format(bits(sat_equation(cnf, n, m), (1 << n))).replace('[', '').replace(']', '')))


def example_c():
    s = propcalc.formula("a&b|~(c|a)->d&e")
    return '{}\n{}'.format(s, s.truthtable())


def example_c_unt():
    cnf = encode(propcalc.formula("a&b|~(c|a)->d&e"))

    n = len(cnf[0])
    m = len(cnf)

    return '{}\n{}'.format(cnf, ''.join('{}'.format(bits(sat_equation(cnf, n, m), (1 << n))).replace('[', '').replace(']', '')))
