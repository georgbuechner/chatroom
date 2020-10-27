# chatroom
A simple webserver in which you can log into and start chatting. 
This repository mainly aims to use and experiment with various DevOps like automated Tests, github-actions and continuos integraion/ delivery and further more. 

## What we're using here...

### Conan
Conan is a c++ package-manager. 
Using conan simplifies building the project on a new platform, as dependencies will automatically be installed while building.

### CMake
CMake is used to generalize the compilation process. 
As well as conan it is a step towards making a program run on cross-platform, as platform and compiler independent configuration-files are used.

### Catch
Catch is a testing tool for c++, which is used to set up a series of tests.

### GitHub Actions
A cmake workflow is setup, which automatically tries to build and run tests on a clean ubuntu server
