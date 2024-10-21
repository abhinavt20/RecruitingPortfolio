# README

## Overview
This project is designed to help you clean up and transform CSV data based on specified config rules. It reads an input CSV, applies the transformations you define in a `config.json` file, and produces a new CSV as the output. If any issues come up (like invalid dates), they’ll be logged in `transform_errors.log` so you can address them easily.

## How to Build and Run

### Prerequisites:

- **Python 3.8+**
- Required package: 
  - `pandas`

### Running the Code:

1. Make sure your `input.csv`, `config.json`, and `transform.py` are in the same directory.
2. From terminal, run the following command:
   python transform.py input.csv output.csv config.json

The transformed data will be saved as output.csv, and any errors (like invalid dates) will be logged in transform_errors.log.

### Architecture and Technology Overview
This tool is built for flexibility, so you can easily modify how your CSV data is transformed by updating the config.json file.  

### Key Components:
transform.py: Contains the main logic for applying the transformations
config.json: Specifies which transformations to apply to each column 
transform_errors.log: Any errors or warnings are logged here to help with debugging

### Technologies:
Python & Pandas: I used pandas for efficient data manipulation.
JSON: The transformation rules are stored in config.json because it’s easy to modify in the future. 

### Assumptions 
Input Format:
    I expected the input file to be in CSV format, with all necessary columns outlined in config.json.
Date Handling: 
    I assumed the Year, Month, and Day columns are provided separately and need to be combined into a valid date. However, if an invalid date is added it will log the error to transform_errors.log.
Error Handling: 
    Any issues during transformation are logged, but there is no code to fix these error, so invalid rows are still included in the final output.

### Next Steps
Support Larger Datasets:
    Implement chunked processing to handle CSV files that may be too large to fit into memory.

Improve Error Handling:
    This could include retrying failed transformations or trying to fix the errors. 

