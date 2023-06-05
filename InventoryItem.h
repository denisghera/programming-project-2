class InventoryItem {
public:
    InventoryItem(int id, const std::string& name, const std::string& category,
                  const std::string& state, double quantity, const std::string& expiration_date)
            : id_(id), quantity_(quantity), expiration_date_(expiration_date) {
        name_.push_back(name);
        category_.push_back(category);
        state_.push_back(state);
    }

    int id() const { return id_; }
    const std::string& name() const { return name_[0]; }
    const std::string& category() const { return category_[0]; }
    const std::string& state() const { return state_[0]; }
    double quantity() const { return quantity_; }
    const std::string& expiration_date() const { return expiration_date_; }

    void add_name(const std::string& name) { name_.push_back(name); }
    void add_category(const std::string& category) { category_.push_back(category); }
    void add_state(const std::string& state) { state_.push_back(state); }
    void update_item(const std::string& name, const std::string& category,
                     const std::string& state, double quantity, const std::string& expiration_date) {
        name_.clear();
        category_.clear();
        state_.clear();

        name_.push_back(name);
        category_.push_back(category);
        state_.push_back(state);
        quantity_ = quantity;
        expiration_date_ = expiration_date;
    }
    bool is_expired() const {
        std::time_t now = std::time(nullptr);
        std::tm current_time = *std::localtime(&now);
        std::tm expiration = parse_date(expiration_date_);

        return std::mktime(&expiration) < std::mktime(&current_time);
    }

private:
    int id_;
    std::vector<std::string> name_;
    std::vector<std::string> category_;
    std::vector<std::string> state_;
    double quantity_;
    std::string expiration_date_;
    std::tm parse_date(const std::string& date_str) const {
        std::istringstream ss(date_str);
        std::tm date = {};
        ss >> std::get_time(&date, "%d/%m/%y");

        // Adjust two-digit year to a four-digit year
        date.tm_year += (date.tm_year < 70) ? 100 : 0;

        return date;
    }
};