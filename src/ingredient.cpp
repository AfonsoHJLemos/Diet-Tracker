#include "ingredient.h"

/* ------------------------- Methods ------------------------ */

Ingredient::Ingredient(const std::string &name, const std::string &brand,
                       double cal, double carb, double fat, double prot)
    : name(name), brand(brand), cal(cal), carb(carb), fat(fat), prot(prot) {}

void Ingredient::view() const {
  std::cout << name << " - " << brand << "\n"
            << cal << " Cals - " << carb << " Carbs, " << fat << " Fat, "
            << prot << " Prot\n"
            << std::endl;
}

bool Ingredient::isEqual(const std::string &name,
                         const std::string &brand) const {
  return (this->name == name && this->brand == brand);
}

/* ------------------------ Functions ----------------------- */

void viewIngredients(
    const std::array<std::vector<Ingredient>, numCategories> &ingredients) {
  if (isIngredientsEmpty(ingredients)) {
    exit("There Are No Ingredients");
    return;
  }

  int category;
  while (true) {
    category = getCategory("view");

    switch (viewCategory(ingredients[category - 1], category)) {
      case 0:
        exit("");
        return;
      case 1:
        pressExit();
        break;
      default:
        exit("There Are No " + categories[category - 1] + " Ingredients");
    }
  }
}

void addIngredient(
    std::array<std::vector<Ingredient>, numCategories> &ingredients) {
  std::string name, brand;
  double cal, carb, fat, prot;

  int category;
  while (true) {
    category = getCategory("add");

    switch (viewCategory(ingredients[category - 1], category)) {
      case 0:
        exit("");
        return;
      default:
        getIngredient(name, brand);

        if (findIngredient(ingredients[category - 1], name, brand) != -1) {
          exit("Ingredient Already Exists");
          return;
        }

        getMacros(cal, carb, fat, prot);

        ingredients[category - 1].push_back(
            {name, brand, cal, carb, fat, prot});

        exit("Ingredient Added");
    }
  }
}

void deleteIngredient(
    std::array<std::vector<Ingredient>, numCategories> &ingredients) {
  if (isIngredientsEmpty(ingredients)) {
    exit("There Are No Ingredients");
    return;
  }

  std::string name, brand;
  std::size_t index;

  int category;
  while (true) {
    category = getCategory("delete");

    switch (viewCategory(ingredients[category - 1], category)) {
      case 0:
        exit("");
        return;
      case 1:
        getIngredient(name, brand);

        index = findIngredient(ingredients[category - 1], name, brand);

        if (index == -1) {
          exit("Ingredient Not Found");
          break;
        }

        ingredients[category - 1].erase(ingredients[category - 1].begin() +
                                        index);

        if (isIngredientsEmpty(ingredients)) {
          exit("There Are No Ingredients");
          return;
        };

        exit("Ingredient Deleted");
        break;
      default:
        exit("There Are No " + categories[category - 1] + " Ingredients");
    }
  }
}

void loadIngredients(
    std::array<std::vector<Ingredient>, numCategories> &ingredients) {
  std::ifstream file("ingredients.bin");

  if (!file.is_open()) {
    exit("Error Opening Ingredients File");
    return;
  }

  std::string name, brand;
  double cal, carb, fat, prot;

  for (std::size_t i = 0; i < numCategories; i++) {
    while (file.peek() != '-' && !file.eof()) {
      std::getline(file, name);
      std::getline(file, brand);

      file >> cal >> std::ws >> carb >> std::ws >> fat >> std::ws >> prot;
      file.ignore();

      ingredients[i].push_back({name, brand, cal, carb, fat, prot});
    }

    file.ignore(2);
  }

  file.close();
  exit("");
}

void saveIngredients(
    const std::array<std::vector<Ingredient>, numCategories> &ingredients) {
  std::ofstream file("ingredients.bin");

  if (!file.is_open()) {
    exit("Error Opening Ingredients File");
    pressExit();
    return;
  }

  for (const std::vector<Ingredient> &category : ingredients) {
    for (const Ingredient &ingredient : category) {
      file << ingredient.name << "\n"
           << ingredient.brand << "\n"
           << ingredient.cal << " " << ingredient.carb << " " << ingredient.fat
           << " " << ingredient.prot << "\n";
    }
    file << "-\n";
  }

  file.close();
}

/* ------------------------- Others ------------------------- */

void getIngredient(std::string &name, std::string &brand) {
  std::cin.ignore();
  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "Brand: ";
  std::getline(std::cin, brand);
}

void getMacros(double &cal, double &carb, double &fat, double &prot) {
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

std::size_t findIngredient(const std::vector<Ingredient> &ingredients,
                           const std::string &name, const std::string &brand) {
  if (!ingredients.empty())
    for (std::size_t i = 0; i < numCategories; i++)
      if (ingredients[i].isEqual(name, brand)) return i;

  return -1;
}

int viewCategory(const std::vector<Ingredient> &ingredients, int &category) {
  if (category == 0)
    return 0;
  else if (ingredients.empty())
    return -1;

  std::cout << categories[category - 1] << " Ingredients:\n\n";
  for (const Ingredient &ingredient : ingredients) ingredient.view();

  return 1;
}

bool isIngredientsEmpty(
    const std::array<std::vector<Ingredient>, numCategories> &ingredients) {
  for (const std::vector<Ingredient> &category : ingredients)
    if (!category.empty()) return false;

  return true;
}
