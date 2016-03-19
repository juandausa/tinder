# -*- coding: utf-8 -*-
import json
import requests
import base64

r = requests.delete('http://localhost:8081/users/2')
print r.status_code
