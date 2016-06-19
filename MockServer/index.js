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

/*************************************************************************************/
/*************************************************************************************/

app.get('/', function(request, response) {
  console.log(request.body);
  response.render('pages/index');
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/register/', function(request, response) {
  console.log(request.body);
  response.send({status_code:200});
});

/*************************************************************************************/
/*************************************************************************************/

app.get('/login/:user_id', function(request, response) {
  console.log(request.params.user_id);
  response.sendStatus(200); //304
});

/*************************************************************************************/
/*************************************************************************************/

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

/*************************************************************************************/
/*************************************************************************************/

app.get('/candidates/:user_id', function(request, response) {

    console.log("Enviando candidatos");
    var path = __dirname + '/profile1.jpg',
              options = {localFile: true, string: true};


    var image2 = undefined;     
    base64.base64encoder(path, options, function (err, image) {  
        if (err) { console.log(err); }  
        var profile1 = image;

        var path = __dirname + '/profile2.jpg',
        options = {localFile: true, string: true};
        base64.base64encoder(path, options, function (err, image) {  
            if (err) { console.log(err); }  
            profile2 = image;
            
            var candidates = {
                    "candidates": [
                    {
                        "user_id": "111",
                        "alias": "Vicky",
                        "age": 23,
                        "photo_profile": profile1,
                        "interests" : ["Florence and the machine", "Adele", "Hockey", "Antes del amanecer", "El túnel"]
	                },{
	                    "user_id": "222",
                        "alias": "Mimi",
                        "age": 24, 
                        "photo_profile": profile2,
                        "interests" : ["La historia de Lisey", "Flash", "Correr", "Batman v Superman"]
                    }]
                };
            response.send(candidates);
            console.log("Candidatos enviados");
        });
    });
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/user/update/:user_id', function(request, response) {
  console.log(request.body);
  response.send({status_code:200});
});

/*************************************************************************************/
/*************************************************************************************/

app.get('/matches/:user_id', function(request, response) {

    console.log("Enviando matches");
    var path = __dirname + '/profile1.jpg',
              options = {localFile: true, string: true};


    var image2 = undefined;     
    base64.base64encoder(path, options, function (err, image) {  
        if (err) { console.log(err); }  
        var profile1 = image;

        var path = __dirname + '/profile2.jpg',
        options = {localFile: true, string: true};
        base64.base64encoder(path, options, function (err, image) {  
            if (err) { console.log(err); }  
            profile2 = image;
            
            var matches = {
                    "matches": [
                    {
                        "user_id": "111",
                        "alias": "Vicky",
                        "age": 23,
                        "photo_profile": profile1,
                        "interests" : ["Florence and the machine", "Adele", "Hockey", "Antes del amanecer", "El túnel"],
                        "messages": [{"0": "hola"}, {"1": "como andas?"}, {"0": "todo bien, vos?"}, {"1": "tambien"}]
	                 },{
	                    "user_id": "222",
                        "alias": "Mimi",
                        "age": 24, 
                        "photo_profile": profile2,
                        "interests" : ["La historia de Lisey", "Flash", "Correr", "Batman v Superman"],
                        "messages": [{"0": "hola, vi que te gustan varios libros que a mi tambien"}, {"1": "mira vos, cuales?"}, {"0": "yy por ejemplo, 'La historia de Lisey'"}, {"1": "siii, tremendo libro"}]
                    }]
                };
            response.send(matches);
            console.log("Candidatos matches");
        });
    });
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/filters/:user_id', function(request, response) {
  console.log(request.body);
  response.send({status_code:200});
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/dislikes/:user_id', function(request, response) {
  console.log("Dislike a", request.body.to_user_id);
  response.send({status_code:200});
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/likes/:user_id', function(request, response) {
  console.log("Like a", request.body.to_user_id);
  response.send({status_code:200});
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/sendmessage/:user_id', function(request, response) {
  console.log("Mensaje enviado", request.body.message);
  response.send({status_code:200});
});

/*************************************************************************************/
/*************************************************************************************/

app.post('/getmessage/:user_id', function(request, response) {
  console.log("Mensaje recibido");
  response.send({message:"hola"});
});

/*************************************************************************************/
/*************************************************************************************/

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});
