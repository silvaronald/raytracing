#include "Color.h"

Color::Color (float red, float green, float blue) {
    this->red = red;
    truncate(this->red);

    this->green = green;
    truncate(this->green);

    this->blue = blue;
    truncate(this->red);
}

void Color::truncate (float &value) {
    if (value < 0) {
        value = 0;
    }

    else if (value > 255) {
        value = 255;
    }
}
