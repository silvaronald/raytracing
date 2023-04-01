#ifndef LIGHT_H
#define LIGHT_H

#include "../tools/Point3D.h"
#include "../tools/Color.h"

class Light {
public:
    Point3D localization = Point3D(0, 0, 0);
    Color color = Color(0, 0, 0);

    Light (Point3D localization, Color color);
};

#endif /* LIGHT_H */
