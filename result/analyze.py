import pandas as pd
import matplotlib.pyplot as plt

# 读入Excel文件
file_path = 'insert_time_data.xlsx'  # 替换为你的文件路径
df = pd.read_excel(file_path)

# 获取数据
x = df['size']
y1 = df['small(std)']
y2 = df['big(std)']
y3 = df['larger(std)']
y4 = df['small(pro)']
y5 = df['big(pro)']
y6 = df['larger(pro)']

# 创建绘图
plt.figure(figsize=(16, 9))

# 绘制前三组数据，使用不同的相近色调
plt.plot(x, y1, label='small(std)', color='#1f77b4', linestyle='--')  # 蓝色
plt.plot(x, y2, label='big(std)', color='#2ca02c', linestyle='--')    # 绿色
plt.plot(x, y3, label='larger(std)', color='#d62728', linestyle='--')  # 红色

# 绘制后三组数据，使用另一种相近的色调
plt.plot(x, y4, label='small(pro)', color='#17becf')  # 青色
plt.plot(x, y5, label='big(pro)', color='#bcbd22')    # 橄榄色
plt.plot(x, y6, label='larger(pro)', color='#ff7f0e')  # 橙色

# 添加图例，标题和轴标签
plt.legend(ncol=2, loc='best')
# plt.yscale('log')
plt.legend()
plt.title('Insert time')
plt.xlabel('Number of Insertion')
plt.ylabel('Time (ns)')

# 显示图表
plt.grid(True)
plt.show()
