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


class UNTMatrix:
    def __init__(self, bits, size):
        self.universe = 0
        self.bits = bits
        self.size = size

    def __str__(self):
        return '[' + ', '.join([str(int(item, 2)) for item in self.slice()[::-1]]) + ']'

    def __add__(self, other):
        self.universe += other.universe
        return self

    def slice(self):
        l, items = bin(self.universe)[2:], []
        l = (self.bits * self.size - len(l)) * '0' + l
        for i in range(0, len(l), self.bits):
            items += [l[i:i + self.bits]]
        return items

    def insert(self, idx, item):
        self.universe |= (item << (idx * self.bits))


if __name__ == '__main__':

    import time

    import numpy
    import pyopencl as cl
    import pyopencl.array as cl_array

    import matplotlib.pyplot as plt

    bits = 16

    sizes, unt_times, gpu_times = [], [], []
    for size in range(1, 2000):

        sizes.append(size)

        # print(80 * '-')

        a = numpy.random.randint(1, 2 ** (bits - 1) - 1, size=size).astype(numpy.int)
        b = numpy.random.randint(1, 2 ** (bits - 1) - 1, size=size).astype(numpy.int)

        # print(a)
        # print(b)

        # print(80 * '-')

        la_aa = UNTMatrix(bits, size)
        for idx, item in enumerate(a.tolist()):
            la_aa.insert(idx, item)
        # print('UNT => {}'.format(la_aa.universe))

        la_bb = UNTMatrix(bits, size)
        for idx, item in enumerate(b.tolist()):
            la_bb.insert(idx, item)
        # print('UNT => {}'.format(la_bb.universe))

        ini = time.time()
        la_aa += la_bb
        end = time.time()
        # print('UNT (RESULT) => {}\n'.format(la_aa.universe))
        # print('\nUNT time {} (s)'.format(end - ini))
        # print(la_aa)

        unt_time = end - ini
        unt_times.append(unt_time)

        # print(80 * '-')

        platform = cl.get_platforms()
        gpu_devices = platform[0].get_devices(device_type=cl.device_type.GPU)
        ctx = cl.Context(devices=gpu_devices)
        queue = cl.CommandQueue(ctx)

        # print(ctx)

        a_dev = cl_array.to_device(queue, a)
        b_dev = cl_array.to_device(queue, b)
        dest_dev = cl_array.empty_like(a_dev)

        prg = cl.Program(ctx, """
            __kernel void sum(__global const int *a, __global const int *b, __global int *c)
            {
              int gid = get_global_id(0);
              c[gid] = a[gid] + b[gid];
            }
            """).build()

        ini = time.time()
        prg.sum(queue, (2 * size,), None, a_dev.data, b_dev.data, dest_dev.data)
        result = dest_dev.get()
        end = time.time()
        # print('\nGPU (RESULT) => {}'.format(dest_dev.get()))
        # print('GPU time {} (s)\n'.format(end - ini))

        gpu_time = end - ini
        gpu_times.append(gpu_time)

        # print(80 * '-')

        # print('TIME: GPU / UNT = {}'.format(gpu_time / unt_time))

        if eval(str(la_aa)) != result.tolist():
            raise Exception('P != NP')

    plt.title('Vector Addition:\nUNT(r) v/s GPU(b)')
    plt.plot(sizes, unt_times, 'r-', alpha=0.5)
    plt.plot(sizes, gpu_times, 'b-', alpha=0.5)
    plt.savefig('unt_matrix_addition_running_time_gpu.png')
