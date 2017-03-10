import pylab

datalist = [(pylab.loadtxt(filename), label) for filename, label in [('size_vs_unt.txt', 'UNT'), ('size_vs_gpu.txt', 'GPU')]]

for data, label in datalist:
    pylab.plot(data[:, 0], data[:, 1], label=label)

pylab.legend()
pylab.title("UNT v/s GPU")
pylab.xlabel("TIME (s)")
pylab.ylabel("SIZE")
pylab.savefig('unt_vs_gpu.png')
