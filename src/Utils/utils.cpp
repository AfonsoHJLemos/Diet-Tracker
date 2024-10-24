#include "utils.h"

void clear(const std::string &msg) {
  system("cls");
  std::cout << msg;
}

void pressExit() {
  std::cout << "Press Enter To Exit... ";
  std::cin.ignore();
  std::cin.get();

  clear("");
}

int getOption() {
  std::cout << "\n\n"
               "D I E T - T R A C K E R\n"
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

  int option;
  do {
    std::cout << "Option (0-6): ";
    std::cin >> option;
  } while (option < 0 || option > 6);

  clear("");
  return option;
}

int getCategory(const std::string &operation,
                const std::array<std::string, 7> &categories) {
  std::cout << "\n\n";

  if (operation == "view")
    std::cout << "        V I E W        \n";
  else if (operation == "add")
    std::cout << "         A D D         \n";
  else if (operation == "delete")
    std::cout << "      D E L E T E      \n";
  else
    std::cout << " W R O N G   T I T L E \n";

  std::cout << "------ Categories -----\n";
  for (int i = 0; i < categories.size(); i++)
    std::cout << "| " << i + 1 << " - " << categories[i]
              << std::string(16 - categories[i].size(), ' ') << "|\n";
  std::cout << "-----------------------\n"
               "| 0 - Back            |\n"
               "-----------------------\n"
            << std::endl;

  int category;
  do {
    std::cout << "Category (0-" << categories.size() << "): ";
    std::cin >> category;
  } while (category < 0 || category > categories.size());

  clear("");
  return category;
}
