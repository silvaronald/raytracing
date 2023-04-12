#include "Color.h"

Color::Color() {
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}

void Color::multiplyColor(Color color) {
    this->red *= color.red;
    truncate(this->red);

    this->green *= color.green;
    truncate(this->green);

    this->blue *= color.blue;
    truncate(this->blue);
}

void Color::sumColor(Color color) {
    this->red += color.red;
    truncate(this->red);

    this->green += color.green;
    truncate(this->green);

    this->blue += color.blue;
    truncate(this->blue);
}

void Color::multiplyValue(float value) {
    this->red *= value;
    truncate(this->red);

    this->green *= value;
    truncate(this->green);

    this->blue *= value;
    truncate(this->blue);
}

void Color::setColor (float red, float green, float blue) {
    this->red = red;
    truncate(this->red);

    this->green = green;
    truncate(this->green);

    this->blue = blue;
    truncate(this->red);
}

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
