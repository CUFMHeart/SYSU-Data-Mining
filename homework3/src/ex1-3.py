import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable 

def read_data(filename):
    x1x2x0_list = []    # x0=1
    y_list = []
    file = open(filename)
    lines = file.readlines()
    for line in lines:
        line_num = []
        line_str = line.split()
        for line_word in line_str:
            line_num.append(float(line_word))
        x1x2x0_list.append(line_num[0:2])
        y_list.append(line_num[2])
    for x1x2 in x1x2x0_list:
        x1x2.append(1.0)
    x1x2x0_np_list = np.array(x1x2x0_list)
    y_np_list = np.array(y_list)
    y_np_list = y_np_list.T
    return x1x2x0_np_list, y_np_list

def get_loss(x1x2x0_list, y_list, theta):
    num = len(y_list)
    diff = y_list - np.matmul(x1x2x0_list, theta.T)
    diff_sq = pow(diff, 2)
    diff_sq = diff_sq.T
    loss = 0.5 * diff_sq.sum() / num
    return loss

def gradient_descent(x1x2x0_list, y_list, theta, rate):
    num = len(y_list)
    rand_num = np.random.randint(0, num)
    x1x2x0_temp = x1x2x0_list[rand_num]
    y_temp =y_list[rand_num]
    diff = y_temp - np.matmul(x1x2x0_temp, theta.T)
    x1 = x1x2x0_temp.T[0]
    x2 = x1x2x0_temp.T[1]
    x0 = x1x2x0_temp.T[2]
    x1 = x1.T
    x2 = x2.T
    x0 = x0.T
    grad1 = x1 * diff
    grad2 = x2 * diff
    grad0 = x0 * diff
    grad1_v = grad1.T.sum()
    grad2_v = grad2.T.sum()
    grad0_v = grad0.T.sum()
    theta_t = theta + rate * np.array([grad1_v, grad2_v, grad0_v])
    return theta_t

def linear_regression():
    learning_rate = 0.00015
    theta = np.array([0.0, 0.0, 0.0])
    train_filename = "./dataForTrainingLinear.txt"
    test_filename = "./dataForTestingLinear.txt"
    lr_table = PrettyTable(["count", "theta0", "theta1", "theta2", "train_loss", "test_loss"])
    iter_count = []
    iter_train_loss = []
    iter_test_loss = []
    x1x2x0_train_list, y_train_list = read_data(train_filename)
    x1x2x0_test_list, y_test_list = read_data(test_filename)
    for count in range(1, 1500001):
        if count % 100000 == 0:
            train_loss = get_loss(x1x2x0_train_list, y_train_list, theta)
            test_loss = get_loss(x1x2x0_test_list, y_test_list, theta)
        theta = gradient_descent(x1x2x0_train_list, y_train_list, theta, learning_rate)
        if count % 100000 == 0:
            iter_count.append(count)
            iter_train_loss.append(train_loss)
            iter_test_loss.append(test_loss)
            lr_table.add_row([count, theta.T[0], theta.T[1], theta.T[2], train_loss, test_loss])
    print(lr_table)
    plt.figure()
    plt.plot(iter_count, iter_train_loss, 'x-', c='b', label="train loss")  
    plt.plot(iter_count, iter_test_loss, 'o-', c='r', label="test loss")
    plt.xlabel("count")
    plt.ylabel("loss") 
    plt.legend()
    plt.show()  

linear_regression()