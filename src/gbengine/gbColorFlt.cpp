/**
 * gbengine.dll - gbColorFlt
 * Floating-point color class (RGBA)
 */

#include "gbengine/gbengine_types.h"

// Constructor with RGB
gbColorFlt::gbColorFlt(float red, float green, float blue) {
    Red = red;
    Green = green;
    Blue = blue;
    Alpha = 1.0f;
}

// Constructor with RGBA
gbColorFlt::gbColorFlt(float red, float green, float blue, float alpha) {
    Red = red;
    Green = green;
    Blue = blue;
    Alpha = alpha;
}

// Default constructor
gbColorFlt::gbColorFlt() {
    Red = Green = Blue = 0.0f;
    Alpha = 1.0f;
}

// Assignment operator
gbColorFlt& gbColorFlt::operator=(const gbColorFlt& color) {
    Red = color.Red;
    Green = color.Green;
    Blue = color.Blue;
    Alpha = color.Alpha;
    return *this;
}

// Inequality operator
int gbColorFlt::operator!=(gbColorFlt& color) {
    return (Red != color.Red || Green != color.Green || Blue != color.Blue || Alpha != color.Alpha) ? 1 : 0;
}

// Add-assign operator
void gbColorFlt::operator+=(const gbColorFlt& color) {
    Red += color.Red;
    Green += color.Green;
    Blue += color.Blue;
    Alpha += color.Alpha;
}
