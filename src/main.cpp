#include "ingredient.h"
#include "utils.h"

int main() {
  std::array<std::vector<Ingredient>, numCategories> ingredients;
  loadIngredients(ingredients);

  std::size_t option;
  do {
    option = getOption();

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