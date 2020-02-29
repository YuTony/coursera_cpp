#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
   public:
    Person(const string& name, const string& occupation) : Name(name),
                                                           Occupation(occupation) {}

    string getName() const {
        return Name;
    }
    string getOccupation() const {
        return Occupation;
    }

    string output() const {
        return getOccupation() + ": " + getName();
    }

    virtual void Walk(const string& destination) const {
        cout << output() << " walks to: " << destination << endl;
    }

   private:
    const string Name;
    const string Occupation;
};

class Student : public Person {
   public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << output() << " learns" << endl;
    }

    void SingSong() const {
        cout << output() << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

   public:
    const string FavouriteSong;
};

class Teacher : public Person {
   public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << output() << " teaches: " << Subject << endl;
    }

   private:
    const string Subject;
};

class Policeman : public Person {
   public:
    Policeman(const string& name) : Person(name, "Policeman") {}

    void Check(const Person& p) const {
        cout << output() << " checks " << p.getOccupation() << ". " << p.getOccupation() << "'s name is: " << p.getName() << endl;
    }
};

void VisitPlaces(const Person& p, const vector<string>& places) {
    for (auto i : places) {
        p.Walk(i);
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