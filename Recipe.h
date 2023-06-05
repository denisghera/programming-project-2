class Recipe {
public:
    void load_recipes_from_csv(const std::string& filename);
    void visualize_recipes() const;
    void check_sufficient_ingredients(int recipe_id, Inventory inventory) const;
private:
    std::vector<RecipeItem> recipe_items_;
};

void Recipe::load_recipes_from_csv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    recipe_items_.clear();

    // Skip the first line
    std::string header_line;
    std::getline(file, header_line);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string recipe_id_str, recipe_name, ingredient_name, quantity_str, state;
        if (std::getline(iss, recipe_id_str, ',') &&
            std::getline(iss, recipe_name, ',') &&
            std::getline(iss, ingredient_name, ',') &&
            std::getline(iss, quantity_str, ',') &&
            std::getline(iss, state, ',')) {

            int recipe_id = std::stoi(recipe_id_str);
            double quantity = std::stod(quantity_str);

            recipe_items_.emplace_back(recipe_id, recipe_name, ingredient_name, quantity, state);
        }
    }
}

void Recipe::visualize_recipes() const {
    int previous_recipe_id = -1;  // Initialize with a value that won't match any recipe ID
    std::string previous_recipe_name;

    for (const auto& item : recipe_items_) {
        if (item.recipe_id() != previous_recipe_id || item.recipe_name() != previous_recipe_name) {
            std::cout << std::endl;
            std::cout << "Recipe ID: " << item.recipe_id() << std::endl;
            std::cout << "Recipe Name: " << item.recipe_name() << std::endl;
            std::cout << "Ingredients:" << std::endl;

            previous_recipe_id = item.recipe_id();
            previous_recipe_name = item.recipe_name();
        }

        std::cout << item.ingredient_name() << " "
                  << item.ingredient_quantity() << " "
                  << item.ingredient_state() << std::endl;
    }
}


void Recipe::check_sufficient_ingredients(int recipe_id, Inventory inventory) const {
    // Find the recipe items matching the given recipe ID
    std::vector<const RecipeItem*> items;
    for (const auto& item : recipe_items_) {
        if (item.recipe_id() == recipe_id) {
            items.push_back(&item);
        }
    }

    bool insufficient = false;

    // Check if there are enough ingredients in the inventory
    for (const auto& item : items) {
        const std::string& ingredient_name = item->ingredient_name();
        const std::string& ingredient_state = item->ingredient_state();
        double ingredient_quantity = item->ingredient_quantity();

        // Search for matching items in the inventory by name
        const std::vector<InventoryItem*> matching_items = inventory.search_by_name(ingredient_name);

        double total_quantity = 0.0;
        for (const auto& matching_item : matching_items) {
            if (!matching_item->is_expired()) {
                total_quantity += matching_item->quantity();
            }
        }

        // Check if the total quantity is sufficient
        if (total_quantity < ingredient_quantity) {
            insufficient = true;
            double additional_quantity_needed = ingredient_quantity - total_quantity;
            std::cout << "Insufficient quantity of ingredient '" << ingredient_name << "' in the inventory."
                      << " Additional " << additional_quantity_needed << ' ' << item->ingredient_state() << " needed." << std::endl;
        }
    }

    if(!insufficient) std::cout<< "There are enough ingredients\n";
}
