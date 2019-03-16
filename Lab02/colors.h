//
// Created by grzegorz on 16.03.19.
//

#pragma once


#include <cmath>

#define colors_size_x 250
#define colors_size_y 250

struct HSL {
    float H;
    float S;
    float L;
};

struct HSV {
    float H;
    float S;
    float V;
};

struct CMY {
    float C;
    float M;
    float Y;
};

struct RGB {
    float R;
    float G;
    float B;
};

RGB convert(const CMY& col){
    RGB result = {};

    result.R = (1.0f - col.C) * 255.0f;
    result.G = (1.0f - col.M) * 255.0f;
    result.B = (1.0f - col.Y) * 255.0f;

    return result;
}

RGB convert(const HSV& col) {
    RGB result = { };
    if (col.S == 0) {
        result.R = col.V * 255;
        result.G = col.V * 255;
        result.B = col.V * 255;
    } else {
        float h = col.H * 6;
        if (h == 6) h = 0;      //H must be < 1
        auto i = static_cast<int>(h);            //Or ... var_i = floor( var_h )
        float a = col.V * ( 1 - col.S );
        float b = col.V * ( 1 - col.S * ( h - static_cast<float>(i) ));
        float c = col.V * ( 1 - col.S * ( 1 - ( h - static_cast<float>(i) )));

        if (i == 0) {
            result.R = col.V;
            result.G = c;
            result.B = a;
        } else if (i == 1) {
            result.R = b;
            result.G = col.V;
            result.B = a;
        } else if (i == 2) {
            result.R = a;
            result.G = col.V;
            result.B = c;
        } else if (i == 3) {
            result.R = a;
            result.G = b;
            result.B = col.V;
        } else if (i == 4) {
            result.R = c;
            result.G = a;
            result.B = col.V;
        } else {
            result.R = col.V;
            result.G = a;
            result.B = b;
        }

        result.R *= 255.0f;
        result.G *= 255.0f;
        result.B *= 255.0f;

    }

    return result;
}

RGB convert(const HSL& col) {
    float C = ( 1.0f - fabsf(2.0f * col.L - 1.0f)) * col.S;
    float X = C * ( 1.0f - fabsf(fmodf(col.H * 0.016666f, 2.0f) - 1.0f));
    float m = col.L - C / 2.0f;
    RGB result = { };

    if (col.H < 60) {
        result.R = ( C + m ) * 255;
        result.G = ( X + m ) * 255;
        result.B = ( 0 + m ) * 255;
    } else if (col.H < 120) {
        result.R = ( X + m ) * 255;
        result.G = ( C + m ) * 255;
        result.B = ( 0 + m ) * 255;
    } else if (col.H < 180) {
        result.R = ( 0 + m ) * 255;
        result.G = ( C + m ) * 255;
        result.B = ( X + m ) * 255;
    } else if (col.H < 240) {
        result.R = ( 0 + m ) * 255;
        result.G = ( X + m ) * 255;
        result.B = ( C + m ) * 255;
    } else if (col.H < 300) {
        result.R = ( X + m ) * 255;
        result.G = ( 0 + m ) * 255;
        result.B = ( C + m ) * 255;
    } else {
        result.R = ( C + m ) * 255;
        result.G = ( 0 + m ) * 255;
        result.B = ( X + m ) * 255;
    }

    return result;
}

inline void draw_to_color_pixels(int x, int y, RGB col, sf::Uint8* pixels, int colors__x) {
    pixels[4 * ( y * colors__x + x ) + 0] = static_cast<sf::Uint8>(col.R);
    pixels[4 * ( y * colors__x + x ) + 1] = static_cast<sf::Uint8>(col.G);
    pixels[4 * ( y * colors__x + x ) + 2] = static_cast<sf::Uint8>(col.B);
    pixels[4 * ( y * colors__x + x ) + 3] = static_cast<sf::Uint8>(255);
}
//APP_COLORS_H
