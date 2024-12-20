// Query 5
// Find the oldest friend for each user who has a friend. For simplicity,
// use only year of birth to determine age, if there is a tie, use the
// one with smallest user_id. You may find query 2 and query 3 helpful.
// You can create selections if you want. Do not modify users collection.
// Return a javascript object : key is the user_id and the value is the oldest_friend id.
// You should return something like this (order does not matter):
// {user1:userx1, user2:userx2, user3:userx3,...}

function oldest_friend(dbname) {
    db = db.getSiblingDB(dbname);

    let results = {};
    // TODO: implement oldest friends
    db.users.find().forEach((u)=>
       {db.users.find({
            $or:[{user_id:{$in: u.friends}}, {friends:{$in: [u.user_id]}}]
        
        }).sort({"YOB": 1, "user_id":1}).limit(1).forEach((f)=>{results[u.user_id]=f.user_id;});
    });



    return results;
}
