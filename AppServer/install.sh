#!/bin/sh
wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz
tar xf release-1.7.0.tar.gz
cd googletest-release-1.7.0
cmake -DBUILD_SHARED_LIBS=ON .
make
sudo cp -a include/gtest /usr/include
sudo cp -a libgtest_main.so libgtest.so /usr/lib/
sudo ldconfig -v | grep gtest
wget https://github.com/google/glog/archive/v0.3.4.tar.gz
tar xf v0.3.4.tar.gz
cd glog-0.3.4
./configure
make
sudo make install
sudo ldconfig -v | grep glog
