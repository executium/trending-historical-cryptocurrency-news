# Prerequisites

- VS 2017+
- cmake 2.8.0+

# Installations

- Install 'Win64 OpenSSL v1.1.1g' using : https://slproweb.com/products/Win32OpenSSL.html

# Build Visual Studio Solution Using CMake
- open cmd in 'cpp_app' directory
- mkdir build
- cd build
- cmake -A x64 ..

# Open Visual Studio Solution
![](./Screenshot_5.png)

# Change Configurations

- 1) Build in Release mode
- 2) Open Solution properties
![](./Screenshot_3.png)
- 3) Change "Whole Program Optimization" = > "Use Link Time Code Generation"
![](./Screenshot_2.png)
- 4) Set Solution as startup project
![](./Screenshot_4.png)
- 4) Run in Release x64 mode
