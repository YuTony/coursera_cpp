#include <algorithm>
#include <string>
#include <list>
#include <string_view>
#include "test_runner.h"
#include "profile.h"
using namespace std;

class Editor {
public:
	Editor()
		: cursor(text.begin())
	{
	}

	void Left() {
		if (cursor != text.begin()) {
			--cursor;
		}
	}

	void Right() {
		if (cursor != text.end()) {
			++cursor;
		}
	}

	void Insert(char token) {
		text.insert(cursor, token);
	}

	void Cut(size_t tokens = 1) {
		Copy(tokens);
		for (size_t i = 0; (i < tokens) && (cursor != text.end()); ++i) {
			cursor = text.erase(cursor);
		}
	}

	void Copy(size_t tokens = 1) {
		auto it = cursor;
		for (size_t i = 0; (i < tokens) && (it != text.end()); ++i) {
			++it;
		}
		buf = string(cursor, it);
		buf_sv = buf;
	}

	void Paste() {
		for (auto it = buf_sv.begin(); it != buf_sv.end(); ++it) {
			text.insert(cursor, *it);
		}
	}

	string GetText() const {
		return string(text.begin(), text.end());
	}

private:
	list<char> text;
	list<char>::iterator cursor;
	string_view buf_sv;
	string buf;
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
	{
		Editor editor;

		TypeText(editor, "world");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Left();
		TypeText(editor, "hello_");

		ASSERT_EQUAL(editor.GetText(), "hello_world");
	}
	{
		Editor editor;

		TypeText(editor, "abcdef");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "abf");
	}
	{
		Editor editor;

		TypeText(editor, "1234567");
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Paste();
		editor.Paste();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "123456667");
	}
	{
		Editor editor;
		string s(1'000'000, 'a');

		LOG_DURATION("1000000 inserts");
		TypeText(editor, s);
		for (int i = 0; i < 1'000'000; i++) {
			editor.Left();
		}

		for (int i = 0; i < 1000; i++) {
			editor.Cut(1000);
			editor.Paste();
		}

		ASSERT_EQUAL(editor.GetText(), s);
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

void TestCut()
{
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcde");
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	//5
	editor.Cut(5);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bcde");
	editor.Right();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
	Editor editor;
	//1
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	ASSERT_EQUAL(editor.GetText(), "a");
	//2
	editor.Copy(1);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");//between a
	//3
	editor.Copy(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcdea");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	RUN_TEST(tr, TestCut);
	RUN_TEST(tr, TestCopy);

	return 0;
}
