import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score, mean_absolute_error
import statsmodels.api as sm
from statsmodels.stats.outliers_influence import variance_inflation_factor

# Set seed for reproducibility
np.random.seed(42)

# Load dataset
housing = fetch_california_housing()
X = housing.data
y = housing.target
feature_names = housing.feature_names

# Create a DataFrame for easier handling
df = pd.DataFrame(X, columns=feature_names)
df['target'] = y

# Dataset Information
print("Dataset Information:")
print(f"Number of samples: {X.shape[0]}")
print(f"Number of features: {X.shape[1]}")
print(f"Features: {feature_names}")
print("\nData Preview:")
print(df.head())
print("\nStatistical Summary:")
print(df.describe())

# Check for missing values
print("\nMissing Values:")
print(df.isnull().sum())

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Standardize features
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Build and train the multiple linear regression model
model = LinearRegression()
model.fit(X_train_scaled, y_train)

# Make predictions
y_pred = model.predict(X_test_scaled)

# Evaluate the model
mse = mean_squared_error(y_test, y_pred)
rmse = np.sqrt(mse)
mae = mean_absolute_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("\nModel Evaluation:")
print(f"Mean Squared Error: {mse:.4f}")
print(f"Root Mean Squared Error: {rmse:.4f}")
print(f"Mean Absolute Error: {mae:.4f}")
print(f"R-squared: {r2:.4f}")

# Display model coefficients
coefficients = pd.DataFrame({'Feature': feature_names, 'Coefficient': model.coef_}).sort_values('Coefficient', ascending=False)
print("\nModel Coefficients:")
print(coefficients)

# Statistical Summary using OLS
X_train_sm = sm.add_constant(X_train_scaled)  # Adding intercept term
sm_model = sm.OLS(y_train, X_train_sm).fit()
print("\nDetailed Statistical Summary:")
print(sm_model.summary())

# Function to calculate Variance Inflation Factors (VIF)
def calculate_vif(X):
    vif = pd.DataFrame()
    vif["Variable"] = X.columns
    vif["VIF"] = [variance_inflation_factor(X.values, i) for i in range(X.shape[1])]
    return vif

X_train_df = pd.DataFrame(X_train, columns=feature_names)
vif_data = calculate_vif(X_train_df)
print("\nVariance Inflation Factors:")
print(vif_data)

# Visualizations
plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred, alpha=0.6)
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'r--', lw=2)
plt.xlabel('Actual Values')
plt.ylabel('Predicted Values')
plt.title('Actual vs Predicted Values')
plt.tight_layout()

plt.figure(figsize=(10, 6))
residuals = y_test - y_pred
plt.scatter(y_pred, residuals, alpha=0.6)
plt.hlines(y=0, xmin=min(y_pred), xmax=max(y_pred), colors='r', linestyles='--')
plt.xlabel('Predicted Values')
plt.ylabel('Residuals')
plt.title('Residual Plot')
plt.tight_layout()

plt.figure(figsize=(10, 6))
sns.histplot(residuals, kde=True)
plt.xlabel('Residuals')
plt.ylabel('Frequency')
plt.title('Distribution of Residuals')
plt.tight_layout()

plt.figure(figsize=(12, 8))
sns.barplot(x='Coefficient', y='Feature', data=coefficients)
plt.title('Feature Coefficients')
plt.tight_layout()

plt.figure(figsize=(12, 10))
correlation_matrix = df.corr()
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', linewidths=0.5)
plt.title('Correlation Matrix')
plt.tight_layout()

fig, axes = plt.subplots(4, 2, figsize=(15, 20))
axes = axes.flatten()
for i, feature in enumerate(feature_names):
    if i < len(axes):
        sns.regplot(x=df[feature], y=df['target'], ax=axes[i])
        axes[i].set_title(f'Partial Regression Plot: {feature}')
plt.tight_layout()

# Implementing Multiple Linear Regression from scratch
class CustomMultipleLinearRegression:
    def __init__(self, learning_rate=0.01, num_iterations=1000):
        self.learning_rate = learning_rate
        self.num_iterations = num_iterations
        self.weights = None
        self.bias = None
        self.cost_history = []

    def fit(self, X, y):
        num_samples, num_features = X.shape
        self.weights = np.zeros(num_features)
        self.bias = 0
        self.cost_history = []

        for _ in range(self.num_iterations):
            y_predicted = np.dot(X, self.weights) + self.bias
            cost = (1 / (2 * num_samples)) * np.sum((y_predicted - y) ** 2)
            self.cost_history.append(cost)
            
            dw = (1 / num_samples) * np.dot(X.T, (y_predicted - y))
            db = (1 / num_samples) * np.sum(y_predicted - y)

            self.weights -= self.learning_rate * dw
            self.bias -= self.learning_rate * db

    def predict(self, X):
        return np.dot(X, self.weights) + self.bias

    def get_cost_history(self):
        return self.cost_history

# Train and evaluate the custom model
custom_model = CustomMultipleLinearRegression(learning_rate=0.01, num_iterations=1000)
custom_model.fit(X_train_scaled, y_train)
custom_y_pred = custom_model.predict(X_test_scaled)

print("\nCustom Multiple Linear Regression Model:")
print(f"Mean Squared Error: {mean_squared_error(y_test, custom_y_pred):.4f}")
print(f"Root Mean Squared Error: {np.sqrt(mean_squared_error(y_test, custom_y_pred)):.4f}")
print(f"R-squared: {r2_score(y_test, custom_y_pred):.4f}")

plt.figure(figsize=(10, 6))
plt.plot(custom_model.get_cost_history())
plt.xlabel('Iteration')
plt.ylabel('Cost')
plt.tight_layout()
