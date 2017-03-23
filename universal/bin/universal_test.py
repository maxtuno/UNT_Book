if __name__ == '__main__':

    import random
    import subprocess

    for bits in range(1, 100):
        u = random.randint(0, (1 << bits) - 1)
        v = random.randint(0, (1 << bits) - 1)

        out = subprocess.run(['./universal', str(u), str(v)], stdout=subprocess.PIPE).stdout

        print(out)
        print(u + v, u * v)