# UI Framework

A small project exploring how one might write a UI Framework.

### Build and Run

```sh
# build
cmake -B build
cd build
cmake --build .

# run
./uif
```

### Linting and Formatter

```sh
# lint
cpplint --filter=-whitespace/line_length --recursive src include
# format
clang-format -i src/*.cpp include/uif/*.h
```
