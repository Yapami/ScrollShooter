To start, "ncurses" and "nlohmann" libraries must be installed.

Installation:

Linux:

ncurses: 
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
nlohmann: 
```
sudo apt update
```
```
sudo apt install nlohmann-json3-dev
```

Also, CMake is needed:

CMake:
```
sudo apt update
```
```
sudo apt install cmake
```

MacOS:

Firstly Brew must be installed:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
ncurses:
```
brew install libvncserver
```
nlohmann: 
```
brew install nlohmann-json
```
CMake:
```
brew install  cmake
```


After that, go to ScrollShooter folder. In ScrollShooter folder:
```
mkdir build && cd build
cmake ..
cmake --build .
./ScrollShooter
```
