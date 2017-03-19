import pylab

datalist = [(pylab.loadtxt(filename), label) for filename, label in [('size_vs_unt.txt', 'SIZE / UNT (s)'), ('size_vs_std.txt', 'SIZE / STD (s)')]]

for data, label in datalist:
    pylab.plot(data[:, 0], data[:, 1], label=label)

pylab.legend()
pylab.title("UNT (s) v/s STD (s)")
pylab.xlabel("SIZE")
pylab.ylabel("UNT / STD")
pylab.savefig('unt_vs_std.png')
