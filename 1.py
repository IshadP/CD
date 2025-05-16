import pandas as pd
df = pd.read_csv("mtcars.csv")
data = df["hp"]
subset_data = df[['hp', 'mpg', 'wt']]
agg_data = subset_data.aggregate(['mean', 'median', 'min', 'max'])
print("Data Info:")
print(df.info())
print("------------")
print("Data summary")
print(df.describe())  
print("------------")
print("Quartiles are:")
print(data.quantile([0.25, 0.5, 0.75]))
print("------------")
print("Subset data:")
print(subset_data.head())
print("------------")
print("Aggregate Data:")
print(agg_data)