# -*- coding: utf-8 -*-
import base64

with open("test_img_2.jpg", "rb") as image_file:
    encoded_string = base64.b64encode(image_file.read())

payload = { 
    "user": { 
        "id": 2, 
        "name": "nuevo usuario", 
        "alias": "a user", 
        "email": "nuevo_usuario@usuario.com", 
        "photo_profile": encoded_string, 
        "interests": [{ 
            "category": "music / band", 
            "value": "velvet revolver" 
        }, { 
            "category": "music / band", 
            "value": "guns n roses" 
        }, { 
            "category": "sport", 
            "value": "basket"  
        }], 
        "location": {  
            "latitude": 222.2222, 
            "longitude": 11.1111
        } 
    }, 
    "metadata": { 
        "version": "0.1" 
    } 
} 

