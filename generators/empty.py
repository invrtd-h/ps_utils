if __name__ == '__main__':
    lis = [1] * 1001
    lis[0] = 0
    lis[1] = 0
    for i in range(2, 1001):
        for j in range(i, 1001):
            if i * j >= 1001:
                break
            lis[i * j] = 0
    ret = [i for i in range(1001) if lis[i] == 1]
    print(ret)