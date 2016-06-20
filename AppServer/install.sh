#!/bin/sh
sudo apt-get install zlib1g-dev libbz2-dev libsnappy-dev
wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz
tar xf release-1.7.0.tar.gz
cd googletest-release-1.7.0
cmake -DBUILD_SHARED_LIBS=ON .
make
sudo cp -a include/gtest /usr/include
sudo cp -a libgtest_main.so libgtest.so /usr/lib/
sudo ldconfig -v | grep gtest
cd ..
wget https://github.com/google/glog/archive/v0.3.4.tar.gz
tar xf v0.3.4.tar.gz
cd glog-0.3.4
./configure
make
sudo make install
sudo ldconfig -v | grep glog
cd ..
# # Install gflags-
wget https://github.com/schuhschuh/gflags/archive/v2.1.2.tar.gz
tar xf v2.1.2.tar.gz
cd gflags-2.1.2/
cmake .
make
sudo make install
sudo ldconfig -v
cd ..
# # Install rocksdb
wget https://github.com/facebook/rocksdb/archive/rocksdb-4.3.1.tar.gz
tar xf rocksdb-4.3.1.tar.gz
cd rocksdb-rocksdb-4.3.1/
make static_lib
sudo make install
sudo ldconfig -v
cd ..
# # Install curl
wget https://curl.haxx.se/download/curl-7.48.0.tar.gz
tar xf curl-7.48.0.tar.gz
cd curl-7.48.0
./configure
make
sudo make install
cd ..
# Install jsoncpp
sudo apt-get install -y  libjsoncpp-dev
