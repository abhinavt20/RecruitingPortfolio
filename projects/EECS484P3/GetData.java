import java.io.FileWriter;
import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.TreeSet;
import java.util.Vector;

import org.json.JSONObject;
import org.json.JSONArray;

public class GetData {

    static String prefix = "project3.";

    // You must use the following variable as the JDBC connection
    Connection oracleConnection = null;

    // You must refer to the following variables for the corresponding 
    // tables in your database
    String userTableName = null;
    String friendsTableName = null;
    String cityTableName = null;
    String currentCityTableName = null;
    String hometownCityTableName = null;

    // DO NOT modify this constructor
    public GetData(String u, Connection c) {
        super();
        String dataType = u;
        oracleConnection = c;
        userTableName = prefix + dataType + "_USERS";
        friendsTableName = prefix + dataType + "_FRIENDS";
        cityTableName = prefix + dataType + "_CITIES";
        currentCityTableName = prefix + dataType + "_USER_CURRENT_CITIES";
        hometownCityTableName = prefix + dataType + "_USER_HOMETOWN_CITIES";
    }

    // TODO: Implement this function
    @SuppressWarnings("unchecked")
    public JSONArray toJSON() throws SQLException {

        // This is the data structure to store all users' information
        JSONArray users_info = new JSONArray();
        
        try (Statement stmt = oracleConnection.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY)) {
            // Your implementation goes here....
            
            

            ResultSet rst = stmt.executeQuery(
                "SELECT DISTINCT U.user_id, U.first_name, U.last_name, U.gender, U.year_of_birth, U.month_of_birth, U.day_of_birth, CC.city_name, CC.state_name, CC.country_name, HC.city_name, HC.state_name, HC.country_name " +
                "FROM " + userTableName + " U " +
                "JOIN " + currentCityTableName + " C ON C.user_id = U.user_id " +
                "JOIN " + cityTableName + " CC ON C.current_city_id = CC.city_id " +
                "JOIN " + hometownCityTableName + " H ON H.user_id = U.user_id " +
                "JOIN " + cityTableName + " HC ON H.hometown_city_id = HC.city_id"

                
            );
            while (rst.next()) {
                int curruid = rst.getInt(1);
                JSONArray friends = new JSONArray();
                try (Statement stmt2 = oracleConnection.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY)) {
                    ResultSet rst2 = stmt2.executeQuery(
                        "SELECT friendID2 FROM (" +
                            "SELECT user1_id AS friendID1, user2_id AS friendID2 " +
                            "FROM " + friendsTableName + " " +
                            "UNION " +
                            "SELECT user2_id AS friendID1, user1_id AS friendID2 " +
                            "FROM " + friendsTableName + ")" +
                        "WHERE friendID1 = " + curruid + " AND friendID2 > " + curruid
                    );
                    while (rst2.next()) {
                        friends.put(rst2.getInt(1));
                    }


                    
                    rst2.close();
                    stmt2.close();
                } catch (SQLException e) {
                    System.err.println(e.getMessage());
                }

                JSONObject user = new JSONObject();
                user.put("user_id", rst.getInt(1));
                user.put("first_name", rst.getString(2));
                user.put("last_name", rst.getString(3));
                user.put("gender", rst.getString(4));
                user.put("YOB", rst.getInt(5));
                user.put("MOB", rst.getInt(6));
                user.put("DOB", rst.getInt(7));

                user.put("friends", friends);

                JSONObject currentLocation = new JSONObject();
                currentLocation.put("city", rst.getString(8));
                currentLocation.put("state", rst.getString(9));
                currentLocation.put("country", rst.getString(10));
                user.put("current", currentLocation);


                JSONObject hometownLocation = new JSONObject();
                hometownLocation.put("city", rst.getString(11));
                hometownLocation.put("state", rst.getString(12));
                hometownLocation.put("country", rst.getString(13));
                user.put("hometown", hometownLocation);

                users_info.put(user);


                /*String u = "{user_id: " + rst.getInt(1)+ ", first_name: " + rst.getString(2) + ", last_name: "
                + rst.getString(3) + ", gender: " + rst.getString(4) + ", YOB: " + rst.getInt(5) + ", MOB: " + rst.getInt(6)
                + ", DOB: " + rst.getInt(7) + ", current: {city: " + rst.getString(8) + ", state: " + rst.getString(9) + ", country: " + rst.getString(10)
                + "}, hometown: {city: " + rst.getString(11) + ", state: " + rst.getString(12) + ", country: " + rst.getString(13)"}, " +
                "friends: {" + friends + "}}"*/


            }
            
            rst.close();
            stmt.close();
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }

        return users_info;
    }

    // This outputs to a file "output.json"
    // DO NOT MODIFY this function
    public void writeJSON(JSONArray users_info) {
        try {
            FileWriter file = new FileWriter(System.getProperty("user.dir") + "/output.json");
            file.write(users_info.toString());
            file.flush();
            file.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
