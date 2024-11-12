    package project2;

    import java.sql.Connection;
    import java.sql.SQLException;
    import java.sql.Statement;
    import java.sql.ResultSet;
    import java.util.ArrayList;

    /*
        The StudentFakebookOracle class is derived from the FakebookOracle class and implements
        the abstract query functions that investigate the database provided via the <connection>
        parameter of the constructor to discover specific information.
    */
    public final class StudentFakebookOracle extends FakebookOracle {
        // [Constructor]
        // REQUIRES: <connection> is a valid JDBC connection
        public StudentFakebookOracle(Connection connection) {
            oracle = connection;
        }

        @Override
        // Query 0
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the total number of users for which a birth month is listed
        //        (B) Find the birth month in which the most users were born
        //        (C) Find the birth month in which the fewest users (at least one) were born
        //        (D) Find the IDs, first names, and last names of users born in the month
        //            identified in (B)
        //        (E) Find the IDs, first names, and last name of users born in the month
        //            identified in (C)
        //
        // This query is provided to you completed for reference. Below you will find the appropriate
        // mechanisms for opening up a statement, executing a query, walking through results, extracting
        // data, and more things that you will need to do for the remaining nine queries
        public BirthMonthInfo findMonthOfBirthInfo() throws SQLException {
            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                // Step 1
                // ------------
                // * Find the total number of users with birth month info
                // * Find the month in which the most users were born
                // * Find the month in which the fewest (but at least 1) users were born
                ResultSet rst = stmt.executeQuery(
                        "SELECT COUNT(*) AS Birthed, Month_of_Birth " + // select birth months and number of uses with that birth month
                                "FROM " + UsersTable + " " + // from all users
                                "WHERE Month_of_Birth IS NOT NULL " + // for which a birth month is available
                                "GROUP BY Month_of_Birth " + // group into buckets by birth month
                                "ORDER BY Birthed DESC, Month_of_Birth ASC"); // sort by users born in that month, descending; break ties by birth month

                int mostMonth = 0;
                int leastMonth = 0;
                int total = 0;
                while (rst.next()) { // step through result rows/records one by one
                    if (rst.isFirst()) { // if first record
                        mostMonth = rst.getInt(2); //   it is the month with the most
                    }
                    if (rst.isLast()) { // if last record
                        leastMonth = rst.getInt(2); //   it is the month with the least
                    }
                    total += rst.getInt(1); // get the first field's value as an integer
                }
                BirthMonthInfo info = new BirthMonthInfo(total, mostMonth, leastMonth);

                // Step 2
                // ------------
                // * Get the names of users born in the most popular birth month
                rst = stmt.executeQuery(
                        "SELECT User_ID, First_Name, Last_Name " + // select ID, first name, and last name
                                "FROM " + UsersTable + " " + // from all users
                                "WHERE Month_of_Birth = " + mostMonth + " " + // born in the most popular birth month
                                "ORDER BY User_ID"); // sort smaller IDs first

                while (rst.next()) {
                    info.addMostPopularBirthMonthUser(new UserInfo(rst.getLong(1), rst.getString(2), rst.getString(3)));
                }

                // Step 3
                // ------------
                // * Get the names of users born in the least popular birth month
                rst = stmt.executeQuery(
                        "SELECT User_ID, First_Name, Last_Name " + // select ID, first name, and last name
                                "FROM " + UsersTable + " " + // from all users
                                "WHERE Month_of_Birth = " + leastMonth + " " + // born in the least popular birth month
                                "ORDER BY User_ID"); // sort smaller IDs first

                while (rst.next()) {
                    info.addLeastPopularBirthMonthUser(new UserInfo(rst.getLong(1), rst.getString(2), rst.getString(3)));
                }

                // Step 4
                // ------------
                // * Close resources being used
                rst.close();
                stmt.close(); // if you close the statement first, the result set gets closed automatically

                return info;

            } catch (SQLException e) {
                System.err.println(e.getMessage());
                return new BirthMonthInfo(-1, -1, -1);
            }
            
        }

        @Override
        // Query 1
        // -----------------------------------------------------------------------------------
        // GOALS: (A) The first name(s) with the most letters
        //        (B) The first name(s) with the fewest letters
        //        (C) The first name held by the most users
        //        (D) The number of users whose first name is that identified in (C)
        public FirstNameInfo findNameInfo() throws SQLException {
            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    FirstNameInfo info = new FirstNameInfo();
                    info.addLongName("Aristophanes");
                    info.addLongName("Michelangelo");
                    info.addLongName("Peisistratos");
                    info.addShortName("Bob");
                    info.addShortName("Sue");
                    info.addCommonName("Harold");
                    info.addCommonName("Jessica");
                    info.setCommonNameCount(42);
                    return info;
                */
                //a,b sort first names by length and get longest and shortest first name
                ResultSet rst = stmt.executeQuery(
                    "SELECT First_Name, LENGTH(First_Name) AS NameCount " +
                    "FROM " + UsersTable + " " +
                    "WHERE First_Name IS NOT NULL " +
                    "GROUP BY First_Name " +
                    "ORDER BY LENGTH(First_Name) DESC, First_Name ASC"
                );
                int largestCount = -1;
                FirstNameInfo info = new FirstNameInfo();

                while (rst.next()) {
                    String fN = rst.getString(1);
                    int nameCount = rst.getInt(2);

                    if (rst.isFirst()) {
                        largestCount = nameCount;
                    }
                    
                    if (nameCount != largestCount) {
                        break;
                    }
                    info.addLongName(fN);
                }
                
                //short
                rst = stmt.executeQuery(
                    "SELECT first_name, LENGTH(first_name) AS NameCount " +
                    "FROM " + UsersTable + " " +
                    "WHERE First_Name IS NOT NULL " +
                    "GROUP BY first_name " +
                    "ORDER BY LENGTH(First_Name) ASC, first_name ASC"
                );
                int smallestCount = -1;

                while (rst.next()) {
                    String fN = rst.getString(1);
                    int nameCount = rst.getInt(2);

                    if (rst.isFirst()) {
                        smallestCount = nameCount;
                    }
                    if (nameCount != smallestCount) {
                        break;
                    }
                    info.addShortName(fN);
                    
                }
                

                //CD
                rst = stmt.executeQuery(
                    "SELECT first_name, COUNT(*) AS NameCount " +
                    "FROM " + UsersTable + " " +
                    "GROUP BY first_name " +
                    "ORDER BY NameCount DESC, first_name ASC"
                );
                int count = -1;
                while (rst.next()) {
                    String fN = rst.getString(1);
                    int nameCount = rst.getInt(2);
                    if (rst.isFirst()) {
                        count = nameCount;                
                        info.setCommonNameCount(count);
                    }
                    if (nameCount != count) {
                        break;
                    }

                    info.addCommonName(fN);
                }



                rst.close();
                stmt.close(); // if you close the statement first, the result set gets closed automatically

                return info;

            } catch (SQLException e) {
                System.err.println(e.getMessage());
                return new FirstNameInfo();
            }
            
        }

        @Override
        // Query 2
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the IDs, first names, and last names of users without any friends
        //
        // Be careful! Remember that if two users are friends, the Friends table only contains
        // the one entry (U1, U2) where U1 < U2.
        public FakebookArrayList<UserInfo> lonelyUsers() throws SQLException {
            FakebookArrayList<UserInfo> results = new FakebookArrayList<UserInfo>(", ");

            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    UserInfo u1 = new UserInfo(15, "Abraham", "Lincoln");
                    UserInfo u2 = new UserInfo(39, "Margaret", "Thatcher");
                    results.add(u1);
                    results.add(u2);
                */

                ResultSet rst = stmt.executeQuery(
                    "SELECT user_id, First_Name, Last_Name " +
                    "FROM " + UsersTable + " " +
                    "WHERE user_id IN (" +
                        "SELECT user_id " +
                        "FROM " + UsersTable + " " +
                        "MINUS " +
                        "(SELECT user1_id " +
                        "FROM " + FriendsTable + " " +
                        "UNION " +
                        "SELECT user2_id " +
                        "FROM " + FriendsTable + "))"
                );
        
                while (rst.next()) {
                    UserInfo userInfo = new UserInfo(rst.getLong(1), rst.getString(2), rst.getString(3));
                    results.add(userInfo);
                }
        
                rst.close();
                stmt.close();
                return results;
        
                } catch (SQLException e) {
                    System.err.println(e.getMessage());
                }
        
                
            return results;


            
        }

        @Override
        // Query 3
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the IDs, first names, and last names of users who no longer live
        //            in their hometown (i.e. their current city and their hometown are different)
        public FakebookArrayList<UserInfo> liveAwayFromHome() throws SQLException {
            FakebookArrayList<UserInfo> results = new FakebookArrayList<UserInfo>(", ");

            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    UserInfo u1 = new UserInfo(9, "Meryl", "Streep");
                    UserInfo u2 = new UserInfo(104, "Tom", "Hanks");
                    results.add(u1);
                    results.add(u2);
                */
                ResultSet rst = stmt.executeQuery(
                        "SELECT U.user_id, U.first_name, U.last_name " +
                        "FROM " + UsersTable + " U " +
                        "JOIN " + CurrentCitiesTable + " C " +
                        "ON U.user_id = C.user_id " +
                        "JOIN " + HometownCitiesTable + " H " +
                        "ON U.user_id = H.user_id " +
                        "WHERE H.hometown_city_id != C.current_city_id " +
                        "ORDER BY U.user_id ASC"
                );

                
                while (rst.next()) {
                    results.add(new UserInfo(rst.getLong(1), rst.getString(2), rst.getString(3)));
                }

                rst.close();
                stmt.close();
                return results;


            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
            return results;
            
        }

        @Override
        // Query 4
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the IDs, links, and IDs and names of the containing album of the top
        //            <num> photos with the most tagged users
        //        (B) For each photo identified in (A), find the IDs, first names, and last names
        //            of the users therein tagged
        public FakebookArrayList<TaggedPhotoInfo> findPhotosWithMostTags(int num) throws SQLException {
            FakebookArrayList<TaggedPhotoInfo> results = new FakebookArrayList<TaggedPhotoInfo>("\n");

            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    PhotoInfo p = new PhotoInfo(80, 5, "www.photolink.net", "Winterfell S1");
                    UserInfo u1 = new UserInfo(3901, "Jon", "Snow");
                    UserInfo u2 = new UserInfo(3902, "Arya", "Stark");
                    UserInfo u3 = new UserInfo(3903, "Sansa", "Stark");
                    TaggedPhotoInfo tp = new TaggedPhotoInfo(p);
                    tp.addTaggedUser(u1);
                    tp.addTaggedUser(u2);
                    tp.addTaggedUser(u3);
                    results.add(tp);
                */

                ResultSet rst = stmt.executeQuery(
                    "SELECT photo_id, album_id, photo_link, album_name " +
                    "FROM (SELECT p1.photo_id, p1.album_id, p1.photo_link, a1.album_name " +
                        "FROM " + PhotosTable + " p1 " +
                        "JOIN " + AlbumsTable + " a1 ON p1.album_id = a1.album_id " +
                        "JOIN " + TagsTable + " t1 ON p1.photo_id = t1.tag_photo_id " +
                        "GROUP BY p1.photo_id, p1.album_id, p1.photo_link, a1.album_name " +
                        "ORDER BY COUNT(*) DESC, p1.photo_id ASC) " +
                    "WHERE ROWNUM <= " + num    
                );

                while (rst.next()) {
                    long uid = rst.getLong(1);
                    PhotoInfo p = new PhotoInfo(uid, rst.getLong(2), rst.getString(3), rst.getString(4));
                    TaggedPhotoInfo tp = new TaggedPhotoInfo(p);

                    try (Statement stmt2 = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                        ResultSet urst = stmt2.executeQuery(
                            "SELECT u.user_id, u.first_name, u.last_name " +
                            "FROM " + TagsTable + " t " +
                            "JOIN " + UsersTable + " u ON t.tag_subject_id = u.user_id " +
                            "WHERE t.tag_photo_id = " + uid + " " + 
                            "ORDER BY u.user_id ASC"
                        );
                        
                        
                        while (urst.next()) {
                            
                            tp.addTaggedUser(new UserInfo(urst.getLong(1), urst.getString(2), urst.getString(3)));
                            
                        }
                        results.add(tp);
                        urst.close();
                        stmt2.close();
                    } catch (SQLException e) {
                        System.err.println(e.getMessage());
                    }
                

                }
                rst.close();
                stmt.close();//close statements and return before exception

                
                return results;

            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
            return results;

        
        }

        @Override
        // Query 5
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the IDs, first names, last names, and birth years of each of the two
        //            users in the top <num> pairs of users that meet each of the following
        //            criteria:
        //              (i) same gender
        //              (ii) tagged in at least one common photo
        //              (iii) difference in birth years is no more than <yearDiff>
        //              (iv) not friends
        //        (B) For each pair identified in (A), find the IDs, links, and IDs and names of
        //            the containing album of each photo in which they are tagged together
        public FakebookArrayList<MatchPair> matchMaker(int num, int yearDiff) throws SQLException {
            FakebookArrayList<MatchPair> results = new FakebookArrayList<MatchPair>("\n");

            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    UserInfo u1 = new UserInfo(93103, "Romeo", "Montague");
                    UserInfo u2 = new UserInfo(93113, "Juliet", "Capulet");
                    MatchPair mp = new MatchPair(u1, 1597, u2, 1597);
                    PhotoInfo p = new PhotoInfo(167, 309, "www.photolink.net", "Tragedy");
                    mp.addSharedPhoto(p);
                    results.add(mp);
                */
                ResultSet rst = stmt.executeQuery(
                    "SELECT * FROM ( " +
                    "SELECT U1.User_ID AS u1id, U1.First_Name AS u1fn, U1.Last_Name AS u1ln, U1.Year_Of_Birth AS u1yob, " +
                    "U2.user_id AS u2id, U2.first_name as u2fn, U2.last_name AS u2ln, U2.year_of_birth AS u2yob " +
                    "FROM " + UsersTable + " U1 " +
                    "JOIN " + UsersTable + " U2 ON U1.gender = U2.gender AND U1.User_ID != U2.user_id " +
                    "JOIN " + TagsTable + " T1 ON U1.user_id = T1.tag_subject_id " +
                    "JOIN " + TagsTable + " T2 ON U2.user_id = T2.tag_subject_id " +
                    "WHERE ABS(U1.year_of_birth - U2.year_of_birth) <= " + yearDiff + " " +
                    "AND ((u1.user_id, u2.user_id) NOT IN (SELECT * FROM " + FriendsTable + ") OR (u2.user_id, u1.user_id) NOT IN (SELECT * FROM " + FriendsTable + "))" +
                    "AND T1.tag_photo_id = T2.tag_photo_id " +
                    "AND U1.user_id < U2.user_id " +
                    "ORDER BY U1.user_id ASC, u2.user_id ASC) " +
                    "WHERE ROWNUM <= " + num
            
                    
                );
                
                while (rst.next()) {
                    Long u1id = rst.getLong(1);
                    Long u2id = rst.getLong(5);
                    UserInfo u1 = new UserInfo(u1id, rst.getString(2), rst.getString(3));
                    UserInfo u2 = new UserInfo(u2id, rst.getString(6), rst.getString(7));
                    MatchPair mp = new MatchPair(u1, rst.getLong(4), u2, rst.getLong(8));

                    //find the IDs, links, and IDs and names of the containing album of each photo
                    try (Statement stmt2 = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                        ResultSet prst = stmt2.executeQuery(
                            "SELECT P.photo_id, P.photo_link, P.album_id, A.album_name " +
                            "FROM " + UsersTable + " U1 " +
                            "JOIN " + UsersTable + " U2 ON U1.user_id != U2.user_id " +
                            "JOIN " + TagsTable + " T1 ON T1.tag_subject_id = U1.user_id " +
                            "JOIN " + TagsTable + " T2 ON T2.tag_subject_id = U2.user_id " + 
                            "JOIN " + PhotosTable + " P ON T1.tag_photo_id = P.photo_id AND T2.tag_photo_id = P.photo_id " +
                            "JOIN " + AlbumsTable + " A ON P.album_id = A.album_id " +
                            "WHERE U1.user_id = " + u1id + " AND U2.user_id = " + u2id + " " +
                            "ORDER BY P.photo_id ASC"
                        );
                        while (prst.next()) {
                            PhotoInfo p = new PhotoInfo(prst.getLong(1), prst.getLong(3), prst.getString(2), prst.getString(4));
                            mp.addSharedPhoto(p);
                        }
                        results.add(mp);
                        prst.close();
                        stmt2.close();
                    } catch (SQLException e) {
                        System.err.println(e.getMessage());
                    }
                }
                
                rst.close();
                stmt.close();
                return results;


            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }

            return results;
        }

        @Override
        // Query 6
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the IDs, first names, and last names of each of the two users in
        //            the top <num> pairs of users who are not friends but have a lot of
        //            common friends
        //        (B) For each pair identified in (A), find the IDs, first names, and last names
        //            of all the two users' common friends
        public FakebookArrayList<UsersPair> suggestFriends(int num) throws SQLException {
            FakebookArrayList<UsersPair> results = new FakebookArrayList<UsersPair>("\n");

            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    UserInfo u1 = new UserInfo(16, "The", "Hacker");
                    UserInfo u2 = new UserInfo(80, "Dr.", "Marbles");
                    UserInfo u3 = new UserInfo(192, "Digit", "Le Boid");
                    UsersPair up = new UsersPair(u1, u2);
                    up.addSharedFriend(u3);
                    results.add(up);
                */


                
                String query6View = "CREATE VIEW b AS " +
                        "SELECT user1_id AS Friend1, user2_id AS Friend2 " +
                        "FROM " + FriendsTable + " " +
                        "UNION " +
                        "SELECT user2_id AS Friend1, user1_id AS Friend2 " +
                        "FROM " + FriendsTable;
                
                stmt.executeUpdate(query6View);

                String pair3View = "CREATE VIEW pairs AS " +
                    "SELECT F1.Friend1 AS user1, F2.Friend1 AS user2, F2.Friend2 AS mutualFriend " +
                    "FROM b F1 " +
                    "JOIN b F2 ON F1.Friend1 != F2.Friend1 " + 
                    "WHERE F1.Friend2 = F2.Friend2 AND F1.Friend1 < F2.Friend1 ";
                stmt.executeUpdate(pair3View);

                

               
                String mutualView = "CREATE VIEW mutuals AS " +
                    "SELECT user1, user2, COUNT(*) as nummuts " +
                    "FROM pairs " + 
                    "GROUP BY user1, user2 " +
                    "ORDER BY nummuts DESC, user1 ASC, user2 ASC";;
                stmt.executeUpdate(mutualView);

                ResultSet rst = stmt.executeQuery(
                    "SELECT U1.user_id, U1.first_name, U1.last_name, U2.user_id, U2.first_name, U2.last_name " +
                    "FROM mutuals m " +
                    "JOIN " + UsersTable + " U1 ON U1.user_id = m.user1 " +
                    "JOIN " + UsersTable + " U2 ON U2.user_id = m.user2 " +
                    "WHERE ROWNUM <= " + num
                );

                while (rst.next()) {
                    Long u1id = rst.getLong(1);
                    Long u2id = rst.getLong(4);
                    UserInfo u1 = new UserInfo(u1id, rst.getString(2), rst.getString(3));
                    UserInfo u2 = new UserInfo(u2id, rst.getString(5), rst.getString(6));
                    UsersPair up = new UsersPair(u1,u2);

                    try (Statement stmt2 = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {

                        ResultSet rst2 = stmt2.executeQuery(
                            "SELECT U.user_id, U.first_name, U.last_name " +
                            "FROM " + UsersTable + " U " +
                            "JOIN pairs P ON U.user_id = p.mutualFriend " +
                            "WHERE p.user1 = " + u1id + " AND p.user2 = " +u2id + " " +
                            "ORDER BY U.user_id ASC"
                        );
                        
                        while (rst2.next()) {
                            UserInfo u3 = new UserInfo(rst2.getLong(1), rst2.getString(2), rst2.getString(3));
                            up.addSharedFriend(u3);
                        }
                        rst2.close();
                        stmt2.close();

                    } catch (SQLException e) {
                        System.err.println(e.getMessage());
                    }


                    results.add(up);
                }





                
                
                stmt.executeUpdate("DROP VIEW mutuals");
                stmt.executeUpdate("DROP VIEW pairs");
                stmt.executeUpdate("DROP VIEW b");


                    
                

                rst.close();
                stmt.close();
                return results;

                


            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }

            return results;
        }

        @Override
        // Query 7
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the name of the state or states in which the most events are held
        //        (B) Find the number of events held in the states identified in (A)
        public EventStateInfo findEventStates() throws SQLException {
            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    EventStateInfo info = new EventStateInfo(50);
                    info.addState("Kentucky");
                    info.addState("Hawaii");
                    info.addState("New Hampshire");
                    return info;
                */

                


    
                ResultSet rst = stmt.executeQuery(
                    "SELECT C.state_name, COUNT(*) AS NumEvents " +
                    "FROM " + CitiesTable + " C " +
                    "JOIN " + EventsTable + " E ON E.event_city_id = C.city_id " +
                    "GROUP BY C.State_Name " +
                    "ORDER BY NumEvents DESC, C.state_name ASC"
                );
    
                int numst = 0;
                EventStateInfo info = null;
                while (rst.next()) {
                    if (rst.isFirst()) {
                        numst = rst.getInt(2);
                        info = new EventStateInfo(numst);
                    }
                    if (rst.getInt(2) != numst) {
                        break;
                    }
                    info.addState(rst.getString(1));
                }
                

                

                rst.close();
                stmt.close();
                return info;

    
            } catch (SQLException e) {
                System.err.println(e.getMessage());
                return new EventStateInfo(-1);
            }
            
        }

        @Override
        // Query 8
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find the ID, first name, and last name of the oldest friend of the user
        //            with User ID <userID>
        //        (B) Find the ID, first name, and last name of the youngest friend of the user
        //            with User ID <userID>
        public AgeInfo findAgeInfo(long userID) throws SQLException {
            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    UserInfo old = new UserInfo(12000000, "Galileo", "Galilei");
                    UserInfo young = new UserInfo(80000000, "Neil", "deGrasse Tyson");
                    return new AgeInfo(old, young);
                */
                
                String query8View = "CREATE VIEW FriendInfo AS "
                    + "SELECT * " +
                    "FROM " + UsersTable + " u " + 
                    "JOIN (" +
                        "SELECT user1_id AS Friend1, user2_id AS Friend2 " +
                        "FROM " + FriendsTable + " " +
                        "UNION " +
                        "SELECT user2_id AS Friend1, user1_id AS Friend2 " +
                        "FROM " + FriendsTable + " ) f ON u.user_id = f.Friend2 " +
                        "WHERE f.Friend1 = " + userID;
                
                stmt.executeUpdate(query8View);

                ResultSet rst = stmt.executeQuery(
                    "SELECT user_id, first_name, last_name " +
                    "FROM FriendInfo " + 
                    "ORDER BY year_of_birth ASC, month_of_birth ASC, day_of_birth ASC, user_id DESC" 
                );

                rst.next(); 
                UserInfo old = new UserInfo(rst.getInt(1), rst.getString(2), rst.getString(3));
                
                rst = stmt.executeQuery(
                    "SELECT user_id, first_name, last_name " +
                    "FROM FriendInfo "+
                    "ORDER BY year_of_birth DESC, month_of_birth DESC, day_of_birth DESC, user_id DESC"
                );

                rst.next();
                UserInfo young = new UserInfo(rst.getInt(1), rst.getString(2), rst.getString(3));
                stmt.executeUpdate("DROP VIEW FriendInfo");
                rst.close();
                stmt.close();
                return new AgeInfo(old, young);
                
                
            } catch (SQLException e) {
                System.err.println(e.getMessage());
                return new AgeInfo(new UserInfo(-1, "ERROR", "ERROR"), new UserInfo(-1, "ERROR", "ERROR"));
            }
        
        }

        @Override
        // Query 9
        // -----------------------------------------------------------------------------------
        // GOALS: (A) Find all pairs of users that meet each of the following criteria
        //              (i) same last name
        //              (ii) same hometown
        //              (iii) are friends
        //              (iv) less than 10 birth years apart
        public FakebookArrayList<SiblingInfo> findPotentialSiblings() throws SQLException {
            FakebookArrayList<SiblingInfo> results = new FakebookArrayList<SiblingInfo>("\n");

            try (Statement stmt = oracle.createStatement(FakebookOracleConstants.AllScroll,
                    FakebookOracleConstants.ReadOnly)) {
                /*
                    EXAMPLE DATA STRUCTURE USAGE
                    ============================================
                    UserInfo u1 = new UserInfo(81023, "Kim", "Kardashian");
                    UserInfo u2 = new UserInfo(17231, "Kourtney", "Kardashian");
                    SiblingInfo si = new SiblingInfo(u1, u2);
                    results.add(si);
                */
                //is creating this view only for redundant friends in the table?
                

                ResultSet rst = stmt.executeQuery(
                    "SELECT DISTINCT u1.user_id, u1.first_name, u1.last_name, u2.user_id, u2.first_name, u2.last_name " +
                    "FROM " + UsersTable + " u1 " + 
                    "JOIN " + UsersTable + " u2 ON u1.last_name = u2.last_name AND u1.user_id != u2.user_id " +
                    "JOIN " + HometownCitiesTable + " h1 ON u1.user_id = h1.user_id " +
                    "JOIN " + HometownCitiesTable + " h2 ON u2.user_id = h2.user_id " +
                    "WHERE (h1.hometown_city_id = h2.hometown_city_id) " +
                    "AND  (((u1.user_id,u2.user_id) IN (SELECT * FROM "+FriendsTable + " )) OR ((u2.user_id,u1.user_id) IN (SELECT * FROM "+FriendsTable +" )))"+
                    "AND (ABS(u1.year_of_birth - u2.year_of_birth) < 10) AND (u1.user_id < u2.user_id) " +
                    "ORDER BY u1.user_id ASC, u2.user_id ASC"
                );
            
                while (rst.next()) {
                    UserInfo user1 = new UserInfo(rst.getInt(1), rst.getString(2), rst.getString(3));
                    UserInfo user2 = new UserInfo(rst.getInt(4), rst.getString(5), rst.getString(6));
                    SiblingInfo s = new SiblingInfo(user1, user2);
                    results.add(s);
                }

                //stmt.executeUpdate("DROP VIEW FriendsView");
                rst.close();
                stmt.close();
                return results;

            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
            return results;

            
        }

        // Member Variables
        private Connection oracle;
        private final String UsersTable = FakebookOracleConstants.UsersTable;
        private final String CitiesTable = FakebookOracleConstants.CitiesTable;
        private final String FriendsTable = FakebookOracleConstants.FriendsTable;
        private final String CurrentCitiesTable = FakebookOracleConstants.CurrentCitiesTable;
        private final String HometownCitiesTable = FakebookOracleConstants.HometownCitiesTable;
        private final String ProgramsTable = FakebookOracleConstants.ProgramsTable;
        private final String EducationTable = FakebookOracleConstants.EducationTable;
        private final String EventsTable = FakebookOracleConstants.EventsTable;
        private final String AlbumsTable = FakebookOracleConstants.AlbumsTable;
        private final String PhotosTable = FakebookOracleConstants.PhotosTable;
        private final String TagsTable = FakebookOracleConstants.TagsTable;
    }
