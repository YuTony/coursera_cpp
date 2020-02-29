#include <iostream>
#include <vector>
using namespace std;

struct Specialization {
    string val;
    explicit Specialization(string v) {
        val = v;
    }
};

struct Course {
    string val;
    explicit Course(string v) {
        val = v;
    }
};

struct Week {
    string val;
    explicit Week(string v) {
        val = v;
    }
};

struct LectureTitle {
    string specialization;
    string course;
    string week;
    LectureTitle(Specialization v1, Course v2, Week v3) {
        specialization = v1.val;
        course = v2.val;
        week = v3.val;
    }
};