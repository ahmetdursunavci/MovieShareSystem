#include <iostream>

#include "ReadFromFile.h"

using namespace std;

int main(int argc, char *argv[]) {
    ReadFromFile read(argv[1],argv[2]);
    read.Reading();



}
