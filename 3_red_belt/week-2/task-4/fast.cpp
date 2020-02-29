#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class ReadingManager {
   public:
    ReadingManager() : pages(1001, 0) {}

    void Read(int user_id, int page_count) {
        if (user_page.count(user_id) != 0) {
            pages[user_page[user_id]]--;
        }
        user_page[user_id] = page_count;
        pages[page_count]++;
    }

    double Cheer(int user_id) const {
        if (user_page.count(user_id) == 0) {
            return 0;
        }
        if (user_page.size() == 1) {
            return 1;
        }
        const int& page = user_page.at(user_id);
        int count = 0;
        for (int i = 1; i < page; i++) {
            count += pages[i];
        }
        return count * 1.0 / (user_page.size() - 1);
    }

   private:
    vector<int> pages;        //колличество пользователей для каждой страницы
    map<int, int> user_page;  //пользователь и его страница
};

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}