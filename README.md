## wolf3d

A Hive graphics project, where you create a program that allows the user to move inside a maze similar to the 1992 game Wolfenstein 3D.
- A project with a team of 2 students.
- The project has to be done in C and respecting the 42 school norm (formatting rules).
- The basic functionalities of a graphics library such as SDL2 may be used (to open a window, copy a frame_buffer to window, etc.).
- Allowed C functions are: write, read, open, close, malloc, free, exit, strerror, perror.
<p align="left">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_editor_sky.png" width="49%" height="45%">
</p>

## Deployment

To deploy this project run:

```bash
  git clone git@github.com:jhakonie/wolf3d.git wolf3d
  cd wolf3d
  make
```
SDL2 is included as sources in the root of the repository in a directory called libsdl2.
The Makefile will install it in the root of the repository. SDL2 can be deleted with 'make fclean'.

## Usage

```
To edit maps, run the editor with the name of the directory,
that contains assets of the level, for example 'test':

    ./wolf3d_editor test

To run the server:

    ./wolf3d_server

To run clients (up to 4) in default level:

    ./wolf3d
    
To run clients in a specific level:

   ./wolf3d <directory_name>
   
The server must be up for clients to be able to move.
```
## Features
- The textures and the map are loaded from the directory named, when running the program.
   If the directory doesn't exist, it is created and populated with an empty map, textures are then loaded from the 'default' directory.
- In the editor the player is drawn as a pink triangle pointing where the player is facing and can be moved with wasd
or by moving the player spawn block, which can be selected from the toolbar on the left.
- Space shifts between 2.5d view and 2d map.
- It's possible to place and remove doors and walls, move the player around and save the changes.
- Rays can be shown by pressing R:
green ones hit the walls, purple ones indicate doors.

<p align="left">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_editor.png" width="30%" height="30%">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_editor_2.5d_view.png" width="30%" height="30%">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_editor_showing_rays.png" width="30%" height="30%">
</p>

- Map format is a simple text file: 1 = wall, . = floor, 2 = door.
- Wall collision can be turned off with C.
- There are doors, that slide open when you move near them.
- It's possible to look sideways, up and down by moving the mouse when in 2.5d mode and arrow keys in 2d mode.
- There's a skybox.
- Light is shaded based on distance.

<p align="left">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_editor_looking_up.png" width="30%" height="30%">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_editor_door_open_2.5d.png" width="30%" height="30%">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_lookdown.png" width="30%" height="30%">
</p>

- It's possible to have up to 4 players that are controlled by an authoritative server.
- Raycasting mode shows other players as a black box, with one of the skybox textures on the sides (chosen based on order of entrance).
- 3d mode shows other players as an object made of triangles.

<p align="left">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_client_2_players_2.5d.png" width="45%" height="40%">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_client_2_players_3d.png" width="45%" height="40%">
</p>
<p align="left">
  <img src="https://github.com/jhakonie/wolf3d/blob/main/screenshots/wolf3d_client_4_players.png" width="60%" height="60%">
</p>



## Authors

I worked on this project with another student, who prefers not to be named.
We divided the project into the mandatory part and bonuses.
I completed the mandatory raycaster, an xpm-reader and a map editor.
My team member created a 3d engine and our client/server programs.

## Research for raycasting and SDL2

 - [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting2.html)
 - [Permadi: Ray-Casting Tutorial For Game Development And Other Purposes](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
 - [SDL2](https://www.libsdl.org/)
 
## License

[GNU AGPLv3](https://choosealicense.com/licenses/agpl-3.0/)

