# -*- coding: utf-8 -*-
import json
import requests
import base64
import db
from users import users
from test_post_user import post_user

correct = 200

def delete_user(user_id):
    r = requests.delete('http://localhost:8081/users/'+str(user_id))
    return r.status_code


def is_correct(response):
    return (correct == response) and (get_count() == 0)

# Assuming that the database is initialy empty
def quick_test():
    delete_all_from_db()    
    response = post_user(users[1])
    print "Post status code", response      
    user_id = get_id_from_db()
    print "User id", user_id
    response = delete_user(user_id)
    print "Delete status code", response
    return is_correct(response)

def get_id_from_db():
    return db.query("""SELECT MAX(id) FROM users""")

def get_count():
    return db.query("""SELECT count(*) FROM users""")

def delete_all_from_db():
    return db.delete_all("""users""")


quick_test()
