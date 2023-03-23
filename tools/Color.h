#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    float red = 0;
    float green = 0;
    float blue = 0;

    void set(float red, float green, float blue);
    void truncate(float &value);
};

#endif 
