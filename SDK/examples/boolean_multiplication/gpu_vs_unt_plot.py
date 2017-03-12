import numpy
import pylab

datalist = [(pylab.loadtxt(filename), label) for filename, label in [('gpu_vs_unt.txt', 'X')]]

average = 0
for data, label in datalist:
    pylab.plot(data[1:, 1], data[1:, 0], label=label)
    average = numpy.average(data[1:, 0])

pylab.legend()
pylab.title('UNT {}X FASTER THAT THE GPU'.format(average))
pylab.xlabel("GPU / UNT")
pylab.ylabel("SIZE")
pylab.savefig('gpu_vs_unt.png')
