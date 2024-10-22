#include "food.h"

/* ------------------------- Methods ------------------------ */

void Food::view() const {
  std::cout << name << "\n"
            << cal << " Cals - " << carb << " Carbs, " << fat << " Fat, "
            << prot << " Prot\n\n";
}

void Food::setName() {
  std::cin.ignore();

  std::cout << "Name: ";
  std::getline(std::cin, name);
}

void Food::setMacros() {
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
}

void Food::resetMacros() {
  cal = 0;
  carb = 0;
  fat = 0;
  prot = 0;
}

bool Food::isEqual(const std::string &name) const {
  return (this->name == name);
}

void Food::addIngredient(const Ingredient &ingredient) {
  ingredients.push_back(ingredient);

  int quantity;

  if (ingredient.isUnit) {
    do {
      std::cout << "\nQuantity: ";
      std::cin >> quantity;
    } while (quantity < 0);
  } else {
    do {
      std::cout << "\nQuantity (g/ml): ";
      std::cin >> quantity;
    } while (quantity < 0);
    quantity /= 100;
  }

  this->cal += ingredient.cal * quantity;
  this->carb += ingredient.carb * quantity;
  this->fat += ingredient.fat * quantity;
  this->prot += ingredient.prot * quantity;
}

/* ------------------------ Functions ----------------------- */

void viewFoods(const std::vector<Food> &foods) {
  if (foods.empty()) {
    clear("There Are No Foods");
    return;
  }

  std::cout << "Foods:\n\n";
  for (const Food &food : foods) food.view();

  pressExit();
}

void addFood(
    std::vector<Food> &foods,
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients) {
  if (foods.empty())
    std::cout << "There Are No Foods\n\n";
  else {
    std::cout << "Foods:\n\n";
    for (const Food &food : foods) food.view();
  }

  Food food;

  food.setName();

  if (findFood(foods, food.name) != FAILURE) {
    clear("Food Already Exists");
    return;
  }

  char tempChar;
  do {
    std::cout << "Made From Ingredients (y/n): ";
    std::cin >> tempChar;
  } while (tempChar != 'y' && tempChar != 'n');

  if (tempChar == 'n') {
    food.setMacros();
    foods.push_back(food);

    clear("Food Added");
    return;
  }

  clear("");

  food.resetMacros();

  Ingredient ingredient;
  int index;

  int category;
  while (true) {
    category = getCategory("add", categories);

    switch (viewCategory(ingredients[category - 1], category)) {
      case FAILURE:
        clear("There Are No " + categories[category - 1] + " Ingredients");
        break;
      case EXIT:
        foods.push_back(food);

        clear("Food Added");
        return;
      case SUCCESS:
        ingredient.setName();

        index = findIngredient(ingredients[category - 1], ingredient.name,
                               ingredient.brand);

        if (index == FAILURE) {
          clear("Ingredient Not Found");
          break;
        }

        food.addIngredient(ingredients[category - 1][index]);

        clear("Ingredient Added");
    }
  }
}

void deleteFood(std::vector<Food> &foods) {
  if (foods.empty()) {
    clear("There Are No Foods");
    return;
  }

  std::cout << "Foods:\n\n";
  for (const Food &food : foods) food.view();

  Food food;
  int index;

  food.setName();

  index = findFood(foods, food.name);

  if (index == FAILURE) {
    clear("Food Not Found");
    return;
  }

  foods.erase(foods.begin() + index);

  clear("Food Deleted");
}

void loadFoods(std::vector<Food> &foods) {
  std::ifstream file("foods.bin");

  if (!file.is_open()) {
    clear("Error Opening Foods File");
    return;
  }

  Food food;
  Ingredient ingredient;

  while (file.peek() != EOF) {
    std::getline(file, food.name);
    file >> food.cal >> std::ws >> food.carb >> std::ws >> food.fat >>
        std::ws >> food.prot;
    file.ignore();

    while (file.peek() != '-') {
      std::getline(file, ingredient.name);
      std::getline(file, ingredient.brand);

      file >> ingredient.cal >> std::ws >> ingredient.carb >> std::ws >>
          ingredient.fat >> std::ws >> ingredient.prot >> std::ws >>
          ingredient.isUnit;
      file.ignore();

      food.ingredients.push_back(ingredient);
    }

    foods.push_back(food);
    file.ignore(2);
  }

  file.close();
}

void saveFoods(const std::vector<Food> &foods) {
  std::ofstream file("foods.bin");

  if (!file.is_open()) {
    clear("Error Opening Foods File\n\n");
    pressExit();
    return;
  }

  for (const Food &food : foods) {
    file << food.name << "\n"
         << food.cal << " " << food.carb << " " << food.fat << " " << food.prot
         << "\n";

    for (const Ingredient &ingredient : food.ingredients) {
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

int findFood(const std::vector<Food> &foods, const std::string &name) {
  if (!foods.empty())
    for (int i = 0; i < foods.size(); i++)
      if (foods[i].isEqual(name)) return i;

  return FAILURE;
}
