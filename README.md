# README for R-TYPE Multiplayer Network Game

## Introduction

Welcome to R-TYPE, an immersive multiplayer space battle game focusing on teamwork and strategy. This README guides you through setup and introduces the game's unique technical features through the documentation.

### Documentation

We have developed a Notion documentation covering four key aspects:

- The Server
- The Game Engine
- How The Client work
- The communication protocol between The Server and The Client

You can access to the documentation following this link: https://opalescent-crab-ddf.notion.site/R-Type-f91eb3655a224788a63274d78887f703?pvs=4

## Getting Started

To embark on your R-TYPE adventure, follow these steps to set up the game environment:

### Cloning the Repository

Begin by cloning the R-TYPE repository to your local machine:

```bash
git clone git@github.com:MaxPeix/R-TYPE.git
```

This command copies all the necessary game files to your system.

### Installation

The script will create a folder r_type_DATE_TIME in the current directory with the binary files inside and the asset folder.

MacOS and Linux:

```bash
./build.sh
```

Windows:

```bash
./build.bat
```

If you don't have the necessary libraries start by installing them, notes that the cmake will automatically install asio for you but in case here are the commands:

#### Ubuntu:

```bash
sudo apt install cmake
sudo apt install libasio-dev
```

#### Fedora:

```bash
sudo dnf install cmake
sudo dnf install asio-devel
```

#### Mac OS:

```bash
brew install cmake
brew install asio
```

#### and then run the build script again with ./build.sh

### Let's play now

After successful compilation, start the R-TYPE server:

```bash
./r-type_server
```

And start the R-TYPE client:

```bash
./r-type_client
```

## Gameplay

Upon launching the client, you'll enter the R-TYPE universe, where you can join other players in cooperative missions against various foes. Master your spacecraft, strategize with your team, and enjoy the high-octane combat that R-TYPE offers.

## Contributors

The development of R-TYPE was made possible thanks to the efforts and dedication of several developers.

- **MaxPeix**

- **gautier337**

- **Hugo-code-dev**

- **RemiMaigrot**

- **NameIsDume** 
