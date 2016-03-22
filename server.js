var express = require('express');
var bodyParser = require('body-parser');
var massive = require("massive");
var base64 = require('node-base64-image');
var keygen = require('keygen');
var app = express();
var config = require('./config.json');
//var connectionString = "postgres://"+config.postgres.user+":"+config.postgres.password+"@"+config.postgres.host+"/"+config.postgres.db;
var port = (process.env.PORT || 5000); // config.express.port
var connectionString = process.env.DATABASE_URL;
var db;

app.use(bodyParser.json({limit: '50mb'})); // for parsing application/json
app.use(bodyParser.urlencoded({limit: '50mb', extended: true})); // for parsing application/x-www-form-urlencoded


/************************************************************************/
/******************					AUX				 ********************/
/************************************************************************/

function checkForError(err, res, message) {
	if (err) {
		console.error(message, err);
		res.sendStatus(500);
		return true;
	}
	return false;
}

function checkIfUndefined(data, message) {
	if (data === undefined) {
		console.error(message);
		res.sendStatus(500);
		return true;
	}
	return false;
}

/************************************************************************/
/************************************************************************/

function decodeImage(data, res) {
	var imageData = new Buffer(data, 'base64');
	var options = {filename: "profile"};
	base64.base64decoder(imageData, options, function (err, saved) {
		if (checkForError(err, res, "Error storing photo")) return;
		res.send(saved);  
	});	
}

/************************************************************************/
/***************				RESTFUL API				*****************/
/************************************************************************/

// This responds with a JSON of users
app.get('/users', function (req, res) {
	// TODO
	var response = {users: []};
	db.run("select * from users", function(err, users) { 
		if (checkForError(err, res, "Error at creating new user")) return;
		for (i = 0; i < users.length; i++) {
			var data = users[i].data;
			data.id = users[i].id;
			response.users.push({user: data});
		}
		response.metadata = {version: "0.1", count: users.length};
		res.send(response);
	});
});

/************************************************************************/
/************************************************************************/

// This responds with a JSON of users
app.get('/users/:user_id', function (req, res) {
	var response = {metadata: {version: "0.1"}};
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, res, "Error at creating new user")) return;
        if (user !== undefined) {
			user.data.id = user.id;
			response.user = user.data;
		} 
		res.send(response);
	});
});

/************************************************************************/
/************************************************************************/

// This downloads a photo
app.get('/users/:user_id/photo', function (req, res) {
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, res, "Error downloading photo")) return;
		if (user !== undefined)
			decodeImage(user.data.photo_profile, res);
	});
});


/************************************************************************/
/************************************************************************/

// This create a new user
app.post('/users', function (req, res) {
	var user_data = req.body.user;
	user_data.photo_profile = '';
	db.users.save({data: user_data}, function(err, saved) {
		if (checkForError(err, res, "Error at saving user data")) return;
        if (checkIfUndefined(saved, "User not created")) return;
		res.sendStatus(201);
	});
});

/************************************************************************/
/************************************************************************/

// This modify the data of one user.
app.put('/users/:user_id', function (req, res) {
	var user_data = req.body.user;
	var user_id = req.params.user_id;
	var new_record = {id: user_id, data: user_data};
	db.users.save(new_record, function(err, saved) {
		if (checkForError(err, res, "Error at saving user data")) return;
        if (checkIfUndefined(saved, "User does not exist")) return;
		res.sendStatus(200);
	});
});

/************************************************************************/
/************************************************************************/

// This modify the data of one or more users.
app.put('/users/:user_id/photo', function (req, res) {
	var user_id = req.params.user_id;
	db.users.findOne({id: user_id}, function(err, user) {
		if (checkForError(err, res, "Error at retrieving user data")) return;
		if (checkIfUndefined(user, "User does not exist")) return;
		var userData = user.data;
		userData.photo_profile = req.body.photo;
		db.users.save({id: user_id, data: userData}, function(err, saved){
			if (checkForError(err, res, "Error at saving photo")) return;
			res.sendStatus(200);
		});
	});
});

/************************************************************************/
/************************************************************************/

// This deletes a user.
app.delete('/users/:user_id', function (req, res) {
	db.users.destroy({id: req.params.user_id}, function(err, deleted) {
		if (checkForError(err, res, "Error at deleting user")) return;
        if (checkIfUndefined(deleted, "User does not exist")) return;	
    	res.sendStatus(200);
	});
});

/************************************************************************/
/************************************************************************/

var server = app.listen(port, function () {
	var host = server.address().address;
	var port = server.address().port;
	massive.connect({connectionString : connectionString}, function(err, database){
		if (checkForError(err, "Error connecting to database")) return;
		db = database;
	});
  	console.log("Example app listening at http://%s:%s", host, port);
});
