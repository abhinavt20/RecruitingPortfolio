import unittest
import pandas as pd
import os
from transform import transform_data

class TestTransformData(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """
        Set up test environment by creating sample input and expected output files.
        """
        # Create a test input CSV
        cls.test_input = 'test_input.csv'
        test_data = {
            'Order Number': [123, 456, 'abc'],  # 'abc' is invalid for OrderID
            'Year': [2023, 2022, 2021],
            'Month': [9, 11, 2],
            'Day': [25, 15, 30],  # February 30th is invalid
            'Product Number': ['A1234', 'B5678', 'C9012'],
            'Product Name': ['APPLE', 'BANANA', 'CHERRY'],
            'Count': ['1', '5.5', '3.2'],
            'Extra Col1': ['--', '--', '--'],
            'Extra Col2': ['--', '--', '--']
        }
        df = pd.DataFrame(test_data)
        df.to_csv(cls.test_input, index=False)

        # Create an expected output CSV for valid rows only
        cls.expected_output = 'expected_output.csv'
        expected_data = {
            'OrderID': [123, 456],
            'OrderDate': [pd.Timestamp('2023-09-25'), pd.Timestamp('2022-11-15')],
            'ProductId': ['A1234', 'B5678'],
            'ProductName': ['Apple', 'Banana'],
            'Quantity': [1.0, 5.5],
            'Unit': ['kg', 'kg']
        }
        expected_df = pd.DataFrame(expected_data)
        expected_df.to_csv(cls.expected_output, index=False)

        # Configuration file
        cls.config_file = 'config.json'

    @classmethod
    def tearDownClass(cls):
        """
        Clean up test files after tests run.
        """
        files_to_remove = [
            cls.test_input,
            cls.expected_output,
            'output.csv',
            'transform_errors.log'
        ]
        for file in files_to_remove:
            if os.path.exists(file):
                os.remove(file)

    def test_valid_transformation(self):
        """
        Test transformation with valid data.
        """
        output_file = 'output.csv'
        transform_data(self.test_input, output_file, self.config_file)

        # Load the output and expected data
        df_output = pd.read_csv(output_file)
        df_expected = pd.read_csv(self.expected_output)

        # Convert 'OrderDate' to datetime for comparison
        df_output['OrderDate'] = pd.to_datetime(df_output['OrderDate'])
        df_expected['OrderDate'] = pd.to_datetime(df_expected['OrderDate'])

        # Compare DataFrames
        pd.testing.assert_frame_equal(df_output, df_expected)

    def test_invalid_data(self):
        """
        Test transformation with invalid data.
        """
        output_file = 'output.csv'
        transform_data(self.test_input, output_file, self.config_file)

        # Check if 'transform_errors.log' contains errors
        self.assertTrue(os.path.exists('transform_errors.log'), "Error log file does not exist.")

        with open('transform_errors.log', 'r') as log_file:
            logs = log_file.read()
            self.assertIn("Error converting OrderID", logs)
            self.assertIn("Invalid date at row 4: 2021-02-30", logs)

        # Load the output data
        df_output = pd.read_csv(output_file)

        # Ensure that only valid rows are transformed
        self.assertEqual(len(df_output), 2, "Output should contain only 2 valid rows.")

if __name__ == '__main__':
    unittest.main()
