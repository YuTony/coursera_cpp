#include <list>
#include <string>
#include "test_runner.h"
using namespace std;

class Editor {
   public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() : cursor(data.begin()) {}
    void Left() {
        if (cursor != data.begin()) {
            cursor--;
        }
    }
    void Right() {
        if (cursor != data.end()) {
            cursor++;
        }
    }
    void Insert(char token) {
        data.insert(cursor, token);
    }
    void Cut(size_t tokens = 1) {
        clipboard.clear();
        auto point = cursor;
        for (size_t i = 0; i < tokens; i++) {
            Right();
        }
        clipboard.splice(clipboard.begin(), data, point, cursor);
    }
    void Copy(size_t tokens = 1) {
        clipboard.clear();
        auto it = cursor;
        for (size_t i = 0; i < tokens; i++) {
            clipboard.push_back(*(it++));
        }
    }
    void Paste() {
        for (char c : clipboard) {
            data.insert(cursor, c);
        }
    }
    string GetText() const {
        return {data.begin(), data.end()};
    }

   private:
    list<char> data;
    list<char>::iterator cursor;
    list<char> clipboard;
};

void TypeText(Editor& editor, const string& text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}