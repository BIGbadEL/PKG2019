#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.h"
#include "Menu.h"

int main() {
    Window window;

    while (window.isOpen()) {

        window.update();

    }

    return 1;
}



