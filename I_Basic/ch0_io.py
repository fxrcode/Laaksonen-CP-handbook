import sys

input = sys.stdin.readline


############ ---- Input Functions ---- ############
# https://codeforces.com/blog/entry/71884


def inp():
    return int(input())


def invr():
    return map(float, input().strip().split())


def insr():
    return input().strip()


def io_eg():
    # how to read input, check Durr book Chap 1.3 input-output
    # p = insr()
    # print(f"{p=}, {type(p)=}")
    a, b, c = invr()
    print(a, b, c)
