#include "Menu.h"

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
        cout << "| Q. Exit                                          |" << endl;
        drawBottom();
        cout << "Choose an option: ";
        cin >> key;
        switch (key) {
            case '1': {
                drawTop();
                cout << "| 1. Real-Graph 1                                  |" << endl;
                cout << "| 2. Real-Graph 2                                  |" << endl;
                cout << "| 3. Real-Graph 3                                  |" << endl;
                cout << "| Q. Exit                                          |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        system = "real1";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '2': {
                        system = "real2";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '3': {
                        system = "real3";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'Q' : {
                        mainMenu = false;
                        subMenu = false;
                        break;
                    }
                    default : {
                        cout << endl << "Invalid option!" << endl;
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
                cout << "| Q. Exit                                          |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        system = "shipping";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '2': {
                        system = "stadiums";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '3': {
                        system = "tourism";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'Q' : {
                        mainMenu = false;
                        subMenu = false;
                        break;
                    }
                    default : {
                        cout << endl << "Invalid option!" << endl;
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
                cout << "| Q. Exit                                          |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        system = "25";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '2': {
                        system = "50";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '3': {
                        system = "100";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '4': {
                        system = "200";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '5': {
                        system = "300";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '6': {
                        system = "400";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '7': {
                        system = "500";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '8': {
                        system = "600";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case '9': {
                        system = "700";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'A': {
                        system = "800";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'B': {
                        system = "900";
                        cout << "Loading data..." << endl;
                        Data d = Data(system);
                        tspm = TspManager(d);
                        mainMenu = false;
                        subMenu = true;
                        break;
                    }
                    case 'Q' : {
                        mainMenu = false;
                        subMenu = false;
                        break;
                    }
                    default : {
                        cout << endl << "Invalid option!" << endl;
                        break;
                    }
                }
                break;
            }
            case 'Q' : {
                mainMenu = false;
                subMenu = false;
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
            cout << "| 4. TSP in the Real World                         |" << endl;
            cout << "| 5. Print Network Details                         |" << endl;
            cout << "| 6. Comparative Analysis                          |" << endl;
            cout << "| 7. Change Dataset                                |" << endl;
            cout << "| Q. Exit                                          |" << endl;
            drawBottom();
            cout << "Choose an option: ";
            cin >> key;
            switch (key) {
                case '1': {
                    tspm.tspBacktracking();
                    break;
                }
                case '2': {
                    if (system != "shipping" && system != "real2" && system != "real3") {
                        drawTop();
                        cout << "| 1. Triangular Heuristic Approximation            |" << endl;
                        cout << "| 2. Triangular Heuristic Approximation Alternative|" << endl;
                        cout << "| Q. Exit                                          |" << endl;
                        drawBottom();
                        cout << "Choose an option: ";
                        cin >> key;
                        switch (key) {
                            case '1': {
                                tspm.tspTriangularHeuristicInput();
                                break;
                            }
                            case '2': {
                                tspm.tspTriangularHeuristicAlternativeInput();
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
                    }
                    else cout << "This option is not available for this dataset." << endl;
                    break;
                }
                case '3': {
                    if (system == "shipping") {
                        cout << "This option is not available for this dataset." << endl;
                        break;
                    }
                    bool flag = (system == "real2" || system == "real3");
                    tspm.tspPrim(flag);
                    break;
                }
                case '4': {
                    tspm.kruskalRealWorld();
                    break;
                }
                case '5': {
                    tspm.printNetworkInfo(system);

                    break;
                }

                case '6': {
                    if (system != "shipping" && system != "real2" && system != "real3") {
                        tspm.compareAlgorithmsPerformance();
                    }
                    else cout << "This option is not available for this dataset." << endl;
                    break;
                }

                case '7': {
                    mainMenu = true;
                    subMenu = false;
                    break;
                }
                case 'Q' : {
                    mainMenu = false;
                    subMenu = false;
                    break;
                }
                default: {
                    cout << endl << "Invalid option!" << endl;
                    break;
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
