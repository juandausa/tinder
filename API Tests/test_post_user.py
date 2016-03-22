# -*- coding: utf-8 -*-
import json
import urllib2
from users import users

correct = 201

def post_user(data):
    req = urllib2.Request('http://localhost:8081/users')
    req.add_header('Content-Type', 'application/json')
    response = urllib2.urlopen(req, json.dumps(data))
    return response.getcode()


def is_correct(response):
    return correct == response


def quick_test():
    response = post_user(users[1])
    print "Status code", response
    return is_correct(response)




quick_test()
