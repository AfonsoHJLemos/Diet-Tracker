#include <iostream>
#include <vector>

#include "ingredient.h"
#include "utils.h"

using namespace std;

int main() {
  vector<Ingredient> ingredients;
  loadIngredients(ingredients);

  int option;
  do {
    printMenu();

    do {
      cout << "Option (0-6): ";
      cin >> option;
    } while (option < 0 || option > 6);

    system("cls");
    switch (option) {
      case 1:
        viewIngredients(ingredients);
        break;
      case 2:
        addIngredient(ingredients);
        break;
      case 3:
        deleteIngredient(ingredients);
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
    }
  } while (option != 0);

  saveIngredients(ingredients);
  return 0;
}