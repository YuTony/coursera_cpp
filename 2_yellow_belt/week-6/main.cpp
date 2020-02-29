#include "condition_parser.cpp"
#include "condition_parser_test.cpp"
#include "database.cpp"
#include "date.cpp"
#include "node.h"
#include "test_runner.cpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    string event;
    getline(is, event);
    auto it = find_if(event.begin(), event.end(), [](int ch) {
        return !isspace(ch);
    });
    event.erase(event.begin(), it);
    return event;
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestDb() {
    {
        Database db;
        db.Add({1, 1, 1}, "e4");
        db.Add({1, 1, 1}, "e6");
        db.Add({1, 1, 1}, "e2");
        db.Add({1, 1, 1}, "e3");
        db.Add({1, 1, 1}, "e2");
        db.Add({1, 1, 1}, "e1");
        db.Add({1, 1, 1}, "e1");
        stringstream ss;
        db.Print(ss);
        AssertEqual(ss.str(), "0001-01-01 e4\n0001-01-01 e6\n0001-01-01 e2\n0001-01-01 e3\n0001-01-01 e1\n", "test Add");
    }
    {
        // Add 2017-01-01 Holiday
        // Add 2017-03-08 Holiday
        // Add 2017-01-01 New Year
        // Find event != "working day"

        // 2017-01-01 Holiday
        // 2017-01-01 New Year
        // 2017-03-08 Holiday
        Database db;
        db.Add({2017, 1, 1}, "Holiday");
        db.Add({2017, 3, 8}, "Holiday");
        db.Add({2017, 1, 1}, "New Year");
        stringstream ss;
        ss << "event != \"working day\"";
        auto condition = ParseCondition(ss);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        AssertEqual(db.FindIf(predicate), vector<pair<Date, string>>{{{2017, 1, 1}, "Holiday"}, {{2017, 1, 1}, "New Year"}, {{2017, 3, 8}, "Holiday"}}, "test FindIf");
    }
    // {
    //     Database db;
    //     db.Add({2017, 1, 1}, "Holiday");
    //     db.Add({2017, 3, 8}, "Holiday");
    //     db.Add({2017, 1, 1}, "New Year");
    //     stringstream ss;
    //     ss << "data == 2017-1-1";
    //     auto condition = ParseCondition(ss);
    //     auto predicate = [condition](const Date& date, const string& event) {
    //         return condition->Evaluate(date, event);
    //     };
    //     db.RemoveIf(predicate);
    //     AssertEqual(db.Print(), vector<pair<Date, string>>{{{2017, 1, 1}, "Holiday"}, {{2017, 3, 8}, "Holiday"}}, "test RemoveIf");
    // }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDb, "TestDb");
}
