import pandas as pd
import json
import logging
from datetime import datetime
import sys

# Set up logging for error handling (adds the time, error value, and log message to the log file)
logging.basicConfig(
    filename='transform_errors.log',
    filemode='w',
    level=logging.ERROR,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

# Load the JSON configuration file
def load_config(config_file):
    try:
        with open(config_file, 'r') as file:
            config = json.load(file)
        return config
    # Handle file not found and JSON decode errors
    except FileNotFoundError:
        logging.error(f"Configuration file {config_file} not found.")
        sys.exit(f"Error: Configuration file {config_file} not found.")
     # Handle JSON decode errors
    except json.JSONDecodeError as e:
        logging.error(f"Error decoding JSON from {config_file}: {e}")
        sys.exit(f"Error: Invalid JSON in {config_file}.")


# Transform the input CSV data based on the configuration and save the output
def transform_data(input_file, output_file, config_file):
    config = load_config(config_file)
    try:
        # Read the CSV file
        df = pd.read_csv(input_file)
    # Handle file not found and empty file errors
    except FileNotFoundError:
        logging.error(f"Input file {input_file} not found.")
        sys.exit(f"Error: Input file {input_file} not found.")
    # Handle empty file errors
    except pd.errors.EmptyDataError:
        logging.error(f"Input file {input_file} is empty.")
        sys.exit(f"Error: Input file {input_file} is empty.")
    # Handle other exceptions
    except Exception as e:
        logging.error(f"Error reading {input_file}: {e}")
        sys.exit(f"Error: Unable to read {input_file}.")

    invalid_rows = []

    # Transformation Steps
    for target_col, rules in config['transformations'].items():
        try:
            if 'source_column' in rules:
                source_col = rules['source_column']
                # Apply transformations based on the the 4 transformation types (not including date)
                if rules['type'] == 'int':
                    df[target_col] = pd.to_numeric(df[source_col], errors='raise').astype(int)

                elif rules['type'] == 'float':
                    df[target_col] = df[source_col].replace(',', '', regex=True).astype(float)

                elif rules['type'] == 'string':
                    df[target_col] = df[source_col].astype(str)

                elif rules['type'] == 'propercase':
                    df[target_col] = df[source_col].str.title()

                # Error handling: unsupported type 
                else:
                    logging.error(f"Unsupported type {rules['type']} for column {target_col}.")
                    invalid_rows.append(target_col)
            
            # Apply transformations for date type
            elif 'source_columns' in rules and rules['type'] == 'date':
                year = df[rules['source_columns'][0]].astype(str)
                month = df[rules['source_columns'][1]].astype(str).str.zfill(2)
                day = df[rules['source_columns'][2]].astype(str).str.zfill(2)
                date_str = year + '-' + month + '-' + day
                df[target_col] = pd.to_datetime(date_str, format='%Y-%m-%d', errors='coerce')

                # Check for invalid dates
                invalid_date_mask = df[target_col].isnull()
                if invalid_date_mask.any():
                    invalid_rows.append(target_col)
                    for idx in df[invalid_date_mask].index:
                        logging.error(f"Invalid date at row {idx + 2}: {date_str[idx]}")

            # Apply transformations for constant value (for example, when its kg for all rows)
            elif 'constant_value' in rules:
                df[target_col] = rules['constant_value']

            else:
                logging.error(f"No valid source information for column {target_col}.")
                invalid_rows.append(target_col)
        
        # Error handling: source column not found
        except KeyError:
            logging.error(f"Source column {rules.get('source_column', rules.get('source_columns'))} not found in input data.")
            invalid_rows.append(target_col)

        # Error handling: value errors
        except ValueError as e:
            logging.error(f"Value error for column {target_col}: {e}")
            invalid_rows.append(target_col)

        # Error handling: other exceptions
        except Exception as e:
            logging.error(f"Unexpected error for column {target_col}: {e}")
            invalid_rows.append(target_col)

    # Keep only the required columns
    required_columns = list(config['transformations'].keys())
    try:
        final_df = df[required_columns]
    
    # Error handling: missing required columns
    except KeyError as e:
        logging.error(f"Error selecting columns: {e}")
        sys.exit(f"Error: Required columns missing in transformed data.")

    # Check for any nulls in required columns
    if final_df.isnull().values.any():
        logging.error("Null values in the transformed data.")
        print("Warning: Some rows have null values after transformation. Check 'transform_errors.log' for details.")

    # Write the transformed data to a new CSV
    try:
        final_df.to_csv(output_file, index=False)
        print(f"Output saved to {output_file}.")
    # Throw error if unable to write to output file
    except Exception as e:
        logging.error(f"Error writing to {output_file}: {e}")
        sys.exit(f"Error: Unable to write to {output_file}.")

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Transform CSV data based on a configuration file.')
    parser.add_argument('input_file', type=str, help='Path to the input CSV file.')
    parser.add_argument('output_file', type=str, help='Path to the output CSV file.')
    parser.add_argument('config_file', type=str, help='Path to the JSON configuration file.')

    args = parser.parse_args()

    transform_data(args.input_file, args.output_file, args.config_file)
