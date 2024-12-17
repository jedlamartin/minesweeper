# Minesweeper

**Minesweeper** is a graphical implementation of the classic Minesweeper game written in **C**. It uses the **raylib** library for rendering graphics and provides an interactive, user-friendly experience.

---

## Table of Contents

- [Features](#features)  
- [Requirements](#requirements)  
- [Installation](#installation)  
- [Building the Game](#building-the-game)  
- [Usage](#usage)  
- [Documentation](#documentation)  

---

## Features

- Graphical Minesweeper Game  
- raylib Integration 
- Detailed specifications and documentation in Hungarian are available in the `docs` folder
- Customizable Grid  

---

## Requirements

To compile and run the game, you need:

- **CMake** (for project building)  
- **C Compiler** (e.g., `gcc`)  
- **raylib** (a simple and easy-to-use C library for graphics)  

---

## Installation

### 1. Install raylib  

#### On Linux (Ubuntu/Debian):  
Run the following commands to install raylib:  
```bash
sudo apt update  
sudo apt install libraylib-dev  
```

#### On macOS:  
Using Homebrew:  
```bash
brew install raylib  
```

#### On Windows:  
1. Download precompiled binaries from the official [raylib website](https://www.raylib.com/).  
2. Follow raylib’s Windows installation instructions.  

---

### 2. Clone the Repository  

```bash
git clone https://github.com/jedlamartin/minesweeper.git
cd minesweeper
```

---

## Building the Game

Build the project using **CMake**:

1. Create a `build` directory:  
   ```bash
   mkdir build
   cd build
   ```

2. Run CMake to configure the project:  
   ```bash
   cmake ..
   ```

3. Compile the project:  
   ```bash
   cmake --build .
   ```

4. The executable will be generated in the `build` directory.

---

## Usage

Run the compiled executable from the `build` directory:

```bash
./minesweeper
```

Follow the on-screen instructions to play the game.

---

## Documentation

The complete **game specification** and **documentation** are located in the `docs` folder.  
> **Note**: The documentation is written in **Hungarian**.

To access it:  
- Open the `docs` folder in this repository.  
- Review the provided `.pdf` or `.md` files.
