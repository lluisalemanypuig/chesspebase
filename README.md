# Chess Puzzle Database explorer

This is a tool to explore a database of chess positions by pieces, that is, the search criteria are not the themes of the puzzle (mate in 1, mate in 2, pin, fortress, ...) but the number of pieces. For example, with chesspebase you can search the database for all positions
- with a number of pawns between 1 and 3 (both White and Black), and exactly 2 bishops (both White and Black),
- with 2 White rooks and a Black queen,
- ...

The way this tool works is by loading first a database from a local file. We currently support the following databases
- [lichess](https://database.lichess.org/#puzzles)

## Tools

- [cli](/cli): the explorer can be used via a command line terminal.
- [web](/web): the explorer can be run as a web server with a backend.

See each subdirectory (by following the links) to read more about each tool.

## Building

To use any of the tools, it is recommended to build the project with the following steps.

### Dependencies

- One dependency of this project is the [classification-tree](https://github.com/lluisalemanypuig/classification-tree.git) library. It is a header-only library, so you only need to download it.

        $ git clone git@github.com:lluisalemanypuig/classification-tree.git

- We also use [cpp-httplib](https://github.com/yhirose/cpp-httplib) to build the web server. It is downloaded automatically.

### Compiling

First, clone this repository next to the `classification-tree` project you just downloaded.

    $ git clone git@github.com:lluisalemanypuig/chesspebase.git

and issue the following commands

    $ mkdir build-release
    $ cd build-release
    $ cmake .. -DCMAKE_BUILD_TYPE=Release
    $ make -j

### Testing

In order to run the tests, it is recommended to build in `debug` mode.

    $ mkdir build-debug
    $ cd build-debug
    $ cmake .. -DCMAKE_BUILD_TYPE=Debug
    $ make -j
    $ cd tests
    $ ctest .
