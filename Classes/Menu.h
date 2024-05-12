//
// Created by darksystem on 04-05-2024.
//

#ifndef PROJ2_MENU_H
#define PROJ2_MENU_H


#include "Data.h"
#include "TspManager.h"
#include "Graph.h"

class Menu {
public:

    /**
     * @brief Constructs a Menu object
     * @details Time complexity: O(1)
     */
    Menu();

    /**
     * @brief Displays the menu
     * @details Time complexity: O(1)
     */
    static void showMenu();

    /**
     * @brief Draws the top part of the menu
     * @details Time complexity: O(1)
     */
    static void drawTop();

    /**
     * @brief Draws the bottom part of the menu
     * @details Time complexity: O(1)
     */
    static void drawBottom();

    template <class T>
    double TSPbacktrack(Graph<T> *graph);



};




#endif //PROJ2_MENU_H
