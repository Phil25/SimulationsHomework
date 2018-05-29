#!/bin/bash

g++ ../psm_window.cpp ./matrix.cpp ./heat.cpp -std=c++11 -lGL -lGLU -lglut -o heat
