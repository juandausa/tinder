# -*- coding: utf-8 -*-
import json
import requests
import db
from test_post_user import post_user
from modified_user import payload as modified
from users import users
#from test_get_user import get_user
# SELECT nextval('users_id_seq')

correct = 200

def put_user(user_id, payload):
    headers = {'content-type': 'application/json'}
    r = requests.put('http://localhost:8081/users/'+str(user_id), data=json.dumps(payload), headers=headers)
    return r.status_code


def is_correct(response):
    return correct == response


# Assuming that the database is initialy empty
def quick_test():
    response = post_user(users[1])
    print "Post status code", response    
    #user = get_user(user_id
    user_id = get_id_from_db()    
    response = put_user(user_id, modified)
    print "Put status code", response
    return is_correct(response)


def get_id_from_db():
    return db.query("""SELECT MAX(id) FROM users""")



quick_test()
