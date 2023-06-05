class RecipeItem {
public:
    RecipeItem(int recipe_id, const std::string& recipe_name,
               const std::string& ingredient_name, double ingredient_quantity,
               const std::string& ingredient_state)
            : recipe_id_(recipe_id), recipe_name_(recipe_name), ingredient_name_(ingredient_name),
              ingredient_quantity_(ingredient_quantity), ingredient_state_(ingredient_state) {}

    int recipe_id() const { return recipe_id_; }
    const std::string& recipe_name() const { return recipe_name_; }
    const std::string& ingredient_name() const { return ingredient_name_; }
    double ingredient_quantity() const { return ingredient_quantity_; }
    const std::string& ingredient_state() const { return ingredient_state_; }

private:
    int recipe_id_;
    std::string recipe_name_;
    std::string ingredient_name_;
    double ingredient_quantity_;
    std::string ingredient_state_;
};