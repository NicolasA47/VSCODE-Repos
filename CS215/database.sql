CREATE TABLE Users (
	id_ int NOT NULL AUTO_INCREMENT,
	email varchar (30) NOT NULL,
	pword varchar (30) NOT NULL,
	birthday varchar (30) NOT NULL,
	screenname varchar (30) NOT NULL,
	profile_pic varchar (50) NOT NULL,
    PRIMARY KEY(id_)
);

CREATE TABLE Recipes (
    recipe_title varchar (50) NOT NULL,
    recipe_desc varchar (255) NOT NULL,
    recipe_date varchar(20) NOT NULL,
    recipe_ingredients varchar (512) NOT NULL,
    recipe_instructions varchar (512) NOT NULL,
    recipe_picture varchar (50) NOT NULL,
    recipe_rating int,
    recipe_id  int NOT NULL AUTO_INCREMENT,
    id_ int NOT NULL,
    PRIMARY KEY(recipe_id),
    FOREIGN KEY(id_) REFERENCES Users(id_)
);

CREATE TABLE Ratings (
	rating_id int NOT NULL AUTO_INCREMENT,
    id_ int,
    recipe_id int,
	rating int NOT NULL,
    PRIMARY KEY(rating_id)
    FOREIGN KEY(id_) REFERENCES Users(id_),
    FOREIGN KEY(recipe_id) REFERENCES Recipes(recipe_id)
);


insert into Users(_id, email, pword, birthday, screenname, profile_pic) 
values (0,'nra862@uregina.ca','passw0rd','07/28/2001','Nicolas','/images/profile-pics/picture.jpg');
insert into Users(_id, email, pword, birthday, screenname, profile_pic) 
values (0,'bob111@uregina.ca','passw0rd','07/28/2001','Brian','/images/profile-pics/picture.jpg');

insert into Recipes(recipe_title, recipe_desc, recipe_ingredients ,recipe_instructions, recipe_picture, recipe_rating, recipe_id, _id)
values ('Chicken Parm', 'This is the best damn this you will ever eat', 'chicken, bacon, mozzarella, cheddar',
        'Lorem ipsum dolor sit amet consectetur adipisicing elit.', 'images/recipe-pics/chicken-parm', 0, 0, 0);

insert into Recipes(recipe_title, recipe_desc, recipe_ingredients ,recipe_instructions, recipe_picture, recipe_rating, recipe_id, _id)
values ('Bacon', 'This is the best damn this you will ever eat', 'bacon, bacon, bacon',
        'Lorem ipsum dolor sit amet consectetur adipisicing elit.', 'images/recipe-pics/bacon', 0, 0, 0);

insert into Ratings(rating_id, id_, recipe_id, rating)
values (0, 1, 1, 4);
insert into Ratings(rating_id, id_, recipe_id, rating)
values (0, 1, 1, 3);




SELECT (id_, screenname, profile_pic) FROM Users WHERE email = "nra862@uregina.ca" AND pword = "passw0rd"

UPDATE ratings set rating=2 WHERE _id=1;





