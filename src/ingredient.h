#ifndef INGREDIENT_H
#define INGREDIENT_H

using namespace std;

#include <string>
#include <vector>

class Ingredient {
 public:
  string name, brand;
  double cal, carb, fat, prot;

  Ingredient(const string &name, const string &brand, double cal, double carb,
             double fat, double prot);

  void view() const;

  bool isEqual(const string &name, const string &brand) const;
};

int findIngredient(const vector<Ingredient> &ingredients, const string &name,
                   const string &brand);

void getIngredient(string &name, string &brand);

void viewIngredients(const vector<Ingredient> &ingredients);

void addIngredient(vector<Ingredient> &ingredients);

void deleteIngredient(vector<Ingredient> &ingredients);

void saveIngredients(const vector<Ingredient> &ingredients);

void loadIngredients(vector<Ingredient> &ingredients);

#endif