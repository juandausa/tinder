var express = require('express');
var bodyParser = require('body-parser');
var massive = require("massive");
var base64 = require('node-base64-image');
var keygen = require('keygen');
var messageParser = require('./js/message_parser')
var app = express();
var db = undefined;

app.use(bodyParser.json({limit: '50mb'})); // for parsing application/json
app.use(bodyParser.urlencoded({limit: '50mb', extended: true})); // for parsing application/x-www-form-urlencoded
var photosPath = 'profile_photos/'

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
})

/************************************************************************/
/************************************************************************/

// This responds with a JSON of users
app.get('/users/:user_id', function (req, res) {
	var response = {};
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, res, "Error at creating new user")) return;
		if (user != undefined) {
			user.data.id = user.id;
			response = {user: user.data, metadata: {version: "0.1"}};
		} 
		res.send(response);
	});
})

/************************************************************************/
/************************************************************************/

// This responds with a JSON of users
app.get('/users/:user_id/photo', function (req, res) {
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, user, res, "Error downloading photo")) return;
		if (user != undefined)
			decodeImage(user.data.photo_profile, res);
	});
})


/************************************************************************/
/************************************************************************/

// This create a new user
app.post('/users', function (req, res) {
	var user_data = req.body.user;
	user_data.photo_profile = '';
	db.users.save({data: user_data}, function(err, saved) {
		if (checkForError(err, saved, res, "Error at saving user data")) return;
		res.sendStatus(201);
	});
})

/************************************************************************/
/************************************************************************/

// This modify the data of one user.
app.put('/users/:user_id', function (req, res) {
	var user_data = req.body.user;
	var user_id = req.params.user_id;
	var new_record = {id: user_id, data: user_data};
	db.users.save(new_record, function(err, saved) {
		if (checkForError(err, saved, res, "Error at saving user data")) return;
		res.sendStatus(200);
	});
})

/************************************************************************/
/************************************************************************/

// This modify the data of one or more users.
app.put('/users/:user_id/photo', function (req, res) {
	var user_id = req.params.user_id;
	db.users.findOne({id: user_id}, function(err, user) {
		if (checkForError(err, user, res, "Error at retrieving user data")) return;
		if (user)
		var userData = user.data;
		userData.photo_profile = req.body.photo;
		db.users.save({id: user_id, data: userData}, function(err, saved){
			if (checkForError(err, saved, res, "Error at saving photo")) return;
			res.sendStatus(200);
		});
	});
})

/************************************************************************/
/************************************************************************/

// This deletes a user.
app.delete('/users/:user_id', function (req, res) {
	db.users.destroy({id: req.params.user_id}, function(err, deleted) {
		if (checkForError(err, res, "Error at deleting user")) return;
		res.sendStatus(200);
	});
	
})

/************************************************************************/
/************************************************************************/

var server = app.listen(8081, function () {
	var host = server.address().address
	var port = server.address().port
	// You can use db for 'database name' running on localhost 
	// or send in everything using 'connectionString' 
	massive.connect({db : "users"}, function(err, database){
		if (checkForError(err, "Error connecting to database")) return;
		db = database;
	});
  	console.log("Example app listening at http://%s:%s", host, port)
})
