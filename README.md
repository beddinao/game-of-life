# *`GAME-OF-LIFE`*

## <a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">About</a>

## Controls
- **Zoom:** use the `MOUSE WHEEL` to zoom in or out.
- **Navigate World:** press the `MOUSE RIGHT KEY` and drag around.
- **Generation speed:** press `UP` or `DOWN` to change how many frames a single generation take.

## Usage

```
$ gol [path to a valid RLE file]
               - a library of more than 4700 seeds under the ./seeds directory
               - default is a random seed
```

## Requirements
- **`Linux or Macos`**
- **`glfw (libglfw3-dev)`**
- **`cmake >= 3.18`**

## Examples
```
 ./gol
```
<img src="https://github.com/user-attachments/assets/3f954569-bc1c-421b-9f70-78dcf56d59f1" alt="random" width="100%" align="center"></img>

```
 ./gol seeds/movingsawtooth.rle
```
<img src="https://github.com/user-attachments/assets/846af648-10c7-4fb8-b5e7-6d7549474aba" alt="movingsawtooth" width="100%" align="center" ></img>

```
 ./gol seeds/spacefiller1.rle
```
<img src="https://github.com/user-attachments/assets/1119dbb3-3985-4b28-a68e-d3480367e215" alt="spacefiller" width="100%" align="center"></img>
