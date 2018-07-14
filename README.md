# mul
Utility libraries for C++11/14/17 development. 
The libraries are divided into several modules:
- **benchmark_tool**: a benchmark library targeting microcontrollers
- **bimap**: a bidirectionnal associative container
- **bluetooth**: 	a cross-platform bluetooth library
- **logger**: a very simple logger library
- **nullstream**: a stream similar to Unix' /dev/null
- **serial**: a cross-plateform serial communication library
- **sfe**: an extension for SFML

## Building
The mul uses CMake as main build system. To build the libraries, use the following commands:
```
cd <mul-directory>
mkdir build && cd build
cmake -G"<generator>" -DWITH_<module-name>=<ON/OFF> ..
```
