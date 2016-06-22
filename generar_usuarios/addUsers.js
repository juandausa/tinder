const fs = require('fs');
var request = require('request');
var ids = ["1", "2", "3", "4", "5", "6", "7"];
var names = ["Abril", "Jessica", "Sofia", "Mary", "Amanda", "Barbara", "Samantha"];
var alias = ["Abril", "Jessica", "Sofia", "Mary", "Amanda", "Barbara", "Samantha"];
var birthdays  = ["07/22/1991", "05/27/1988", "11/05/1992", "08/05/1994", "09/30/1992", "12/21/1986", "01/22/1998"]
var gender = ["female", "female", "female", "female", "female", "female", "female"];
var filenames = ["girl1.jpeg", "girl2.jpg", "girl3.jpg", "girl4.jpg", "girl5.jpg", "girl6.jpg", "girl7.jpg"];
var distances = [10,10,10,10,10,10,10];
var emails = ["Abril@hotmail.com", "Jessica@hotmail.com", "Sofia@hotmail.com", "Mary@hotmail.com", "Amanda@hotmail.com", "Barbara@hotmail.com", "Samantha@hotmail.com"];


var photos = [
    "http://66.media.tumblr.com/933936c4b299a196d1e61e4edc243193/tumblr_mvesjszpd61r00u9co1_540.jpg",
    "https://pbs.twimg.com/profile_images/635004209830559744/J2zsh4DW.jpg",
    "https://pbs.twimg.com/profile_images/449986528878419968/FuQ9ienw.jpeg",
    "http://s1.favim.com/orig/150608/girls-tumblr-instagirls-instagram-girls-Favim.com-2802070.jpg",
    "http://static.tumblr.com/pa3kh3c/pkIlytxqw/asdfhjkl.jpg",
    "http://66.media.tumblr.com/84d982c883aa3ff654e6fa7ee7011fba/tumblr_mu00wgk2zN1rz6rffo1_1280.jpg",
    "http://static.tumblr.com/8b42073d6cafba61694b1aef56375e4f/axlgwmc/L9sne9wcw/tumblr_static_54fuho9gbg4cok0g0s0wkcs0c.jpg"
];


var location = {
        "latitude" : -34.780884,
        "logitude" : -58.395260 
    };


var movies = {"movies": ["Primer", "Dead Poets Society"]};
var music = {"music" : ["Alter Bridge"]};
var likes = {"likes" : ["Chandler Bing"]};
var games = {"games" : ["Crysis", "Mass Effect"]}
var books = {"books" : ["El hobbit"]};
var television = {"television" : ["Supernatural"]};



function set_interests() {
    var user_interests = {};
    user_interests.movies = ["Primer", "Dead Poets Society"];
    user_interests.gender = "male";
    return user_interests;
}

var interests = set_interests();
var json_candidates = {};
var candidates = [];

//https://enigmatic-scrubland-75073.herokuapp.com

function sendCandidate(candidates, i, callback) {
    setTimeout(function() {
        if (i >= 6) return;    
        request({
            url: 'http://localhost:8000/register',
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },            
            json: candidates[i]
        }, function(error, response, body){
            if(error) {
                console.log(error);
            } else {
                console.log(response.statusCode);
                callback(candidates, i+1, callback);
            }
        });
    console.log("sent");
    }, 2000);
}


setTimeout(function() {
    for (var i = 0; i < 6; i++) {
       var candidate = {};
        candidate.user_id = ids[i]
        candidate.name = names[i];
        candidate.birthday = birthdays[i];
        candidate.gender = gender[i];
        candidate.email = emails[i]
        candidate.alias = alias[i];
        candidate.interests = interests;
        candidate.photo_profile = photos[i];        
        candidate.location = location;
        candidate.discovering_distance = distances[i];
        console.log(interests);
        candidates.push(candidate);           
    }    
    sendCandidate(candidates, 0, sendCandidate);
}, 2000);



