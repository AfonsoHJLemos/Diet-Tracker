#include "utils.h"

void exit(const std::string &msg) {
  system("cls");
  std::cout << msg << "\n" << std::endl;
}

void pressExit() {
  std::cout << "Press Enter To Exit... ";
  std::cin.ignore();
  std::cin.get();

  exit("");
}

std::size_t getOption() {
  std::size_t option;

  std::cout << "D I E T - T R A C K E R\n"
               "----- Ingredients -----\n"
               "| 1 - View            |\n"
               "| 2 - Add             |\n"
               "| 3 - Delete          |\n"
               "-------- Foods --------\n"
               "| 4 - View            |\n"
               "| 5 - Add             |\n"
               "| 6 - Delete          |\n"
               "-----------------------\n"
               "| 0 - Exit            |\n"
               "-----------------------\n"
            << std::endl;

  do {
    std::cout << "Option (0-6): ";
    std::cin >> option;
  } while (option < 0 || option > 6);

  exit("");
  return option;
}

std::size_t getCategory(const std::string &operation) {
  if (operation == "view")
    std::cout << "        V I E W        \n";
  else if (operation == "add")
    std::cout << "         A D D         \n";
  else if (operation == "delete")
    std::cout << "      D E L E T E      \n";
  else
    std::cout << " T I T L E   E R R O R \n";

  std::size_t category;

  std::cout << "------ Categories -----\n";
  showCategories();
  std::cout << "-----------------------\n"
               "| 0 - Back            |\n"
               "-----------------------\n"
            << std::endl;

  do {
    std::cout << "Category (0-" << numCategories << "): ";
    std::cin >> category;
  } while (category < 0 || category > numCategories);

  system("cls");
  return category;
}

void showCategories() {
  for (std::size_t i = 0; i < numCategories; i++) {
    std::cout << "| " << i + 1 << " - " << categories[i]
              << std::string(16 - categories[i].size(), ' ') << "|\n";
  }
}