// Query 6
// Find the average friend count per user.
// Return a decimal value as the average user friend count of all users in the users collection.

function find_average_friendcount(dbname) {
    db = db.getSiblingDB(dbname);

    // TODO: calculate the average friend count
    var totalFriendCount = 0;
    var userCount = 0;

    db.users.find().forEach(function(user) {
        var friendCount = user.friends.length;
        totalFriendCount += friendCount;
        userCount++;
    });

    var averageFriendCount = totalFriendCount / userCount || 0;

    return averageFriendCount;
}
