import pandas as pd

pd.options.display.float_format = "{:.1f}".format

# Усреднение худших результатов
frames = [pd.read_csv(f"worse/result0{i}.csv", skipinitialspace=True) for i in range(1, 6)]
table = pd.concat(frames).groupby("n").mean()
table.to_csv("worse/avg.csv")
print(table)
print()

# Усреднение лучших результатов
frames = [pd.read_csv(f"best/result0{i}.csv", skipinitialspace=True) for i in range(1, 6)]
table = pd.concat(frames).groupby("n").mean()
table.to_csv("best/avg.csv")
print(table)
