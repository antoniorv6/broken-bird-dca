#!/bin/bash

g++ -o game src/*.cpp -I src/ -I vendor/include/ -L vendor/lib -lraylib -lGL -lm -lpthread -lrt -lX11