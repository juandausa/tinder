#!/bin/sh
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/database/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/resources/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/server/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/server/Controllers/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/server/Services/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/utils/*
./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/main/*
exit 0