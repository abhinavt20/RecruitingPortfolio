
# Project 3: MongoDB - Fakebook Data Management

## Project Overview
In Project 3, we explore the capabilities of MongoDB, a NoSQL database, by managing data for the fictional social media platform Fakebook. The project has two parts: exporting data from an Oracle database to JSON format, and importing this data into MongoDB for further querying and analysis.

## Key Features
1. **Export to JSON**: Extracts user data from the Fakebook Oracle database and exports it to JSON format for MongoDB usage.
2. **MongoDB Queries**: Seven MongoDB queries on the JSON data, handling various relationships and statistics like friend connections and birth month analysis.
3. **Data Management**: Creates MongoDB collections for organized data storage and retrieval.

## File Structure
- `GetData.java`: Contains the function to export Oracle database information to JSON.
- `Main.java`: The driver for Part A that runs data export and creates output.json.
- `Makefile`: Facilitates compilation, testing, and running both parts of the project.
- `query[1-7].js`: JavaScript files containing each MongoDB query.

## Requirements
- **Java JDK** (1.8+ for Oracle SQL and JSON generation)
- **MongoDB 3.6** (Tested on CAEN servers)
- **ojdbc6.jar** (for Oracle DB connectivity)
- **json_simple-1.1.jar, json-20151123.jar** (for JSON support)

## How to Build and Run the Code
1. **Compile** the code using the Makefile:
   ```
   make compile
   ```
2. **Run Part A** to generate output.json from the Oracle database:
   ```
   make run
   ```
3. **Set up MongoDB** by loading data:
   ```
   make setupsampledb  # Uses sample.json
   make setupmydb  # Uses output.json
   ```
4. **Test Queries**:
   ```
   make mongotest
   ```

## Example Usage
To test specific queries or commands, use the mongo shell directly:
```shell
make loginmongo  # Opens mongo shell on CAEN
```
To check output differences between output.json and sample.json, use JSON diff tools as standard `diff` may not work due to ordering differences.

