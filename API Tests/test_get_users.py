import urllib2
import json
import requests

r = requests.get('http://localhost:8081/users')
print r.text

