# -*- coding: utf-8 -*-
import json
import requests
import base64


with open("test_img.jpg", "rb") as image_file:
    encoded_string = base64.b64encode(image_file.read())

payload = { 
    "photo":  encoded_string, 
} 

headers = {'content-type': 'application/json'}
r = requests.put('http://localhost:8081/users/2/photo', data=json.dumps(payload), headers=headers)
print r.status_code
