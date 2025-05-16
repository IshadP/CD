import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score

# Generate synthetic data
X, true_labels = make_blobs(n_samples=300, centers=4, cluster_std=0.60, random_state=42)

# Evaluate silhouette scores for k = 2 to 9
silhouette_scores = []
for k in range(2, 10):
    kmeans = KMeans(n_clusters=k, random_state=42)
    cluster_labels = kmeans.fit_predict(X)
    silhouette_avg = silhouette_score(X, cluster_labels)
    silhouette_scores.append(silhouette_avg)
    print(f"For n_clusters = {k}, the silhouette score is {silhouette_avg:.3f}")

# Determine the optimal number of clusters
optimal_k = np.argmax(silhouette_scores) + 2
print(f"\nOptimal number of clusters: {optimal_k}")

# Fit KMeans using the optimal number of clusters
kmeans = KMeans(n_clusters=optimal_k, random_state=42)
cluster_labels = kmeans.fit_predict(X)
centroids = kmeans.cluster_centers_

# Plot the clusters and centroids
plt.figure(figsize=(10, 8))
colors = ['r', 'g', 'b', 'y', 'c', 'm', 'orange', 'purple', 'brown']
for i in range(optimal_k):
    cluster_points = X[cluster_labels == i]
    plt.scatter(cluster_points[:, 0], cluster_points[:, 1],
                c=colors[i], label=f'Cluster {i}', alpha=0.7)
    plt.scatter(centroids[i, 0], centroids[i, 1],
                marker='*', s=300, c='black', edgecolor=colors[i], linewidth=2)

plt.title('K-means Clustering')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()
