import math
import random
import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable 

def read_data(filename):
    x123456x0_list = []
    y_list = []
    file = open(filename)
    lines = file.readlines()
    for line in lines:
        line_num = []
        line_str = line.split()
        for line_word in line_str:
            line_num.append(float(line_word))
        x123456x0_list.append(line_num[0:6])
        y_list.append(line_num[6])
    for x1x2 in x123456x0_list:
        x1x2.append(1.0)
    x123456x0_np_list = np.array(x123456x0_list)
    y_np_list = np.array(y_list)
    y_np_list = y_np_list.T
    return x123456x0_np_list, y_np_list

def read_k_data(filename, k):
    x123456y_list = []
    x123456x0_list = []
    y_list = []
    file = open(filename)
    lines = file.readlines()
    for line in lines:
        line_num = []
        line_str = line.split()
        i = 1
        for line_word in line_str:
            line_num.append(float(line_word))
            i += 1
            if i % 7 == 0:
                line_num.append(1.0)
        x123456y_list.append(line_num[0:8])
    x123456y_np_list = np.array(x123456y_list)
    np.random.shuffle(x123456y_np_list)
    slice_list = x123456y_np_list[0:k]
    for one in slice_list:
        x123456x0_list.append(one[0:7])
        y_list.append(one[7])
    x123456x0_np_list = np.array(x123456x0_list)
    y_np_list = np.array(y_list)
    y_np_list = y_np_list.T
    return x123456x0_np_list, y_np_list

def get_loss(x123456x0_list, y_list, w):
    loss = 0.0
    num = len(y_list)
    for i in range(0, num):
        mul = np.matmul(w, x123456x0_list[i].T)
        val = -1.0 * y_list[i] * mul + math.log(1 + math.exp(mul))
        loss += val
    return loss

def get_res(x123456x0_list, y_list, w):
    half = 0.0
    res = 0.0
    num = len(y_list)
    for i in range(0, num):
        mul = np.matmul(w, x123456x0_list[i].T)
        if mul == 0:
            half += 1
        if mul > 0 and y_list[i] == 1:
            res += 1
        if mul < 0 and y_list[i] == 0:
            res += 1
    return half, res

def iterf(x123456x0_list, y_list, w):
    d1 = w.T
    d2 = 0.0
    num = len(y_list)
    for i in range(0, num):
        mul = np.matmul(w, x123456x0_list[i].T)
        p1 = math.exp(mul) / (1 + math.exp(mul))
        d1 = d1 - (y_list[i] - p1) * x123456x0_list[i]
        d2_val = np.matmul(x123456x0_list[i], x123456x0_list[i].T) * p1 * (1.0-p1)
        d2 += d2_val
    w_t = w - (1.0/d2) * d1
    return w_t

def logistic_regression():
    w = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
    train_filename = "./dataForTrainingLogistic.txt"
    test_filename = "./dataForTestingLogistic.txt"
    lr_table = PrettyTable(["count", "w0", "w1", "w2", "w3", "w4", "w5", "w6", "train_loss", "test_loss"])
    iter_count = []
    iter_train_loss = []
    iter_test_loss = []
    iter_k_loss = []
    x123456x0_train_list, y_train_list = read_data(train_filename)
    x123456x0_test_list, y_test_list = read_data(test_filename)

    for k in range(1, 41):
        x_k_list, y_k_list = read_k_data(train_filename, k*10)
        for count in range(1, 101):
            train_loss = get_loss(x123456x0_train_list, y_train_list, w)
            test_loss = get_loss(x123456x0_test_list, y_test_list, w)
            k_loss = get_loss(x_k_list, y_k_list, w)
            w = iterf(x_k_list, y_k_list, w)
            iter_count.append(k*10)
            iter_train_loss.append(train_loss)
            iter_test_loss.append(test_loss)
            iter_k_loss.append(k_loss)
    # print(lr_table)
    print(get_res(x123456x0_test_list, y_test_list, w))
    plt.figure()
    plt.plot(iter_count, iter_train_loss, 'x-', c='b', label="train loss")  
    plt.plot(iter_count, iter_test_loss, 'o-', c='r', label="test loss")
    plt.plot(iter_count, iter_k_loss, '+-', c='b', label="train_subset_k loss")
    plt.xlabel("k")
    plt.ylabel("loss") 
    plt.legend()
    plt.show()  

logistic_regression()