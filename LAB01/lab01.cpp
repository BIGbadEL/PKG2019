// Calosc mozna dowolnie edytowac wedle uznania. 

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "window.h"


int main()
{
 Window window{};


 while (window.isOpen())
  {
     window.render();
  }

 return 0;
}