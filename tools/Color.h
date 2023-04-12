#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    float red = 0;
    float green = 0;
    float blue = 0;

    Color ();
    
    void multiplyValue (float value);
    void multiplyColor (Color color);
    void sumColor (Color color);
    void setColor (float red, float green, float blue);
    Color (float red, float green, float blue);
    void truncate();
    void normalize();
    void denormalize();
};

#endif 
