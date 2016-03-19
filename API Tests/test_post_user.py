# -*- coding: utf-8 -*-
import json
import urllib2

data = {
        "user": { 
            "name": "usuario", 
            "alias": "not a user", 
            "email": "usuario@usuario.com", 
            "interests": [{ 
                "category": "music/band", 
                "value": "radiohead" 
            }, { 
                "category": "music/band", 
                "value": "pearl jam" 
            },{ 
                "category": "outdoors", 
                "value": "running" 
            }],
            "location": {
                "latitude": 121.45356,
                "longitude": 46.51119 
            } 
        } 
    }

req = urllib2.Request('http://localhost:8081/users')
req.add_header('Content-Type', 'application/json')
response = urllib2.urlopen(req, json.dumps(data))
