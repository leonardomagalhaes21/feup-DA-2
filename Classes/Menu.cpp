#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {}

void Menu::drawTop() {
    cout << "____________________________________________________" << endl;
    cout << "|" << "====================== Menu ======================" << "|" << endl;
    cout << "|__________________________________________________|" << endl;
}

void Menu::drawBottom() {
    cout << "|__________________________________________________|" << endl;
    cout << "|==================================================|" << endl;
    cout << "|__________________________________________________|" << endl;
}

void Menu::showMenu() {
    char key;
    bool mainMenu = true;
    bool subMenu = false;

    TspManager tspm;
    string system;

    while (mainMenu) {
        drawTop();
        cout << "| 1. Real World Graphs                             |" << endl;
        cout << "| 2. Toy-Graphs                                    |" << endl;
        cout << "| 3. Extra-Fully-Connected Graphs                  |" << endl;
        drawBottom();
        cout << "Choose an option: ";
        cin >> key;
        switch (key) {
            case '1': {
                drawTop();
                cout << "| 1. Real-Graph 1                                  |" << endl;
                cout << "| 2. Real-Graph 2                                  |" << endl;
                cout << "| 3. Real-Graph 3                                  |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        system = "real1";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '2': {
                        system = "real2";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '3': {
                        system = "real3";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                }
                break;
            }
            case '2': {
                drawTop();
                cout << "| 1. Load shipping.csv (Not fully connected graph) |" << endl;
                cout << "| 2. Load stadiums.csv                             |" << endl;
                cout << "| 3. Load tourism.csv                              |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        system = "shipping";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '2': {
                        system = "stadiums";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '3': {
                        system = "tourism";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                }
                break;
            }
            case '3': {
                drawTop();
                cout << "| 1. Load Graph with 25 nodes                      |" << endl;
                cout << "| 2. Load Graph with 50 nodes                      |" << endl;
                cout << "| 3. Load Graph with 100 nodes                     |" << endl;
                cout << "| 4. Load Graph with 200 nodes                     |" << endl;
                cout << "| 5. Load Graph with 300 nodes                     |" << endl;
                cout << "| 6. Load Graph with 400 nodes                     |" << endl;
                cout << "| 7. Load Graph with 500 nodes                     |" << endl;
                cout << "| 8. Load Graph with 600 nodes                     |" << endl;
                cout << "| 9. Load Graph with 700 nodes                     |" << endl;
                cout << "| A. Load Graph with 800 nodes                     |" << endl;
                cout << "| B. Load Graph with 900 nodes                     |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        system = "25";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '2': {
                        system = "50";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '3': {
                        system = "100";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '4': {
                        system = "200";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '5': {
                        system = "300";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '6': {
                        system = "400";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '7': {
                        system = "500";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '8': {
                        system = "600";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '9': {
                        system = "700";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'A': {
                        system = "800";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'B': {
                        system = "900";
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                }
                break;
            }
            default: {
                cout << endl << "Invalid option!" << endl;
                break;
            }
        }

        while (subMenu) {
            drawTop();
            cout << "| 1. Backtracking Algorithm                        |" << endl;
            cout << "| 2. Triangular Heuristic Approximation            |" << endl;
            cout << "| 3. Prim's Algorithm                              |" << endl;
            cout << "| 4. Change Dataset                                |" << endl;
            cout << "| 5. Print Network Details                         |" << endl;
            cout << "| Q. Exit                                          |" << endl;
            drawBottom();
            cout << "Choose an option: ";
            cin >> key;
            switch (key) {
                case '1': {
                    tspm.TSPbacktracking();
                    break;
                }
                case '2': {
                    tspm.TSPtriangularHeuristic();
                    break;
                }
                case '3':{
                    tspm.TSPprim();
                    break;
                }
                case '4': {
                    mainMenu = true;
                    subMenu = false;
                    break;
                }
                case '5': {
                    char key1;
                    drawTop();
                    cout << "| 1. Print Cities Details                          |" << endl;
                    cout << "| 2. Print Reservoirs Details                      |" << endl;
                    cout << "| 3. Print Pumping Stations Details                |" << endl;
                    cout << "| Q. Exit                                          |" << endl;
                    drawBottom();
                    cout << "Choose an option: ";
                    cin >> key1;
                    switch (key1) {
                        case '1': {
                            // wsm.printCitiesDetails();
                            break;
                        }
                        case '2': {
                            // wsm.printReservoirsDetails();
                            break;
                        }
                        case '3': {
                            // wsm.printStationsDetails();
                            break;
                        }
                        case 'Q' : {
                            break;
                        }
                        default: {
                            cout << endl << "Invalid option!" << endl;
                        }
                    };
                    break;
                }
                case 'Q' : {
                    mainMenu = false;
                    subMenu = false;
                    break;
                }
                default: {
                    cout << endl << "Invalid option!" << endl;
                }
            }

            if (subMenu) {
                cout << endl;
                cout << "Would you like to do something else? (Y/N) \n";
                char newCycle;
                cin >> newCycle;
                if (newCycle == 'N') subMenu = false;
                while (newCycle != 'Y' && newCycle != 'N') {
                    cout << "Please type \"Y\" or \"N\"." << endl;
                    cin >> newCycle;
                    if (newCycle == 'N') subMenu = false;
                }
            }
        }
    }
}
