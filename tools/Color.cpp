#include "Color.h"

Color::Color (float red, float green, float blue) {
    this->red = red;

    this->green = green;

    this->blue = blue;
}

Color::Color() {
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}

void Color::multiplyColor(Color color) {
    this->red *= color.red;

    this->green *= color.green;

    this->blue *= color.blue;

    truncate();
}

void Color::sumColor(Color color) {
    this->red += color.red;

    this->green += color.green;

    this->blue += color.blue;

    truncate();
}

void Color::multiplyValue(float value) {
    this->red *= value;
    this->green *= value;

    this->blue *= value;

    truncate();
}

void Color::setColor (float red, float green, float blue) {
    this->red = red;

    this->green = green;

    this->blue = blue;

    truncate();
}

void Color::truncate () {
    if (this->red < 0) {
        this->red = 0;
    }
    else if (this->red > 1) {
        this->red = 1;
    }

    if (this->green < 0) {
        this->green = 0;
    }
    else if (this->green > 1) {
        this->green = 1;
    }

    if (this->green < 0) {
        this->green = 0;
    }
    else if (this->green > 1) {
        this->green = 1;
    }
}

void Color::normalize() {
    this->red = this->red / 255;
    this->green = this->green / 255;
    this->blue = this->blue / 255;
}

void Color::denormalize() {
    this->red = this->red * 255;
    this->green = this->green * 255;
    this->blue = this->blue * 255;
}
