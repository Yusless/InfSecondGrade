import numpy as np
import matplotlib.pyplot as plt
from statistics import mean

def MNK(x_axis,y_axis):
    def Cov(x_axis, y_axis):
        xy = mean(x_axis * y_axis)
        return xy - mean(x_axis) * mean(y_axis)
    k = Cov(x_axis, y_axis) / Cov(x_axis, x_axis)
    b = mean(y_axis) - k * mean(x_axis)
    return k, b 
data_points = [
    (100, 8100),
    (500, 48600),
    (1000, 109900),
    (5000, 652500),
    (10000, 1943200)
]

# Разделяем данные на n и время
n_values = np.array([point[0] for point in data_points])
time_ns = np.array([point[1] for point in data_points])

# Вычисляем n log n для сравнения
n_log_n = n_values * np.log2(n_values)

# Нормализуем n log n к нашим данным (находим коэффициент пропорциональности)
# Используем первую точку для нормализации
scale_factor = time_ns[0] / n_log_n[0]
n_log_n_scaled = n_log_n * scale_factor

# Создаем более плотную сетку для гладкого графика O(n log n)
n_dense = np.linspace(100, 10000, 500)
n_log_n_dense = n_dense * np.log2(n_dense) * scale_factor
k, b = MNK(time_ns,n_log_n) 
X=[]
for i in range(2000000):
    X.append(i)
Y=[]
for i in range(2000000):
    Y.append(i * k + b) 
fig,ax = plt.subplots()

ax.scatter(time_ns,n_log_n, s=5)
plt.plot(X,Y, color = 'red')
plt.xlabel('Время')
plt.ylabel('n log n')
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()