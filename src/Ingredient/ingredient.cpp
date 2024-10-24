#include "ingredient.h"

/* ------------------------- Methods ------------------------ */

void Ingredient::view() const {
  std::cout << name << " - " << brand << "\n"
            << cal << " Cals - " << carb << " Carbs, " << fat << " Fat, "
            << prot << " Prot\n\n";
}

void Ingredient::setName() {
  std::cin.ignore();

  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "Brand: ";
  std::getline(std::cin, brand);
}

void Ingredient::setMacros() {
  do {
    std::cout << "Calories: ";
    std::cin >> cal;
  } while (cal < 0);
  do {
    std::cout << "Carbohydrates: ";
    std::cin >> carb;
  } while (carb < 0);
  do {
    std::cout << "Fat: ";
    std::cin >> fat;
  } while (fat < 0);
  do {
    std::cout << "Protein: ";
    std::cin >> prot;
  } while (prot < 0);

  char tempChar;
  do {
    std::cout << "Is Unit (y/n): ";
    std::cin >> tempChar;
  } while (tempChar != 'y' && tempChar != 'n');
  isUnit = (tempChar == 'y');
}

bool Ingredient::isEqual(const std::string &name,
                         const std::string &brand) const {
  return (this->name == name && this->brand == brand);
}

/* ------------------------ Functions ----------------------- */

void viewIngredients(
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  if (isIngredientsEmpty(ingredients)) {
    clear("There Are No Ingredients");
    return;
  }

  int category;
  while (true) {
    category = getCategory("view", categories);

    switch (viewCategory(ingredients[category - 1], category)) {
      case FAILURE:
        clear("There Are No " + categories[category - 1] + " Ingredients");
        break;
      case EXIT:
        clear("");
        return;
      case SUCCESS:
        pressExit();
    }
  }
}

void addIngredient(
    std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  Ingredient ingredient;

  int category;
  while (true) {
    category = getCategory("add", categories);

    switch (viewCategory(ingredients[category - 1], category)) {
      case EXIT:
        clear("");
        return;
      default:
        ingredient.setName();

        if (findIngredient(ingredients[category - 1], ingredient.name,
                           ingredient.brand) != FAILURE) {
          clear("Ingredient Already Exists");
          return;
        }

        ingredient.setMacros();

        insertIngredient(ingredients[category - 1], ingredient);

        clear("Ingredient Added");
    }
  }
}

void deleteIngredient(
    std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  if (isIngredientsEmpty(ingredients)) {
    clear("There Are No Ingredients");
    return;
  }

  Ingredient ingredient;
  int index;

  int category;
  while (true) {
    category = getCategory("delete", categories);

    switch (viewCategory(ingredients[category - 1], category)) {
      case FAILURE:
        clear("There Are No " + categories[category - 1] + " Ingredients");
        break;
      case EXIT:
        clear("");
        return;
      case SUCCESS:
        ingredient.setName();

        index = findIngredient(ingredients[category - 1], ingredient.name,
                               ingredient.brand);

        if (index == FAILURE) {
          clear("Ingredient Not Found");
          break;
        }

        ingredients[category - 1].erase(ingredients[category - 1].begin() +
                                        index);

        if (isIngredientsEmpty(ingredients)) {
          clear("There Are No Ingredients");
          return;
        };

        clear("Ingredient Deleted");
    }
  }
}

void loadIngredients(
    std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  std::ifstream file("ingredients.bin");

  if (!file.is_open()) {
    clear("Error Opening Ingredients File");
    return;
  }

  if (file.peek() == EOF) {
    file.close();
    return;
  }

  Ingredient ingredient;

  for (int i = 0; i < categories.size(); i++) {
    while (file.peek() != '-') {
      std::getline(file, ingredient.name);
      std::getline(file, ingredient.brand);

      file >> ingredient.cal >> std::ws >> ingredient.carb >> std::ws >>
          ingredient.fat >> std::ws >> ingredient.prot >> std::ws >>
          ingredient.isUnit;
      file.ignore();

      ingredients[i].push_back(ingredient);
    }

    file.ignore(2);
  }

  file.close();
}

void saveIngredients(
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  std::ofstream file("ingredients.bin");

  if (!file.is_open()) {
    clear("Error Opening Ingredients File\n\n");
    pressExit();
    return;
  }

  for (const std::vector<Ingredient> &category : ingredients) {
    for (const Ingredient &ingredient : category) {
      file << ingredient.name << "\n"
           << ingredient.brand << "\n"
           << ingredient.cal << " " << ingredient.carb << " " << ingredient.fat
           << " " << ingredient.prot << " " << ingredient.isUnit << "\n";
    }
    file << "-\n";
  }

  file.close();
}

/* ------------------------- Helpers ------------------------ */

bool isIngredientsEmpty(
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  for (const std::vector<Ingredient> &category : ingredients)
    if (!category.empty()) return false;

  return true;
}

int viewCategory(const std::vector<Ingredient> &ingredients, int category) {
  if (category == 0)
    return EXIT;
  else if (ingredients.empty()) {
    std::cout << "There Are No " << categories[category - 1]
              << " Ingredients\n\n";
    return FAILURE;
  }

  std::cout << categories[category - 1] << " Ingredients:\n\n";
  for (const Ingredient &ingredient : ingredients) ingredient.view();

  return SUCCESS;
}

int findIngredient(const std::vector<Ingredient> &ingredients,
                   const std::string &name, const std::string &brand) {
  if (!ingredients.empty())
    for (int i = 0; i < categories.size(); i++)
      if (ingredients[i].isEqual(name, brand)) return i;

  return FAILURE;
}

void insertIngredient(std::vector<Ingredient> &category,
                      const Ingredient &ingredient) {
  std::vector<Ingredient>::iterator it = std::lower_bound(
      category.begin(), category.end(), ingredient,
      [](const Ingredient &x, const Ingredient &y) { return x.name < y.name; });

  category.insert(it, ingredient);
}