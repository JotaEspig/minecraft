# Minecraft
Minecraft clone written in C++ and using Axolote Engine with OpenGL

## Dependencies
* CMake
* OpenGL
* GLM
* GLFW3
* Doxygen (Optional)
* Axolote Engine. See [https://github.com/JotaEspig/axolote-engine](https://github.com/JotaEspig/axolote-engine) 

## Compiling
```bash
git clone https://github.com/JotaEspig/minecraft.git
cd minecraft
cmake .
make -j4
```
You need to install [Axolote Engine](https://github.com/JotaEspig/axolote-engine) to run it.
```bash
chmod +x install_axolote.sh
./install_axolote.sh
```

## Running
After compiling
```bash
./bin/minecraft
```
