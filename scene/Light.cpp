#include "Light.h"

Light::Light (Point3D localization, Color color) {
    this->localization = localization;
    this->color = color;
    this->color.normalize();
}