# Particlez
Here is my terrible, horrible C code for this fun little toy project.

# Building
I, annoyingly to everyone else, used my own custom-built build system to work on this project. Here's a simple
terminal command you can use to build it yourself;

### Windows (PowerShell)
WARNING!!! You may need to compile the Raylib library yourself if you are using an ARM machine- It's easy tho I believe in you.

`gcc ./src/*.c -I./inc -L./libs -Wall -O2 -static -mwindows -lraylib -lgdi32 -lopengl32 -lwinmm -o Particlez.exe`

### Linux (may also just work on MacOS)
Please note that you must have Raylib installed as a shared library on your system- make sure to grab it with
whatever package manager you use.

`gcc ./src/*.c -I./inc -Wall -O2 -lraylib -lm -o Particlez`


### Happy developing!
