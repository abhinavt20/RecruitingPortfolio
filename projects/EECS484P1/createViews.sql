CREATE VIEW View_User_Information AS 
SELECT U.user_id, U.first_name, U.last_name, U.year_of_birth, U.month_of_birth, 
U.day_of_birth, U.gender, C.city_name AS current_city, C.state_name AS current_state, C.country_name AS current_country, 
CH.city_name AS hometown_city, CH.state_name AS hometown_state, CH.country_name AS hometown_country, 
P.institution AS institution_name, E.program_year,
P.concentration AS program_concentration, P.degree AS program_degree
FROM Users U 
LEFT JOIN User_Current_Cities Cu ON U.user_id=Cu.user_id
LEFT JOIN Cities C ON C.city_id = Cu.current_city_id
LEFT JOIN User_Hometown_Cities H ON U.user_id = H.user_id
LEFT JOIN Cities CH ON CH.city_id = H.hometown_city_id
LEFT JOIN Education E ON E.user_id = U.user_id
LEFT JOIN Programs P ON P.program_id = E.program_id;


CREATE VIEW View_Are_Friends AS 
SELECT user1_id, user2_id
FROM Friends;


CREATE VIEW View_Photo_Information AS 
SELECT A.album_id, A.album_owner_id AS owner_id, A.cover_photo_id, A.album_name, A. album_created_time, 
A.album_modified_time, A.album_link, A.album_visibility, P.photo_id, P.photo_caption, 
P.photo_created_time, P.photo_modified_time, P.photo_link
FROM Photos P
LEFT JOIN Albums A ON A.album_id=P.album_id;


CREATE VIEW View_Event_Information AS
SELECT E.event_id, E.event_creator_id, E.event_name, E.event_tagline, E.event_description, E.event_host, E.event_type, E.event_subtype, 
E.event_address, C.city_name AS event_city, C.state_name AS event_state, C.country_name AS event_country,
E.event_start_time, E.event_end_time
FROM User_Events E
LEFT JOIN Cities C ON E.event_city_id = C.city_id;


CREATE VIEW View_Tag_Information AS
SELECT tag_photo_id, tag_subject_id, tag_created_time, tag_x AS tag_x_coordinate , tag_y AS tag_y_coordinate
FROM Tags;