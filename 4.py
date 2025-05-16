import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
from sklearn.datasets import load_iris

# Load the Iris dataset
iris = load_iris()
df = pd.DataFrame(data=iris.data, columns=iris.feature_names)
df['species'] = pd.Categorical.from_codes(iris.target, iris.target_names)

# Correlation Matrix Analysis
print("CORRELATION MATRIX ANALYSIS")
print("--------------------------")
correlation_matrix = df.iloc[:, 0:4].corr()
print("Correlation Matrix:")
print(correlation_matrix)
print("\n")

# Covariance Analysis
print("COVARIANCE ANALYSIS")
print("------------------")
covariance_matrix = df.iloc[:, 0:4].cov()
print("Covariance Matrix:")
print(covariance_matrix)
print("\n")

# ANOVA Analysis
print("ANOVA ANALYSIS")
print("-------------")
features = iris.feature_names
print("One-way ANOVA results for each feature across different species:")
for feature in features:
    groups = [df[df['species'] == species][feature] for species in iris.target_names]
    f_val, p_val = stats.f_oneway(*groups)
    print(f"\nFeature: {feature}")
    print(f"F-value: {f_val:.4f}")
    print(f"p-value: {p_val:.8f}")
    if p_val < 0.05:
        print("Result: There are significant differences between species for this feature")
    else:
        print("Result: No significant differences between species for this feature")

# Correlation Matrix Heatmap
plt.figure(figsize=(10, 8))
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', vmin=-1, vmax=1)
plt.title('Correlation Matrix Heatmap of Iris Features')
plt.tight_layout()
plt.savefig('correlation_heatmap.png')

# Covariance Matrix Heatmap
plt.figure(figsize=(10, 8))
sns.heatmap(covariance_matrix, annot=True, cmap='viridis')
plt.title('Covariance Matrix Heatmap of Iris Features')
plt.tight_layout()
plt.savefig('covariance_heatmap.png')

# ANOVA Boxplots
plt.figure(figsize=(12, 10))
for i, feature in enumerate(features):
    plt.subplot(2, 2, i+1)
    sns.boxplot(x='species', y=feature, data=df)
    plt.title(f'Distribution of {feature} by Species')
plt.tight_layout()
plt.savefig('anova_boxplots.png')

# Pairplot of Features
plt.figure(figsize=(12, 10))
sns.pairplot(df, hue='species')
plt.tight_layout()
plt.savefig('feature_relationships.png')

print("\nAnalysis complete. All visualizations have been saved.")
