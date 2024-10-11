#include "ingredient.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

Ingredient::Ingredient(const string &name, const string &brand, double cal,
                       double carb, double fat, double prot)
    : name(name), brand(brand), cal(cal), carb(carb), fat(fat), prot(prot) {}

void Ingredient::view() const {
  cout << name << " - " << brand << "\n";
  cout << cal << " Cals - " << carb << " Carbs, " << fat << " Fat, " << prot
       << " Prot\n";
  cout << endl;
}

bool Ingredient::isEqual(const string &name, const string &brand) const {
  return (this->name == name && this->brand == brand);
}

int findIngredient(vector<Ingredient> &ingredients, const string &name,
                   const string &brand) {
  for (int i = 0; i < ingredients.size(); i++)
    if (ingredients[i].isEqual(name, brand)) return i;

  return -1;
}

void getIngredient(string &name, string &brand) {
  cin.ignore();
  cout << "Name: ";
  getline(cin, name);
  cout << "Brand: ";
  getline(cin, brand);
}

void viewIngredients(const vector<Ingredient> &ingredients) {
  if (ingredients.empty()) {
    exit("There are no ingredients");
    return;
  }

  for (const Ingredient &ingredient : ingredients) ingredient.view();

  pressExit();
  cout << endl;
}

void addIngredient(vector<Ingredient> &ingredients) {
  string name, brand;
  double cal, carb, fat, prot;

  getIngredient(name, brand);

  if (findIngredient(ingredients, name, brand) != -1) {
    exit("Ingredient already exists");
    return;
  }

  do {
    cout << "Calories: ";
    cin >> cal;
  } while (cal < 0);
  do {
    cout << "Carbohydrates: ";
    cin >> carb;
  } while (carb < 0);
  do {
    cout << "Fats: ";
    cin >> fat;
  } while (fat < 0);
  do {
    cout << "Protein: ";
    cin >> prot;
  } while (prot < 0);

  Ingredient newIngredient(name, brand, cal, carb, fat, prot);
  ingredients.push_back(newIngredient);

  exit("Ingredient added");
}

void deleteIngredient(vector<Ingredient> &ingredients) {
  if (ingredients.empty()) {
    exit("There are no ingredients");
    return;
  }

  for (const Ingredient &ingredient : ingredients) ingredient.view();

  string name, brand;

  getIngredient(name, brand);

  int index = findIngredient(ingredients, name, brand);
  if (index == -1) {
    exit("Ingredient not found");
    return;
  }

  ingredients.erase(ingredients.begin() + index);

  exit("Ingredient deleted");
}

void saveIngredients(const vector<Ingredient> &ingredients) {
  ofstream file("ingredients.bin");

  for (const Ingredient &ingredient : ingredients) {
    file << ingredient.name << "\n"
         << ingredient.brand << "\n"
         << ingredient.cal << "\n"
         << ingredient.carb << "\n"
         << ingredient.fat << "\n"
         << ingredient.prot << "\n";
  }

  file.close();
}

void loadIngredients(vector<Ingredient> &ingredients) {
  ifstream file("ingredients.bin");

  if (!file.is_open()) {
    exit("Error opening ingredients file");
    return;
  }

  string name, brand;
  double cal, carb, fat, prot;

  while (getline(file, name) && getline(file, brand) &&
         file >> cal >> carb >> fat >> prot) {
    file.ignore();

    Ingredient newIngredient(name, brand, cal, carb, fat, prot);
    ingredients.push_back(newIngredient);
  }

  file.close();
  cout << endl;
}