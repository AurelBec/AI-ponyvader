///
/// \file Main.cpp
///

#include "../hdr/Moteur2D.hpp"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    for (int i = argc; i > 0; --i) {
        if (string(argv[i - 1]) == "help") {
            cout << "Ponyvader Quick Documentation" << endl << endl;
            cout << "[./ponyvader (-ips X) (-vit X) (-aa X)]" << endl;
            cout << "-ips X : Set the number of IPS at value X" << endl;
            cout << "-vit X : Set the game speed at value X" << endl;
            cout << "-aa  X : Set the AntiAliasingLevel at value X" << endl;
            cout << "--nogui : Turn off the GUI update in learning mode" << endl;
            cout << endl << "--------------" << endl << endl;
            cout << "Ponyvader is a 1 player game" << endl;
            cout << "The player controls a base, and can use arrows to shoot and move" << endl;
            cout << "Otherwise, you can train an agent using MCRL method" << endl;
            cout << endl << "--------------" << endl << endl;
            cout << "Aurelien BEC - https://github.com/AurelBec/AI-ponyvader" << endl;
            cout << "2018 - Sapienza - AI2" << endl << endl;

            return EXIT_SUCCESS;
        }
    }

    srand(time(0));

    Settings settings(argc, argv);
    Moteur2D moteur(settings);
    moteur.run();

    return EXIT_SUCCESS;
}
