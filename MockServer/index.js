var express = require('express');
var app = express();
var base64 = require('node-base64-image');
var bodyParser = require('body-parser');

app.use(bodyParser.json({limit: '50mb'})); // for parsing application/json
app.use(bodyParser.urlencoded({limit: '50mb', extended: true})); // for parsing application/x-www-form-urlencoded

app.set('port', (process.env.PORT || 5000));

app.use(express.static(__dirname + '/public'));

// views is directory for all template files
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');

app.get('/', function(request, response) {
  console.log(request.body);
  response.render('pages/index');
});


app.post('/register/', function(request, response) {
  console.log(request.body);
  response.send({status_code:200});
});

app.get('/login/:user_id', function(request, response) {
  console.log(request.params.user_id);
  response.sendStatus(200); //304
});


app.get('/user/:user_id', function(request, response) {

    console.log("Enviando perfil");
    var path = __dirname + '/profile.jpg',
              options = {localFile: true, string: true};


    var image2 = undefined;     
    base64.base64encoder(path, options, function (err, image) {  
        if (err) { console.log(err); }  
        var image1 = image;
   
        var candidates = {
            "user_id": "111",
            "name": "nombre",
            "email": "usuario@usuario.com",
            "alias": "usuario1",
            "gender": "Hombre",
            "age": 23,
            "photo_profile": image1,
            "interests" : ["velvet revolver", "racing", "basquet", "programaciónnnnnnnnnnnnnnnnnnnnn", "lalal"]
        };
        response.send(candidates);
        console.log("Perfil enviado");
    });
});






app.get('/candidates/:user_id', function(request, response) {

    console.log("Enviando candidatos");
    var path = __dirname + '/profile.jpg',
              options = {localFile: true, string: true};


    var image2 = undefined;     
    base64.base64encoder(path, options, function (err, image) {  
        if (err) { console.log(err); }  
        var image1 = image;

        var path = __dirname + '/homer.jpg',
        options = {localFile: true, string: true};
        base64.base64encoder(path, options, function (err, image) {  
            if (err) { console.log(err); }  
            image2 = image;
            
            var candidates = {
                    "candidates": [
                    {
                        "user_id": "111",
                        "alias": "usuario1",
                        "age": 23,
                        "photo_profile": image1,
                        "interests" : ["velvet revolver", "racing", "basquet", "programaciónnnnnnnnnnnnnnnnnnnnn", "lalal"]
	                 },{
	                    "user_id": "222",
                        "alias": "usuario2",
                        "age": 24, 
                        "photo_profile": image2,
                        "interests" : ["d'oh", "donuts", "beer", "boobies"]
                    }]
                };
            response.send(candidates);
            console.log("Candidatos enviados");
        });
    });
});



app.post('/user/update/:user_id', function(request, response) {
  console.log(request.body);
  response.send({status_code:200});
});

app.post('/filters/:user_id', function(request, response) {
  console.log(request.body);
  response.send({status_code:200});
});

app.post('/dislikes/:user_id', function(request, response) {
  console.log("Dislike a", request.body.to_user_id);
  response.send({status_code:200});
});


app.post('/likes/:user_id', function(request, response) {
  console.log("Like a", request.body.to_user_id);
  response.send({status_code:200});
});




app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});


