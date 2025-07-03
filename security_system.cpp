#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct FurnitureEvent {
    int row_furniture;
    int end_row_value;
    int type_value; // +1 for start, -1 for end
    int furnitures_id;
    

    // Sorting events: start events come before end events at the same row_furniture
    bool operator<(const FurnitureEvent& other) const {
        if (row_furniture != other.row_furniture)
            return row_furniture < other.row_furniture;
        return type_value > other.type_value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int total_rows, furniture_count, max_allowed_per_row;
    std::cin >> total_rows >> furniture_count >> max_allowed_per_row;

    std::vector<FurnitureEvent> events;

    for (int i = 0; i < furniture_count; ++i) {
        int start_row, start_col, end_row_value, end_col;
        std::cin >> start_row >> start_col >> end_row_value >> end_col;

        events.push_back({ start_row, +1, i, end_row_value });       // Furniture appears
        events.push_back({ end_row_value + 1, -1, i, end_row_value });     // Furniture ends after this row_furniture
    }

    std::sort(events.begin(), events.end());

    std::set<std::pair<int, int>> active_furnitures; // (end_row_value, furnitures_id)
    std::vector<bool> is_removed(furniture_count, false);
    int total_removed = 0;

    for (size_t i = 0; i < events.size(); ) {
        int current_row = events[i].row_furniture;

        // Process all events at current_row
        size_t j = i;
        while (j < events.size() && events[j].row_furniture == current_row) {
            const FurnitureEvent& event = events[j];
            if (event.type_value == +1) {
                if (!is_removed[event.furnitures_id]) {
                    active_furnitures.insert({ event.end_row_value, event.furnitures_id });
                }
            }
            else {
                if (!is_removed[event.furnitures_id]) {
                    active_furnitures.erase({ event.end_row_value, event.furnitures_id });
                }
            }
            ++j;
        }

        // If current row_furniture is within room bounds, enforce furniture limit
        if (current_row <= total_rows && active_furnitures.size() > static_cast<size_t>(max_allowed_per_row)) {
            int to_remove = active_furnitures.size() - max_allowed_per_row;

            for (int r = 0; r < to_remove; ++r) {
                if (active_furnitures.empty()) break;

                auto fur_to_remove = *active_furnitures.rbegin();
                active_furnitures.erase(std::prev(active_furnitures.end()));

                is_removed[fur_to_remove.second] = true;
                total_removed++;
            }
        }

        i = j;
    }

    std::cout << total_removed << "\n";
    return 0;
}