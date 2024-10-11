#include "utils.h"

#include <iostream>
#include <string>

using namespace std;

void exit(const string &msg) {
  system("cls");
  cout << msg << endl;
}

void pressExit() {
  cout << "Press enter to exit... ";
  cin.ignore();
  cin.get();

  system("cls");
}

void printMenu() {
  cout << "\n";
  cout << "D I E T - T R A C K E R\n";
  cout << "----- Ingredients -----\n";
  cout << "| 1 - View            |\n";
  cout << "| 2 - Add             |\n";
  cout << "| 3 - Delete          |\n";
  cout << "-------- Foods --------\n";
  cout << "| 4 - View            |\n";
  cout << "| 5 - Add             |\n";
  cout << "| 6 - Delete          |\n";
  cout << "-----------------------\n";
  cout << "| 0 - Exit            |\n";
  cout << "-----------------------\n\n";
}

using namespace std;