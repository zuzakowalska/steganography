//
// Created by Zuzanna Kowalska on 29/12/2021.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_PIXEL_H
#define STEGANOGRAFIA_OBRAZOWA_PIXEL_H

class Pixel<T> {

    T red;
    T green;
    T blue;
    T alpha;

public:
    const T &getRed() const {
        return red;
    }

    void setRed(const T &red) {
        Pixel::red = red;
    }

    const T &getGreen() const {
        return green;
    }

    void setGreen(const T &green) {
        Pixel::green = green;
    }

    const T &getBlue() const {
        return blue;
    }

    void setBlue(const T &blue) {
        Pixel::blue = blue;
    }

    const T &getAlpha() const {
        return alpha;
    }

    void setAlpha(const T &alpha) {
        Pixel::alpha = alpha;
    }

    /**
     *
     * @param red
     * @param green
     * @param blue
     * @param alpha
     */
    Pixel(const T &red, const T &green, const T &blue, const T &alpha) {

        this.red = red;

        this.green = green;

        this.blue = blue;

        this.alpha = alpha;
    }
};

#endif //STEGANOGRAFIA_OBRAZOWA_PIXEL_H
