#!/bin/sh
sudo docker build -t g6tinder/appserver ./docker
sudo docker run -v AppServer:/root/AppServer -ti g6tinder/appserver
