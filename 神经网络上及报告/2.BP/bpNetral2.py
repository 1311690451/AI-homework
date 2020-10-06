import numpy as np
import math
import matplotlib.pyplot as plt

x = np.linspace(-1, 1, 21)
# print(x)
# print(x[1])
x_size = x.size
y = np.zeros((x_size, 1))
# print(y.size)
y=[-0.96 ,-0.577 ,-0.0729 ,0.377 ,0.641 ,0.66 ,0.461 ,0.1336 ,-0.201 ,-0.434 ,-0.5 ,-0.393 ,-0.1647 ,0.0988
,0.3072 ,0.396 ,0.3449 ,0.1816 ,-0.0312 ,-0.2183 ,-0.3201]

# print(y)


hidesize = 10
W1 = np.random.random((hidesize, 1))  # 输入层与隐层之间的权重
B1 = np.random.random((hidesize, 1))  # 隐含层神经元的阈值
W2 = np.random.random((1, hidesize))  # 隐含层与输出层之间的权重
B2 = np.random.random((1, 1))  # 输出层神经元的阈值
threshold = 0.005
max_steps = 1001


def sigmoid(x_):
    y_ = 1/ (1 + math.exp(-x_))
    return y_


E = np.zeros((max_steps, 1))  # 误差随迭代次数的变化
Y = np.zeros((x_size, 1))  # 模型的输出结果
for k in range(max_steps):
    temp = 0
    for i in range(x_size):
        hide_in = np.dot(x[i], W1) - B1  # 隐含层输入数据
        # print(x[i])
        hide_out = np.zeros((hidesize, 1))  # 隐含层的输出数据
        for j in range(hidesize):
            hide_out[j] = sigmoid(hide_in[j])
            # print("第{}个的值是{}".format(j, hide_out[j]))

        # print(hide_out[3])
        y_out = np.dot(W2, hide_out) - B2  # 模型输出
        # print(y_out)

        Y[i] = y_out
        # print(i,Y[i])

        e = y_out - y[i]  # 模型输出减去实际结果。得出误差

        ##反馈，修改参数
        dB2 = -1 * threshold * e
        dW2 = e * threshold * np.transpose(hide_out)
        dB1 = np.zeros((hidesize, 1))
        for j in range(hidesize):
            dB1[j] = np.dot(np.dot(W2[0][j], sigmoid(hide_in[j])), (1 - sigmoid(hide_in[j])) * (-1) * e * threshold)

        dW1 = np.zeros((hidesize, 1))

        for j in range(hidesize):
            dW1[j] = np.dot(np.dot(W2[0][j], sigmoid(hide_in[j])), (1 - sigmoid(hide_in[j])) * x[i] * e * threshold)

        W1 = W1 - dW1
        B1 = B1 - dB1
        W2 = W2 - dW2
        B2 = B2 - dB2
        temp = temp + abs(e)

    E[k] = temp

    if k % 1000 == 0:
        print(k)

plt.figure()
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
plt.plot(x, y, label='原数据曲线')
plt.plot(x, Y, color='red', linestyle='--', label='预测曲线')
plt.legend()
plt.show()








