🍷 C++ Problem: Predicting Wine Quality Using Kth Nearest Neighbors (7 Dimensions)
Problem Statement
You are provided with a dataset of wines, where each wine is represented by 7 chemical and sensory features, along with a quality rating (from 0 to 10). Your task is to predict the quality rating of a new wine sample using the Kth Nearest Neighbors (KNN) algorithm, based on Euclidean distance in multi-dimensional space.

---

Wine Features
Each wine sample is described using the following 7 features:

Fixed Acidity (g/L)
Volatile Acidity (g/L)
Citric Acid (g/L)
Residual Sugar (g/L)
Chlorides (g/L)
Free Sulfur Dioxide (mg/L)
Density (g/cm³)

The target value is:

Quality Rating (0 to 10, integer)

---

Input Format
You are given a .dat file (e.g. wine_data.dat), with each line in the format:

<fixed_acidity> <volatile_acidity> <citric_acid> <residual_sugar> <chlorides> <free_sulfur_dioxide> <density> <quality>


Example:

7.4 0.70 0.00 1.9 0.076 11 0.9978 5


From standard input, you will receive:

  
An integer K — the number of neighbors.
A line representing the new wine sample with 7 features in the same order.

---

Output Format
Print the predicted wine quality based on the average quality of the K nearest neighbors, rounded to 2 decimal places.

---

Constraints
1 <= K <= number of training samples
All values are real numbers; quality is an integer in [0, 10]
Dataset size: ≤ 10,000 samples

---

Sample .dat File (wine_data.dat)
7.4 0.70 0.00 1.9 0.076 11 0.9978 5
7.8 0.88 0.00 2.6 0.098 25 0.9968 5
7.8 0.76 0.04 2.3 0.092 15 0.9970 5
11.2 0.28 0.56 1.9 0.075 17 0.9980 6
7.4 0.70 0.00 1.9 0.076 11 0.9978 5
7.9 0.60 0.06 1.6 0.069 16 0.9964 6
6.7 0.58 0.08 2.0 0.080 15 0.9959 5


---

Sample Input
3
7.5 0.72 0.01 2.0 0.077 12 0.9979


---

Sample Output
5.33


---

Explanation
You calculate the Euclidean distance between the test wine and each sample in the dataset (based on all 7 features). The 3 closest samples are selected, and their average quality is computed and printed.

---

✅ Extra Credit
Implement z-score normalization for all features before distance calculation.
Add support for weighted KNN, where closer neighbors contribute more to the average