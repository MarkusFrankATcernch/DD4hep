#!/bin/bash

source /cvmfs/sft.cern.ch/lcg/views/LCG_98python3/x86_64-centos7-gcc10-opt/setup.sh

cd /Package
mkdir build
cd build
cmake -DDD4HEP_USE_GEANT4=ON -DBoost_NO_BOOST_CMAKE=ON -DDD4HEP_USE_LCIO=ON -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-fdiagnostics-color=always" -DCMAKE_CXX_STANDARD=17 ..
export PATH=/cov-analysis-linux64/bin:$PATH
cov-build --dir cov-int make -j4
tar czvf myproject.tgz cov-int
