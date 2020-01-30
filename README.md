# Milestone 2 C++ Project
### Credit:  Yehonatan Harmatz and Oren Schwartz
## Description:
This is a C++ project that solves searching problems using searching algorithm.
This is a server that can handle up to 10 different client simultaneously. Each client sent a searching problem to the server and the server solves the problem and sends the solution back to the client. The server solves the searcing problem using the A* searcing algorithm.
The protocol of connection between the client and the server:
The client send the matrix, start position, end position and then "end"

#### Compile the program using this command:
> g++ -std=c++14 \*/*.cpp *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

#### and then run it with:
> ./a.out [PORT NUMBER]
