To start, "ncurses" and "nlohmann" libraries must be installed.

Installation:

ncurses (linux): 
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
nlohmann (linux): 
```
sudo apt update
```
```
sudo apt install nlohmann-json3-dev
```

Also, CMake is needed:

CMake (linux):
```
sudo apt update
```
```
sudo apt install cmake
```

After that, go to ScrollShooter folder. In ScrollShooter folder:
```
mkdir build && cd build
cmake ..
cmake --build .
./ScrollShooter
```
