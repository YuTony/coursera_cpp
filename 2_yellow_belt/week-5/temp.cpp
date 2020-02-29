#include <iostream>
#include <string>
#include <vector>

using namespace std;

class People {
   public:
    People(const string& name, const string& occupation) : Name(name), Occupation(occupation){};
    virtual void Walk(const string& destination) const {
        cout << Occupation << ": " << Name << " walks to: " << destination << endl;
    }
    string GetName() const { return Name; }
    string GetOccup() const { return Occupation; }
    void Output() const {
        cout << GetOccup() << ": " << GetName();
    }

   private:
    const string Name;
    const string Occupation;
};

class Student : public People {
   public:
    Student(const string& name, const string& favouriteSong) : People(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        Output();
        cout << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        People::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        Output();
        cout << " sings a song: " << FavouriteSong << endl;
    }

   public:
    string FavouriteSong;
};

class Teacher : public People {
   public:
    Teacher(const string& name, const string& subject) : People(name, "Teacher"), Subject(subject){};

    void Teach() const {
        Output();
        cout << " teaches: " << Subject << endl;
    }

   public:
    string Subject;
};

class Policeman : public People {
   public:
    Policeman(const string& name) : People(name, "Policeman"){};

    void Check(const People& t) const {
        Output();
        cout << " checks " << GetOccup() << "." << GetOccup() << "'s name is: " << GetName() << endl;
    }
};

void VisitPlaces(const People& t, const vector<string>& places) {
    for (auto p : places) {
        t.Walk(p);
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