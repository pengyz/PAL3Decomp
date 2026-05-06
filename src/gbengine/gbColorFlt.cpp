/**
 * gbengine.dll - gbColorFlt
 * Floating-point color class (RGBA)
 */

#include "gbengine/gbengine_types.h"

// Constructor with RGB
gbColorFlt::gbColorFlt(float red, float green, float blue) {
    /* STUB */
    r = red;
    g = green;
    b = blue;
    a = 1.0f;  // Default alpha
}

// Constructor with RGBA
gbColorFlt::gbColorFlt(float red, float green, float blue, float alpha) {
    /* STUB */
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

// Default constructor
gbColorFlt::gbColorFlt() {
    /* STUB */
    r = g = b = 0.0f;
    a = 1.0f;
}

// Assignment operator
gbColorFlt& gbColorFlt::operator=(const gbColorFlt& color) {
    /* STUB */
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

// Inequality operator
int gbColorFlt::operator!=(gbColorFlt& color) {
    /* STUB */
    return (r != color.r || g != color.g || b != color.b || a != color.a) ? 1 : 0;
}

// Add-assign operator
void gbColorFlt::operator+=(const gbColorFlt& color) {
    /* STUB */
    r += color.r;
    g += color.g;
    b += color.b;
    a += color.a;
}
