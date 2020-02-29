#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
   public:
    Person(const string& _name, const string& _type) : name(_name), type(_type) {}
    string GetName() const { return name; }
    string GetType() const { return type; }
    virtual void Walk(const string& destination) const {
        cout << GetType() << ": " << GetName() << " walks to: " << destination << endl;
    }

   private:
    string name;
    string type;
};

class Student : public Person {
   public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student") {
        FavouriteSong = favouriteSong;
    }

    void Learn() const {
        cout << "Student: " << GetName() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
    }

   public:
    string FavouriteSong;
};

class Teacher : public Person {
   public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher") {
        Subject = subject;
    }
    void Teach() const {
        cout << "Teacher: " << GetName() << " teaches: " << Subject << endl;
    }

   public:
    string Subject;
};

class Policeman : public Person {
   public:
    Policeman(const string& name) : Person(name, "Policeman") {
    }
    void Check(const Person& person) const {
        cout << "Policeman: " << GetName() << " checks " << person.GetType()
             << ". " << person.GetType() << "'s name is: " << person.GetName()
             << endl;
    }
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const auto& p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
