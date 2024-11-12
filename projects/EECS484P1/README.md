
# Project 1: Fakebook Database

## Project Overview
In this project, we design a relational database for a fictional social media platform called "Fakebook." The project involves creating an ER Diagram, SQL scripts for setting up and managing the database schema, loading data from a public dataset, and creating external views to display the data.

## Key Features
### ER Diagram
- Design an ER Diagram representing key business rules and entities like Users, Messages, Photos and Albums, and Events.

### SQL Scripts
- **Create Tables**: Define SQL Data Definition Language (DDL) statements to create tables and set constraints based on the project requirements.
- **Drop Tables**: DDL statements to drop the tables and constraints.
- **Load Data**: Populate tables using data from a public dataset.
- **Create Views**: Set up views that mirror the schema of the public dataset for easy querying.
- **Drop Views**: DDL statements to drop views.

## File Structure
- `createTables.sql`: Creates data tables, constraints, and sequences for Fakebook.
- `dropTables.sql`: Drops all tables and constraints.
- `loadData.sql`: Loads data from the public dataset into the tables.
- `createViews.sql`: Creates external views for querying data in a format matching the public dataset.
- `dropViews.sql`: Drops all external views.

## Requirements
- **Software**: SQL*Plus, Oracle Database (access via CAEN Linux environment recommended)
- **Setup**: Ensure access to SQL*Plus on CAEN Linux machines and the Oracle environment.

## How to Build and Run
1. **Connect to SQL*Plus** on CAEN and load the provided scripts in the specified order.
2. Run the following commands to execute each step:

```sql
-- Create tables
@createTables.sql

-- Load data
@loadData.sql

-- Create views
@createViews.sql

-- Drop views (if needed)
@dropViews.sql

-- Drop tables (if needed)
@dropTables.sql
```

This sequence will set up the database, load data, and create views for Fakebook. To drop views or tables, execute `dropViews.sql` and `dropTables.sql` as needed.

## Example Queries
Refer to the example queries provided in the public dataset and view verification section of the project instructions for validating table and view structure.


