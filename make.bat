set CMAKE_ARGS=-DLLAMA_CUBLAS=on
set FORCE_CMAKE=1
cmake --build build\ --config Release
make .