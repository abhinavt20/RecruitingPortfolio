
# EECS 484 Project 2: Fakebook JDBC

Link to project:[https://eecs484db.github.io/f24/p2-fakebook-jdbc](https://eecs484db.github.io/f24/p2-fakebook-jdbc)

## Requirements
- **Java Development Kit (JDK)**: Version 1.7 or 1.8 is recommended to ensure compatibility with `ojdbc6.jar`.
- **Oracle Database Access**: Credentials and access to the EECS 484 Fakebook database.

## File Structure
- **StudentFakebookOracle.java**: Core file where SQL queries are implemented.
- **FakebookOracle.java**: Base abstract class defining required query methods.
- **FakebookOracleDataStructures.java**: Custom data structures for handling query results.
- **PublicFakebookOracleConstants.java**: Constants defining schema details for public dataset access.
- **FakebookOracleUtilities.java**: Utility class for handling array lists and output formatting.
- **FakebookOracleMain.java**: Main application driver file to run and test queries.

## Key Queries Implemented
- Query 0: **Birth Months** - Provided as an example; retrieves birth month data for users.
- Query 1: **First Names** - Identifies longest, shortest, and most common first names.
- Query 2: **Lonely Users** - Lists users with no friends.
- Query 3: **Users Who Live Away From Home** - Finds users who do not live in their hometown.
- Query 4: **Highly-Tagged Photos** - Returns top tagged photos and tagged users.
- Query 5: **Matchmaker** - Suggests possible friendships based on tags and birth year proximity.
- Query 6: **Suggest Friends** - Suggests friendships based on mutual friends.
- Query 7: **Event-Heavy States** - Lists states with the highest event counts.
- Query 8: **Oldest and Youngest Friends** - Finds oldest and youngest friends for a given user.
- Query 9: **Potential Siblings** - Identifies potential sibling pairs based on criteria.

## How to Build and Run
1. **Compile the Project**:
   ```bash
   make compile
   ```
2. **Run Queries**:
   - To run all queries and view output:
     ```bash
     make query-all
     ```
   - To run a specific query (e.g., Query 1):
     ```bash
     make query1
     ```

3. **Check Runtime Performance**:
   - To time all queries:
     ```bash
     make time-all
     ```
   - To time a single query (e.g., Query 1):
     ```bash
     make time1
     ```

4. **Clean Up**:
   ```bash
   make clean
   ```

## Example Usage
Use the `make query-all` command to test outputs against `PublicSolution.txt` and verify correctness.
Ensure your output matches exactly as specified, as any deviation may indicate issues in query implementation.


