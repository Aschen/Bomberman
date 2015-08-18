# Bomberman

Epitech project : We have to make a clone of Bomberman. We decided to make it multiplayer :)

## How to
* First install dependencies : apt-get install clang libsdl2-dev libgles2-mesa libgl1-mesa-glx
* Compile : make
* Add custom library path in env : . config.sh
* Launch a bomberman server : ./bomberman server players port
* Join the game : ./bomberman client server_ip server_port (The game don't start until all players are connected.)

## Feature
* Multiplayer game
* Basic bomberman, no live, no item
* Auto-generated map with crate and wall

## Example
* . config.sh
* ./bomberman server 1 4242 (Start a server on port 4242)
* ./bomberman client 127.0.0.1 4242 (On other terminal, don't forget to add custom library in path : . config.sh)
![alt text](https://github.com/Aschen/Bomberman/raw/master/screenshot.png "bomb_blast.so")
