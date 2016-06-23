var express = require('express');
var bodyParser = require('body-parser');
var massive = require("massive");
var base64 = require('node-base64-image');
var keygen = require('keygen');
var app = express();
var config = require('./config.json');
var localhostString = "postgres://"+config.postgres.user+":"+config.postgres.password+"@"+config.postgres.host+"/"+config.postgres.db;
var port = (process.env.PORT || 5000); // config.express.port
var connectionString = (process.env.DATABASE_URL || localhostString);
var db;
var url = config.url;

app.use(bodyParser.json({limit: '50mb'})); // for parsing application/json
app.use(bodyParser.urlencoded({limit: '50mb', extended: true})); // for parsing application/x-www-form-urlencoded
app.use(express.static(__dirname + '/shared-app'));

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

function getMetadata(collection) {
	var metadata = {version: config.version};
	if (collection !== null) {
		metadata.count = collection.length;
	}
	return metadata;
}

/************************************************************************/
/***************				RESTFUL API				*****************/
/************************************************************************/

// Enable CORS (Cross-over Origins)
app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Methods", "POST, GET, PUT, DELETE, OPTIONS");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

/************************************************************************/
/************************************************************************/

// This responds OK for Heroku badges
app.get('/', function (req, res) {
    res.sendFile('index.html');
});

/************************************************************************/
/************************************************************************/

// This responds with a JSON of interests
app.get('/interests', function (req, res) {
	var response = {interests: []};
	db.run("select * from interests", function(err, interests) { 
		if (checkForError(err, res, "Error at creating new interest")) return;
		for (i = 0; i < interests.length; i++) {
			response.interests.push(interests[i].data);
		}
		response.metadata = getMetadata(interests);
		res.send(response);
	});
});

/************************************************************************/
/************************************************************************/

// This responds with a JSON of users
app.get('/users', function (req, res) {
	var response = {users: []};
	db.run("select * from users", function(err, users) { 
		if (checkForError(err, res, "Error at creating new user")) return;
		for (i = 0; i < users.length; i++) {
			var data = users[i].data;
			data.id = users[i].id;
			data.photo_profile = url + "/users/"+ String(data.id) + "/photo"
			response.users.push({user: data});
		}
		response.metadata = getMetadata(users);
		res.send(response);
	});
});

/************************************************************************/
/************************************************************************/

// This responds with a JSON of users
app.get('/users/:user_id', function (req, res) {
	var response = {};
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, res, "Error at creating new user")) return;
        if (user !== undefined) {
			user.data.id = user.id;
			response.user = user.data;
		}
		response.metadata = getMetadata(null);
		res.send(response);
	});
});

/************************************************************************/
/************************************************************************/

// This downloads a photo
/*app.get('/users/:user_id/photo', function (req, res) {
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, res, "Error downloading photo")) return;
		if (user !== undefined) {
			var data = user.data.photo_profile;
			var imageData = new Buffer(data, 'base64');
			res.statusCode = 200;
			res.setHeader('Content-Type', 'image/jpg');
			res.end(imageData, 'binary');
		}	
	});
});*/

app.get('/users/:user_id/photo', function (req, res) {
	db.users.findOne({id: req.params.user_id}, function(err, user) { 
		if (checkForError(err, res, "Error sending photo")) return;
		if (user !== undefined) {
			var data = user.data.photo_profile;
			res.send(data);
		}	
	});
});
/************************************************************************/
/************************************************************************/

// This create a new user
app.post('/users', function (req, res) {
	var response = {};
	var user_data = req.body.user;
    console.log(req.body);
	user_data.photo_profile = '';
	db.users.save({data: user_data}, function(err, saved) {
		if (checkForError(err, res, "Error at saving user data")) return;
        if (checkIfUndefined(saved, "User not created")) return;
		saved.data.id = saved.id;
		response.user = saved.data;
		response.metadata = getMetadata(null);
        res.status(201).send(response);
	});
});

/************************************************************************/
/************************************************************************/

// This create a new user
app.post('/interests', function (req, res) {
	var interest_data = req.body.interest;
	console.log(interest_data.value);
	db.run("select count(*) from interests where data->>'category' = '" +
		String(interest_data.category) + "' and data->>'value' = '" +
		String(interest_data.value) + "'", function(err, found) {
		console.log("Count founded", found);
		if ((found !== undefined) && (found !== null)) {
			var count = found[0].count;
			if (count > 0) {
				res.sendStatus(304);
				return;
			}
		}
		db.interests.save({data: interest_data}, function(err, saved) {
			if (checkForError(err, res, "Error at saving interest data")) return;
	        if (checkIfUndefined(saved, "interest not created")) return;
			res.sendStatus(201);
		});
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
