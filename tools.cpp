class Color {

public:
    float red = 0;
    float green = 0;
    float blue = 0;

    void set (float red, float green, float blue) {
        this->red = red;
        truncate(this->red);

        this->green = green;
        truncate(this->green);

        this->blue = blue;
        truncate(this->red);
    }

    void truncate (float &value) {
        if (value < 0) {
            value = 0;
        }

        else if (value > 255) {
            value = 255;
        }
    }
};