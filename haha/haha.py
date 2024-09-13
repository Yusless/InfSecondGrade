import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from random import gauss
from statistics import mean

def get_linear_data(N, k, b, xsigma, ysigma, min_data, max_data):
    xdata = np.linspace(min_data, max_data, N)
    ydata=k*xdata +b
    for i in range(N):
        xdata[i] += gauss(0, xsigma * xdata[i])
        ydata[i] += gauss(0, ysigma * ydata[i])
    return xdata,ydata

def MNK(xdata,ydata):
    def Cov(xdata, ydata):
        xy = mean(xdata * ydata)
        return xy - mean(xdata) * mean(ydata)
    
    N = len(xdata)
    k = Cov(xdata, ydata) / Cov(xdata, xdata)
    b = mean(ydata) - k * mean(xdata)
    sigma_k = Cov(ydata, ydata) / Cov(xdata, xdata)
    sigma_k -= k ** 2
    sigma_k = np.sqrt((1/(N-2)) * sigma_k)
    sigma_b=sigma_k * np.sqrt(mean([x ** 2 for x in xdata]))
    return k, b, sigma_k, sigma_b



data = get_linear_data(10, 5, 2, 0.01, 0.02, 20, 35)
k, b, _, _1 = MNK(data[0], data[1])

#popt, pcov = curve_fit(lambda x, a, b : a*x+b, xdata, ydata)
#k, b = popt[0], popt[1]

#k, b = np.polyfit(xdata, ydata, 1)

fig,ax = plt.subplots()
ax.scatter(data[0], data[1])
ax.plot(data[0], data[0] * k + b)
plt.show()
