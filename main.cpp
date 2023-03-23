#include "tools/Color.h"
#include "iostream"

int main () {
    Color myColor;

    myColor.set(255.55, -12.500, 26.589);

    std::cout << " " << myColor.red << " " << myColor.green << " " << myColor.blue;
}