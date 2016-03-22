# -*- coding: utf-8 -*-
import json
import requests
import base64
import db
from users import users
from test_post_user import post_user


correct = 200

with open("test_img.jpg", "rb") as image_file:
    encoded_string = base64.b64encode(image_file.read())

payload = { 
    "photo":  encoded_string, 
} 

def put_photo(user_id):
    headers = {'content-type': 'application/json'}
    r = requests.put('http://localhost:8081/users/'+str(user_id)+'/photo', data=json.dumps(payload), headers=headers)
    return r.status_code


def is_correct(response):
    return correct == response


# Assuming that the database is initialy empty
def quick_test():
    response = post_user(users[1])
    print "Post status code", response    
    user_id = get_id_from_db()   
    print user_id 
    response = put_photo(user_id)
    print "Put status code", response
    return is_correct(response)


def get_id_from_db():
    return db.query("""SELECT MAX(id) FROM users""")



quick_test()
