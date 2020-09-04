# convertEncoding
converts the given encoding (currently WINDOWS) of a file or directory to utf-8 with BOM

## License
GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999

## Usage
**convertEncoding [path]**
path = poath to a file or directory

## Build

  - cd build 
  - cmake ../src
  - cmake -DCMAKE_BUILD_TYPE=Debug --clean-first --build .
  - make [-j 4]
