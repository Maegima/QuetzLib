# QuetzLib 🎮

QuetzLib is a lightweight **listing program and game launcher** written in C++.  
It provides a simple interface to organize your games and applications, with built-in support for **gamepad input visualization** and launching executables directly.

## ✨ Features
- 📂 **Game Library Management** – Add and organize your games in a clean list.
- 🎮 **Gamepad Support** – Includes a `GamepadWindow` and `AxisDisplayPanel` to visualize controller input.
- 🚀 **Launcher Functionality** – Quickly launch games or applications from the interface.
- ⚡ **Cross-Platform Build** – Built in C++ with a Makefile for easy compilation.
- 📜 **MIT Licensed** – Free to use, modify, and distribute.

## 📂 Project Structure
```
QuetzLib/
├── Application/        # Main source code
├── LICENSE             # MIT License
├── README.md           # Project documentation
├── makefile            # Build instructions
└── .clang-format       # Code style
```

## 📦 Installation
### Prerequisites
- A C++ compiler (e.g., `g++`, `clang`)
- [wxWidgets](https://wxwidgets.org)
- `make` build tool

### Build Instructions
#### Clone the repository
```bash
git clone https://github.com/Maegima/QuetzLib.git
cd QuetzLib
```

#### Build the project
```bash
make
```
This will generate the executable in the build directory.

## 🚀 Usage
Run the compiled binary to open the launcher:

```
./bin/QuetzLib
```

From there, you can:

- Add games to your library
- Launch them directly
- Connect a gamepad to visualize input axes

## ⚙️ Configuration
QuetzLib uses a [.conf](./.conf.example) file to define **paths, runners and image associations**.
This file allows you to customize how the launcher detects games, which emulator or runner to use, and how files are displayed.

### Section Breakdown
#### config
- `root`: Base directory where your games are stored.

#### runners
- Defines the executables/emulators used to run games.
- Example: `snes9x` for SNES, `dolphin` for GameCube/Wii.

#### runner-config (ex.: `snes9x`, `dolphin`)
- Emulator-specific arguments.
- `args=<file.Path>`: Passes the selected game file to the emulator.
- `--config`: Sets emulator options (e.g., fullscreen mode).

#### image
- Maps file types and UI elements to icons.
- Example: `.zip` files use `zip.png`.

#### fileinfo
- Defines metadata fields shown in the launcher (Name, Size, Created, etc.).
- Supports regex-based links to external sites.

### Customization Tips
- Update the root path to match your own ROM directory.
- Add or modify runners for different emulators.
- Use [fileinfo] links to integrate with external databases or artwork sources.

## 🛠️ Contributing
Contributions are welcome! Feel free to fork the repo, open issues, or submit pull requests.

## 📜 License
This project is licensed under the MIT License – see the LICENSE file for details.