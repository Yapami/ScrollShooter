# ScrollShooter
## To start, "git", "g++", "cmake", "ncurses" and "nlohmann" libraries must be installed.

Installation:

### Linux:

ncurses:
```
sudo apt update
```
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
nlohmann: 
```
sudo apt install nlohmann-json3-dev
```
g++:
```
sudo apt install g++
```
git:
```
sudo apt install git
```
CMake:
```
sudo apt update
```
```
sudo apt install cmake
```

### MacOS:

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
brew install cmake
```
g++:
```
brew install g++
```
git:
```
brew install git
```

### Windows:
1. open PowerShell as administrator
2. in PowerShell:
```
wsl --install
```

3. reboot your computer

4. Open the "Start" menu and find Ubuntu (if Ubuntu did not start automatically after computer reboot)

5. Enter any name in the terminal

6. Enter password

7. Then, call all commands above in order:

git:
```
sudo apt update
```
```
sudo apt install git
```
g++:
```
sudo apt install g++
```
ncurses:
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
nlohmann: 
```
sudo apt install nlohmann-json3-dev
```
cmake:
```
sudo apt install cmake
```


## After all preparation actions on any system:
```
git clone https://github.com/Yapami/ScrollShooter.git
```
```
cd ScrollShooter/
```
```
mkdir build && cd build
```
```
cmake ..
```
```
cmake --build .
```
```
./ScrollShooter
```



## Base inputs in the game:

  '->': move right

  '<-': move left

  ' ': shoot

  'q': quit

  'r': restart game after finish

### Balance rules can be changed in config/config.json

