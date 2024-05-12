#include <iostream>
#include "Classes/Menu.h"

int main() {
    std::cout << "Loading ..." << std::endl;
    Menu m = Menu();
    m.showMenu();
    std::cout << std::endl;
    std::cout << "Done!" << std::endl;
    return 0;
}
