import urllib2
import json
import requests
import db
from users import users
from test_post_user import post_user

correct = json.loads(json.dumps(users[1]))

def get_user(user_id):
    r = requests.get('http://localhost:8081/users/'+str(user_id))
    return r.json()

def is_correct(response):
    response = response["user"]
    del response["id"]
    del response["photo_profile"]
    return correct["user"] == response

# Assuming that the database is initialy empty
def quick_test():
    response = post_user(correct)
    print "Post status code", response      
    user_id = get_id_from_db()
    response = get_user(user_id)
    print "User posted", correct
    print "User getted", response
    return is_correct(response)

def get_id_from_db():
    return db.query("""SELECT MAX(id) FROM users""")


quick_test()
