# minesweeper
Light version of [Microsoft Minesweeper](https://en.wikipedia.org/wiki/Microsoft_Minesweeper) for Linux. Some interesting implementation moments are described [here](https://rdiachenko.blogspot.com/2016/10/minesweeper-for-linux-just-for-fun.html).

1. [Required dependencies](https://github.com/rdiachenko/minesweeper#required-dependencies)
2. [Build and install](https://github.com/rdiachenko/minesweeper#build-and-install)
3. [Launch](https://github.com/rdiachenko/minesweeper#launch)
4. [Launch with default configuration](https://github.com/rdiachenko/minesweeper#launch-with-default-configuration)
5. [Launch with custom configuration](https://github.com/rdiachenko/minesweeper#launch-with-custom-configuration)
  1. [Classic style](https://github.com/rdiachenko/minesweeper#classic-style)
  2. [RD style](https://github.com/rdiachenko/minesweeper#rd-style)

## Required dependencies
* SDL2
* SDL2_image
```
# E.g.: installation for Ubuntu 2x.xx
apt-get install libsdl2-dev libsdl2-image-dev -y
```

## Build and install
```
minesweeper]$ mkdir build && cd build
minesweeper]$ cmake .. -DCMAKE_CXX_STANDARD=17
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

![](https://raw.githubusercontent.com/rdiachenko/minesweeper/master/screenshots/rd-lose.png)

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
