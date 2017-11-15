# PONYVADER

Want to play space invader with ponies? Or see an agent learning to defeat them?

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

Requires SFML library and a compiler supporting c++11 standards

```
sudo apt-get install libsfml-dev
```

### Installing

Create the build directory if not present at ROOT

```
cd ROOT_PROJECT/
mkdir build
```

then

```
cd build
cmake ..
make
cd ..
```

You can also run the following commands directly into the ROOT folder, but it'll flood it with unwanted files
```
cmake ./
make
```


## Running the game

The game is generated in the ROOT directory

```
cd ROOT_PROJECT/
./ponyvader
```

For help and detailled options, run
```
./ponyvader help
```

## Author

**Aurelien BEC** - *An AI project* - [AurelBec](https://github.com/AurelBec)

## License

This project is licensed under free licence
