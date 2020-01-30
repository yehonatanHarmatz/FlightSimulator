#include "Boot.h"
using namespace boot;
int main(int argc, char* argv[]) {
    Main m;
    int port = argc > 1 ? atoi(argv[1]) : 5600;
    return m.main(port);
}