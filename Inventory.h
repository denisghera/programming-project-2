class Inventory {
public:
    void add_item(const InventoryItem& item) { items_.push_back(item); }
    void remove_item(int id);
    void reset();
    void update_item(int id, const std::string& name, const std::string& category,
                     const std::string& state, double quantity, const std::string& expiration_date);

    const std::vector<InventoryItem*> search_by_name(const std::string& name);
    const std::vector<InventoryItem*> search_by_category(const std::string& name);

    int size() const { return items_.size(); }
    const InventoryItem& operator[](int index) const { return items_[index]; }
    bool is_item_expired(int id) const;

private:
    std::vector<InventoryItem> items_;
};

void Inventory::remove_item(int id) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (it->id() == id) {
            items_.erase(it);
            return;
        }
    }
}
void Inventory::reset() {
    items_.clear();
}

const std::vector<InventoryItem*> Inventory::search_by_name(const std::string& name) {
    std::vector<InventoryItem*> matching_items;
    for (auto& item : items_) {
        if (item.name() == name) {
            matching_items.push_back(&item);
        }
    }
    return matching_items;
}

const std::vector<InventoryItem*> Inventory::search_by_category(const std::string& category) {
    std::vector<InventoryItem*> matching_items;
    for (auto& item : items_) {
        if (item.category() == category) {
            matching_items.push_back(&item);
        }
    }
    return matching_items;
}

void Inventory::update_item(int id, const std::string& name, const std::string& category,
                            const std::string& state, double quantity, const std::string& expiration_date) {
    for (auto& item : items_) {
        if (item.id() == id) {
            item.update_item(name, category, state, quantity, expiration_date);
            return;
        }
    }
}

bool Inventory::is_item_expired(int id) const {
    for (const auto& item : items_) {
        if (item.id() == id) {
            return item.is_expired();
        }
    }
    return false;  // Item not found in the inventory
}

void load_inventory_from_csv(const std::string& filename, Inventory& inventory) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string header_line;
    std::getline(file, header_line);

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string id_str, name, category, state, quantity_str, expiration_date;
        std::getline(ss, id_str, ',');
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, state, ',');
        std::getline(ss, quantity_str, ',');
        std::getline(ss, expiration_date);

        int id = std::stoi(id_str);
        double quantity = std::stod(quantity_str);

        InventoryItem item(id, name, category, state, quantity, expiration_date);
        inventory.add_item(item);
    }
}