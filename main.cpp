#include "Headers.h"
#include "InventoryItem.h"
#include "Inventory.h"
#include "RecipeItem.h"
#include "Recipe.h"

void clear_input_stream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int get_integer_input() {
    int value;
    while (true) {
        if (std::cin >> value) {
            // Input is valid, break the loop
            break;
        } else {
            // Clear the error flag and input stream
            clear_input_stream();
            std::cout << "Invalid input. Please enter an integer: ";
        }
    }
    return value;
}

double get_double_input() {
    double value;
    while (true) {
        if (std::cin >> value) {
            // Input is valid, break the loop
            break;
        } else {
            // Clear the error flag and input stream
            clear_input_stream();
            std::cout << "Invalid input. Please enter a double: ";
        }
    }
    return value;
}

std::string get_string_input() {
    std::string value;
    while (true) {
        if (std::cin >> value) {
            // Input is valid, break the loop
            break;
        } else {
            // Clear the error flag and input stream
            clear_input_stream();
            std::cout << "Invalid input. Please enter a string: ";
        }
    }
    return value;
}

char get_char_input() {
    char value;
    while (true) {
        if (std::cin >> value && (value == 'y' || value == 'n')) {
            // Input is valid, break the loop
            break;
        } else {
            // Clear the error flag and input stream
            clear_input_stream();
            std::cout << "Invalid input. Please enter a character (y or n): ";
        }
    }
    return value;
}

