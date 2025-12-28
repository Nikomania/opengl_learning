#!/bin/bash
echo "Compiling project..."
g++ src/glad.c src/main.cpp -Iinclude -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o main

if [[ $? -eq 0 ]]
then
    echo "Compilation completed! Run it with ./main"
else
    echo "Compilation failed!"
fi

