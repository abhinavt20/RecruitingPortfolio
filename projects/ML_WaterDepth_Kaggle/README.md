## Project Overview
The SI 670 Fall 2024 Kaggle Competition project is centered around predicting the water temperature at a specific depth (10.5m) in Trout Lake for a defined period using past lake temperature data collected from multiple sensors at various depths. This competition, hosted on Kaggle, allows participants to explore predictive modeling and machine learning techniques to accurately forecast water temperatures, leveraging sensor data spanning six years.

## Key Features
- **Depth-Specific Temperature Prediction**: The primary goal is to predict temperatures at a depth of 10.5m, using historical data from different depths as reference points.
- **Time Series Analysis**: Incorporates time-series data, with hourly measurements over a multi-year period, requiring techniques like trend analysis and seasonality adjustments.
- **Machine Learning & Benchmarking**: Uses supervised learning methods, with model accuracy evaluated using the Mean Squared Error (MSE), and benchmarks set for varying levels of accuracy.

## Requirements (Software & Libraries)
- **Python 3.8 or higher**
- **Libraries**:
  - `pandas` for data manipulation
  - `numpy` for numerical operations
  - `matplotlib` and `seaborn` for data visualization
  - `scikit-learn` for machine learning models and evaluation
  - `xgboost` for advanced model tuning
  - 'GridSearchCV' for optimal parameter tuning
  - 'cross_val_score' for nested cross validation

## Example Usage
After setting up and running the code, predictions for depth 10.5m can be generated for each hour between April 20, 2018, and April 19, 2019. The results will be saved in a `predictions.csv` file in the following format:
```
Date_Time,Water_Temp_C
04/20/2018 00:00,1.356
04/20/2018 01:00,1.342
...
04/19/2019 23:00,1.398
```

