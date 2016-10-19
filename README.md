# minesweeper
Light version of [Microsoft Minesweeper](https://en.wikipedia.org/wiki/Microsoft_Minesweeper) for Linux

## Required dependencies
* SDL2
* SDL2_image
```
# E.g.: for Fedora 24

$ sudo dnf install SDL2 SDL2-devel SDL2_image SDL2_image-devel
```

## Build and installation
```
minesweeper]$ mkdir build && cd build
minesweeper]$ cmake ../
minesweeper]$ make
minesweeper]$ make install

# after completion minesweeper should be installed in minesweeper/release folder
```

## Launch
```
release]$ ./minesweeper [path to config]
```

## Launch with default configuration
```
# default configuration
release]$ cat resources/classic.conf 
mines=99
field_rows=16
field_cols=30
sprite_img=resources/classic.png
sprite_txt=resources/classic.txt

# launch
release]$ ./minesweeper
```
![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/classic-in-progress.png)

![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/classic-lose.png)

## Launch with custom configuration
### Classic style
```
# custom configuration
release]$ cat resources/classic.conf 
mines=10
field_rows=10
field_cols=10
sprite_img=resources/classic.png
sprite_txt=resources/classic.txt

# launch
release]$ ./minesweeper resources/classic.conf
```
![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/classic-win.png)

### RD style
```
# custom configuration
release]$ cat resources/rd.conf 
mines=99
field_rows=16
field_cols=30
sprite_img=resources/rd.png
sprite_txt=resources/rd.txt

# launch
release]$ ./minesweeper resources/rd.conf
```
![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/rd-in-progress.png)

![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/rd-in-lose.png)

```
# custom configuration
release]$ cat resources/rd.conf
mines=7
field_rows=7
field_cols=14
sprite_img=resources/rd.png
sprite_txt=resources/rd.txt

# launch
release]$ ./minesweeper resources/rd.conf
```
![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/rd-win.png)
