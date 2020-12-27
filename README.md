# convertEncoding
converts the given encoding (currently WINDOWS) of a file or directory to utf-8 with BOM.

## License
The work is licensed under Apache License form Version 2.0, January 2004.
See LICENSE

## Usage
**convertEncoding [path]**
path = path to a file or directory

## Build

  - cd build 
  - cmake ../src
  - cmake -DCMAKE_BUILD_TYPE=Debug --clean-first --build .
  - make [-j 4]
