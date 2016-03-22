import urllib2
import json
import requests

empty = json.loads("""{ 
        "users": [], 
        "metadata": { 
            "version": "0.1", 
            "count": 0 
        } 
    }""")


def get_users():
    r = requests.get('http://localhost:8081/users')
    return json.loads(r.text)

def is_empty(response):
    return empty == response

def quick_test():
    response = get_users()
    print "Users", response
    return is_empty(response)


quick_test()