void run_inventory_menu(Inventory& inventory, Recipe& recipe_list) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "======= Inventory Menu =======\n";
        std::cout << "0: Exit\n";
        std::cout << "1: View inventory\n";
        std::cout << "2: Add item to inventory\n";
        std::cout << "3: Remove item from inventory\n";
        std::cout << "4: Search items by name\n";
        std::cout << "5: Search items by category\n";
        std::cout << "6: Update item from inventory\n";
        std::cout << "7: Check expiration date of item\n";
        std::cout << "8: Check ingredients for given recipe\n";
        std::cout << "9: Reset inventory\n";
        std::cout << "==============================\n";
        std::cout << "Enter your choice: ";
        choice = get_integer_input();
        switch (choice) {
            case 0: {
                std::cout << "Exiting inventory menu...\n";
                std::cout << "Do you want to save the inventory? (y/n): ";
                char answer;
                answer = get_char_input();
                if (answer == 'y') {
                    std::ofstream file("C:\\Users\\denis\\CLionProjects\\pp_cpp\\inventory.csv");
                    if (!file) {
                        std::cerr << "Failed to open file for writing: inventory.csv\n";
                        return;
                    }
                    for (int i = 0; i < inventory.size(); ++i) {
                        const InventoryItem& item = inventory[i];
                        file << item.id() << ',' << item.name() << ',' << item.category()
                             << ',' << item.state() << ',' << item.quantity() << ','
                             << item.expiration_date() << '\n';
                    }
                    std::cout << "Inventory saved to inventory.csv\n";
                }
                return;
            }
            case 1: {
                std::cout << "Inventory:\n";
                for (int i = 0; i < inventory.size(); ++i) {
                    const InventoryItem &item = inventory[i];
                    std::cout << item.id() << ", " << item.name() << ", "
                              << item.category() << ", " << item.state() << ", "
                              << item.quantity() << ", " << item.expiration_date()
                              << "\n";
                }
                break;
            }
            case 2: {
                int id;
                std::string name, category, state, expiration_date;
                double quantity;
                std::cout << "Enter item ID: ";
                id = get_integer_input();
                std::cout << "Enter item name: ";
                name = get_string_input();
                std::cout << "Enter item category: ";
                category = get_string_input();
                std::cout << "Enter item state (kilograms or liters): ";
                state = get_string_input();
                while(true) {
                    if(state != "kilograms" && state != "liters") {
                        std::cout << "Invalid input, please select kilograms or liters: ";
                        state = get_string_input();
                    }
                    else break;
                }
                std::cout << "Enter item quantity: ";
                quantity = get_double_input();
                std::cout << "Enter item expiration date (dd/mm/yy): ";
                expiration_date = get_string_input();
                std::regex date_regex(R"(^\d{2}/\d{2}/\d{2}$)");
                while(true) {
                    if(std::regex_match(expiration_date, date_regex)) break;
                    else {
                        std::cout << "Invalid input, please select a valid expiration date (dd/mm/yy): ";
                        expiration_date = get_string_input();
                    }
                }
                InventoryItem item(id, name, category, state, quantity, expiration_date);
                inventory.add_item(item);
                std::cout << "Item added to inventory.\n";
                break;
            }
            case 3: {
                int id;
                std::cout << "Enter the ID of the item to delete: ";
                id = get_integer_input();
                inventory.remove_item(id);
                std::cout << "Item with ID " << id << " deleted.\n";
                break;
            }
            case 4: {
                std::string name;
                std::cout << "Enter item name to search: ";
                name = get_string_input();
                bool found = false;
                for (int i = 0; i < inventory.size(); ++i) {
                    const InventoryItem& item = inventory[i];
                    if (item.name() == name) {
                        found = true;
                        std::cout << item.id() << ", " << item.name() << ", "
                                  << item.category() << ", " << item.state() << ", "
                                  << item.quantity() << ", " << item.expiration_date() << "\n";
                    }
                }
                if (!found) {
                    std::cout << "No items with name " << name << " found in inventory.\n";
                }
                break;
            }
            case 5: {
                std::string category;
                std::cout << "Enter item category to search: ";
                category = get_string_input();
                bool found = false;
                for (int i = 0; i < inventory.size(); ++i) {
                    const InventoryItem& item = inventory[i];
                    if (item.category() == category) {
                        found = true;
                        std::cout << item.id() << ", " << item.name() << ", "
                                  << item.category() << ", " << item.state() << ", "
                                  << item.quantity() << ", " << item.expiration_date() << "\n";
                    }
                }
                if (!found) {
                    std::cout << "No items with name " << category << " found in inventory.\n";
                }
                break;
            }
            case 6: {
                int id;
                std::cout << "Enter the ID of the item to update: ";
                id = get_integer_input();

                // Check if the item with the given ID exists in the inventory
                bool item_found = false;
                for (int i = 0; i < inventory.size(); ++i) {
                    const InventoryItem& item = inventory[i];
                    if (item.id() == id) {
                        item_found = true;
                        break;
                    }
                }

                if (item_found) {
                    std::string name, category, state, expiration_date;
                    double quantity;
                    std::cout << "Enter item name: ";
                    name = get_string_input();
                    std::cout << "Enter item category: ";
                    category = get_string_input();
                    std::cout << "Enter item state (kilograms or liters): ";
                    state = get_string_input();
                    while(true) {
                        if(state != "kilograms" && state != "liters") {
                            std::cout << "Invalid input, please select kilograms or liters: ";
                            state = get_string_input();
                        }
                        else break;
                    }
                    std::cout << "Enter item quantity: ";
                    quantity = get_double_input();
                    std::cout << "Enter item expiration date (dd/mm/yy): ";
                    expiration_date = get_string_input();
                    std::regex date_regex(R"(^\d{2}/\d{2}/\d{2}$)");
                    while(true) {
                        if(std::regex_match(expiration_date, date_regex)) break;
                        else {
                            std::cout << "Invalid input, please select a valid expiration date (dd/mm/yy): ";
                            expiration_date = get_string_input();
                        }
                    }
                    inventory.update_item(id, name, category, state, quantity, expiration_date);
                    std::cout << "Item with ID " << id << " updated.\n";
                } else {
                    std::cout << "Item with ID " << id << " not found in inventory.\n";
                }
                break;
            }
            case 7: {
                int id;
                std::cout << "Enter the ID of the item to check expiration: ";
                id = get_integer_input();
                // Check if the item with the given ID exists in the inventory
                bool item_found = false;
                for (int i = 0; i < inventory.size(); ++i) {
                    const InventoryItem& item = inventory[i];
                    if (item.id() == id) {
                        item_found = true;
                        break;
                    }
                }

                if (item_found) {
                    bool is_expired = inventory.is_item_expired(id);
                    if (is_expired) {
                        std::cout << "Item with ID " << id << " is expired.\n";
                    } else {
                        std::cout << "Item with ID " << id << " is not expired.\n";
                    }
                } else {
                    std::cout << "Item with ID " << id << " not found in inventory.\n";
                }
                break;
            }
                break;
            case 8: {
                std::cout << "Here are the recorded recipes:" << std::endl;
                recipe_list.visualize_recipes();
                std::cout << "\nEnter the ID for the recipe wanted: ";
                int id;
                id = get_integer_input();
                recipe_list.check_sufficient_ingredients(id, inventory);
                break;
            }
            case 9: {
                std::cout << "Are you sure you want to reset the inventory? (y/n): ";
                char answer;
                answer = get_char_input();
                if (answer == 'y')
                {
                    inventory.reset();
                    std::cout << "The inventory was reset!\n";
                }
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

int main() {
    Inventory inventory;
    Recipe recipe_list;

    recipe_list.load_recipes_from_csv("C:\\Users\\denis\\CLionProjects\\pp_cpp\\recipes.csv");

    load_inventory_from_csv("C:\\Users\\denis\\CLionProjects\\pp_cpp\\inventory.csv", inventory);

    // Display the inventory menu
    run_inventory_menu(inventory, recipe_list);

    return 0;
}
