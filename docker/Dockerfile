# This is a comment
FROM ubuntu:14.04
RUN apt-get update -y
RUN sudo apt-get install zlib1g-dev libbz2-dev libsnappy-dev wget cmake libpthread-stubs0-dev -y
RUN sudo apt-get install build-essential python -y
RUN wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz \
&& tar xf release-1.7.0.tar.gz \
&& cd googletest-release-1.7.0 \
&& cmake -DBUILD_SHARED_LIBS=ON . \
&& make \
&& sudo cp -a include/gtest /usr/include \
&& sudo cp -a libgtest_main.so libgtest.so /usr/lib/ \
&& sudo ldconfig -v | grep gtest \
&& cd ..
RUN wget https://github.com/google/glog/archive/v0.3.4.tar.gz \
&& tar xf v0.3.4.tar.gz \
&& cd glog-0.3.4 \
&& ./configure \
&& make \
&& sudo make install \
&& sudo ldconfig -v | grep glog \
&& cd ..
RUN wget https://github.com/schuhschuh/gflags/archive/v2.1.2.tar.gz \
&& tar xf v2.1.2.tar.gz \
&& cd gflags-2.1.2/ \
&& cmake . \
&& make \
&& sudo make install \
&& sudo ldconfig -v \
&& cd ..
RUN wget https://github.com/facebook/rocksdb/archive/rocksdb-4.3.1.tar.gz \
&& tar xf rocksdb-4.3.1.tar.gz \
&& cd rocksdb-rocksdb-4.3.1/ \
&& make static_lib \
&& sudo make install \
&& sudo ldconfig -v \
&& cd ..
RUN sudo apt-get install libssl-dev -y
RUN wget https://github.com/curl/curl/archive/curl-7_48_0.tar.gz \
&& tar xf curl-7_48_0.tar.gz \
&& cd curl-curl-7_48_0/ \
&& cmake . \
&& make \
&& sudo make install \
&& sudo ldconfig -v \
&& cd ..
RUN sudo apt-get install git valgrind lcov -y
