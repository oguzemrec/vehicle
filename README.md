# Vehicle #

To build and run:
```
git clone https://github.com/oguzemrec/vehicle.git
cd vehicle && mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
./vehicle
```

To build for debug
```
git clone https://github.com/oguzemrec/vehicle.git
cd vehicle && mkdir build_debug && cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .
./vehicle
```

To run unittest
```
git clone https://github.com/oguzemrec/vehicle.git
cd vehicle/unittest
mkdir build && cd build
conan install .. -s build_type=Debug -s compiler.libcxx=libc++ -s cppstd=20 --install-folder=cmake-build-debug --build missing
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build . && ./bin/unittest
```



