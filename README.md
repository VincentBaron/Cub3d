# Cub3d
## Project overview

This project aimed at creating a 3D game using [raycasting](https://en.wikipedia.org/wiki/Ray_casting).

For this project, we had to parse a map.cub file (see below).

```
NO  ./textures/eagle.xpm

SO  ./textures/blue.xpm

WE ./textures/wood.xpm

S  ./textures/barrel.xpm

EA ./textures/eagle.xpm

C 30,30,30

F 0,0,0

11111111111111111111111111111
10000000000000000000000000001
10000000000000000000000000001
1000000110000000000011000001
10000001100000002000011000001
10000000000000000000000000001
10000000000200000200000000001
10000000000000000000000000001
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10001000000000000000000000001
10000000000000000001010000101
11000001110101011111011110001
11110111 1110101 101111010N01
11111111 1111111 111111111111
```

- NO, SO, WE, S, EA are the textures depending on the wall orientation.
- C and F are the Ceiling and Floor textures.
- The map has to be surrounded by 1 representing walls. 0 represent the floor. The orginal position of the player is 'N' meanig it should spawn facing North. But 'S', 'W', 'E' can also be used for other spawning orientations (South, West, East).

Below is an image representing what the game rendered in 3D should look like:

![Alt text](./3dexample.jpg?raw=true "Optional Title")

## What I learned

1. Raycasting technique.
2. Deep understanding of the graphic mlx library.
3. Math algorithms to project the 2d map into a 3D image.
4. Structuring my code efficiently.
5. Debugging.
6. implementing .xpm files for textures.
7. File parsing.
8. Error management.
