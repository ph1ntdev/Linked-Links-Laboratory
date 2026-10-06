import pandas as pd

# Усреднение худших результатов
frames = [pd.read_csv(f"worse/result0{i}.csv", skipinitialspace=True) for i in range(1, 5)]
table = pd.concat(frames).groupby("n").mean()
table.to_csv("worse/avgWorse.csv")
print(table)
print()

# Усреднение лучших результатов
frames = [pd.read_csv(f"best/result0{i}.csv", skipinitialspace=True) for i in range(1, 5)]
table = pd.concat(frames).groupby("n").mean()
table.to_csv("best/avgBest.csv")
print(table)
