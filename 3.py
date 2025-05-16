import pandas as pd
import requests
import matplotlib.pyplot as plt
import seaborn as sns  

def plot_hp_visualizations(df):
    plt.figure(figsize=(15, 10))

    plt.subplot(2, 2, 1)
    sns.boxplot(y=df['hp'])
    plt.title('Box Plot of HP')

    plt.subplot(2, 2, 2)
    sns.scatterplot(x=df.index, y=df['hp'])
    plt.title('Scatter Plot of HP')

    plt.subplot(2, 2, 3)
    plt.hist(df['hp'], bins=10, edgecolor='black')
    plt.title('Histogram of HP')

    plt.subplot(2, 2, 4)
    df['hp'].value_counts().plot(kind='bar')
    plt.title('Bar Chart of HP')

    plt.tight_layout()
    plt.show()

def plot_hp_pie_chart(df):
    hp_counts = df['hp'].value_counts()
    plt.figure(figsize=(8, 8))
    plt.pie(hp_counts, labels=hp_counts.index, autopct='%1.1f%%', startangle=140)
    plt.title('Pie Chart of HP')
    plt.show()

def detect_outliers(df):
    Q1 = df['hp'].quantile(0.25)
    Q3 = df['hp'].quantile(0.75)
    IQR = Q3 - Q1
    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR
    outliers = df[(df['hp'] < lower_bound) | (df['hp'] > upper_bound)]
    return outliers  

if __name__ == "__main__":
    mtcars = pd.read_csv("mtcars.csv")
    plot_hp_visualizations(mtcars)
    plot_hp_pie_chart(mtcars)

    outliers = detect_outliers(mtcars)
    print("Outliers in HP:")
    print(outliers)
