#include "pch.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <istream>
#include "gtest\gtest.h"
#include "..\StringRedactor\Editor.h"
#include "..\StringRedactor\CommandParser.h"

TEST(COPY, FirstTest) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"copy 0, 1\n" //0 - включительно, считаем с 0 индекса, правый невключ. [0, 1)
		"paste 0\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "aabc");
}

TEST(COPY, CopyWholeTest) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"copy 0, 4\n"
		"paste 0\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abcabc");
}

TEST(COPY, Copy_text_position_beyond_doc) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"copy 0, 4\n"
		"paste 3\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abcabc");
}

TEST(COPY, Copy_text_position_beyond_doc_) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"copy 0, 3\n"
		"paste 5\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), std::string("abc  abc"));
}

TEST(COPY, Copy_text_paste_at_right_boundary) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"copy 0, 4\n"
		"paste 3\n" /*вставка между указанной позицией и предыдущей*/
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), std::string("abcabc"));
}

TEST(COPY, copy_from_empty) {
	std::string str = "";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"copy 2"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "");
}

TEST(PASTE, empty_buffer_to_paste) {
	std::string str = "";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"paste 2"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "");
}

TEST(INSERT, empty_doc_insert) {
	std::string str = "";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"hello\", 0"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "hello");
}

TEST(INSERT, empty_doc_insert_with_offset) {
	std::string str = "";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"hello\", 2"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "  hello");
}

TEST(INSERT, regular_doc) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"hello\", 0"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "helloabc");
}

TEST(INSERT, regular_doc_) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"hello\", 1"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "ahellobc");
}

TEST(INSERT, insert_beyond_boundaries) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"hello\", 3"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abchello");
}

TEST(INSERT, insert_beyond_boundaries_) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"hello\", 4"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) { 
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc hello");
}

TEST(INSERT, insert_nothing) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"\", 0"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc");
}

TEST(INSERT, insert_nothing_beyond_the_line) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"\", 3"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc");
}

TEST(INSERT, insert_nothing_beyond_the_line_with_gap) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"\", 4"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc");
}

TEST(INSERT, insert_at_negative_position) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"\", -4"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc");
}

TEST(DELETE, empty_doc) {
	std::string str = "";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 2, 5"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "");
}

TEST(DELETE, indexes_beyond) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 5"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "");
}

TEST(DELETE, several_deletes) {
	std::string str = "This is a long string";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 1\n"
		"delete 1, 2\n"
		"delete 2, 3\n"
		"delete 4, 5\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "hsisa long string");
}

TEST(DELETE, regular) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 1"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "bc");
}

TEST(DELETE, start_higher_than_end) {
	std::string str = "abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 2, 1"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc");
}

TEST(DELETE, regular_) {
	std::string str = "abc abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 3, 7"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc");
}

TEST(UNDO, regular_) {
	std::string str = "abc abc";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 3, 7\n"
		"undo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abc abc");
}

TEST(REDO, regular) {
	std::string str = "abcd";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 1\n"
		"undo\n"
		"redo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "bcd");
}

TEST(UNDO, more_than_commands) {
	std::string str = "abcd";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 1\n"
		"undo\n"
		"undo\n"
		"undo\n"
		"undo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abcd");
}

TEST(UNDO, last_two_commands_denied) {
	std::string str = "abcd";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 1\n"
		"insert \"hello\", 1\n"
		"delete 2, 6\n"
		"undo\n"
		"undo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "bcd");
}


TEST(UNDO, no_commands_to_undo) {
	std::string str = "abcd";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"undo\n"
		"undo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "abcd");
}

TEST(MIXED_CMDS, redo_undo) {
	std::string str = "abcd";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 1\n"
		"insert \"hello\", 1\n"
		"undo\n"
		"redo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "bhellocd");
}

TEST(MIXED_CMDS, delete_undo_redo) {
	std::string str = "Hello!\nThis is my new OOP program!";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"delete 0, 6\n" /*\nThis is my new OOP program!*/
		"delete 1, 3\n" /*\nis is my new OOP program!*/
		"delete 1, 2\n" /*\ns is my new OOP program!*/
		"undo\n" /*\nis is my new OOP program!*/
		"redo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "\ns is my new OOP program!");
}

TEST(MIXED_CMDS, insert_undo_redo) {
	std::string str = "Hello!\n";
	auto doc = std::make_shared<Document>(str);
	LineEditor editor;
	std::stringstream ss(
		"insert \"This is my new program!\", 7\n"
		"undo\n"
		"redo\n"
	);
	CmdParser parser(ss, doc);
	for (auto cmd : parser) {
		editor.execute(cmd);
	}
	EXPECT_EQ(doc->text(), "Hello!\nThis is my new program!");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}