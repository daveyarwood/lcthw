#!/bin/bash

set -e

# go somewhere safe
cd /tmp

# get the source for base APR 1.4.6
curl -L -O http://archive.apache.org/dist/apr/apr-1.4.6.tar.gz

# extract it and go into the source
tar -xzvf apr-1.4.6.tar.gz
cd apr-1.4.6

# build APR from source
./configure
make
sudo make install

# reset and cleanup
cd /tmp
rm -rf apr-1.4.6 apr-1.4.6.tar.gz

# get the source for apr-util 1.4.1
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.4.1.tar.gz

# extract
tar -xzvf apr-util-1.4.1.tar.gz
cd apr-util-1.4.1

# build from source
./configure --with-apr=/usr/local/apr
make
sudo make install

# cleanup
cd /tmp
rm -rf apr-util-1.4.1* apr-1.4.6*
