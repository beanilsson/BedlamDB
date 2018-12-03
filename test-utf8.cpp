#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
#include <vector>
#include <filesystem>
#include "manual.h"

using namespace std;
namespace fs = std::experimental::filesystem;

const string path = "db_data";
const string extension = ".bedl";
const string prompt = "$ ";

void db_open(string file_input, string file_name, string db_path) {
        string keywords[6] = { "print_content", "print_entry", "insert", "quit", "print_content_reverse", "insert_bulk" };
        ifstream in(db_path);
        while (true) {
                std::cout << file_name << prompt;
                std::getline(cin, file_input);
                size_t space_index = file_input.find(" ");
                string command;
                string option;

                if (space_index != string::npos) {
                        command = file_input.substr(0, space_index);
                        option = file_input.substr(file_input.find(" ") + 1);
                }
                else {
                        command = file_input;
                }
                if (command == keywords[0]) {
                        ifstream db_content(db_path);
                        string content;
                        if (db_content.is_open())
                        {
                                while (getline(db_content, content))
                                {
                                        std::cout << content;
                                }
                                std::cout << endl;
                                db_content.close();
                        }

                        else std::cout << "Unable to open database" << endl;
                }
                else if (command == keywords[1]) {
                        ifstream db_content(db_path);
                        string content;
                        vector <string> items;
                        string temp_item = "";
                        if (db_content.is_open())
                        {
                                while (getline(db_content, content))
                                {
                                        for (char& c : content) {
                                                if (c != '{' && c != '}') {
                                                        temp_item += c;
                                                }
                                                else if (c == '}') {
                                                        items.push_back(temp_item);
                                                        temp_item = "";
                                                }
                                        }
                                        for (int i = 0; i < items.size(); i++) {
                                                int result = items[i].find(option);
                                                if (result == 0) {
                                                        std::cout << items[i] << std::endl;
                                                }
                                        }
                                }
                                db_content.close();
                        }

                        else std::cout << "Unable to open file" << endl;
                }
                else if (command == keywords[2]) {
                        ifstream in(db_path.c_str());

                        if (!in) {
                                cerr << "Cannot open db: " << db_path << endl;
                        }

                        string str;
                        vector<string> db_content;

                        while (in >> str) {
                                db_content.push_back(str);
                        }

                        string formatted_input = "{" + option + "}";
                        db_content.insert(db_content.end(), formatted_input);

                        ofstream db_file_write;
                        db_file_write.open(db_path);
                        for (const auto &e : db_content) {
                                if (e[e.length() - 1] == '}') {
                                        db_file_write << e;
                                }
                                else {
                                        db_file_write << e;
                                }

                        }
                        db_file_write.close();
                        in.close();
                        std::cout << "Data saved to db" << std::endl;
                }
                else if (command == keywords[3]) {
                        break;
                }
                else if (command == keywords[4]) {
                        ifstream db_content(db_path);
                        string content;
                        vector<std::string> content_vector;
                        string temp_item = "";

                        if (db_content.is_open())
                        {
                                while (getline(db_content, content))
                                {
                                        for (char& c : content) {
                                                if (c != '{' && c != '}') {
                                                        temp_item += c;
                                                }
                                                else if (c == '}') {
                                                        content_vector.push_back("{" + temp_item + "}");
                                                        temp_item = "";
                                                }

                                        }

                                }
                                for (int i = content_vector.size() - 1; i >= 0; i--) {
                                        std::cout << content_vector[i];
                                }
                                std::cout << endl;
                                db_content.close();
                        }

                        else std::cout << "Unable to open database" << endl;
                }
                else if (command == keywords[5]) {
                ifstream in(db_path.c_str());

                        if (!in) {
                                cerr << "Cannot open db: " << db_path << endl;
                        }

                        string str;
                        vector<string> db_content;

                        while (in >> str) {
                                db_content.push_back(str);
                        }

                        db_content.insert(db_content.end(), option);

                        ofstream db_file_write;
                        db_file_write.open(db_path);
                        for (const auto &e : db_content) {
                                if (e[e.length() - 1] == '}') {
                                        db_file_write << e;
                                }
                                else {
                                        db_file_write << e;
                                }

                        }
                        db_file_write.close();
                        in.close();
                        std::cout << "Data saved to db" << std::endl;
        }
                else {
                        std::cout << "Invalid input" << std::endl;
                }
                in.close();
        }
}

void open_db(string file_name) {
        string file_input;
        string db_path = path;
        db_path += "/";

        file_name += extension;
        db_path += file_name;
        ifstream in(db_path);


        if (!in) {
                std::cout << "Created new db " << file_name << std::endl;
                std::cout << "Input to db: ";
                ofstream db_file_write;
                db_file_write.open(db_path);
                getline(cin, file_input);
                db_file_write << "{" << file_input << "}";
                in.close();
                db_file_write.close();
                std::cout << "Data saved to db" << std::endl;
                db_open(file_input, file_name, db_path);
        }
        else {
                std::cout << "Opened db with name " << file_name << std::endl;
                db_open(file_input, file_name, db_path);
        }
}

int menu() {
        string menu;
        string keywords[5] = { "open_db", "print_db_names", "delete_db", "quit", "manual" };
        _mkdir("db_data");
        std::cout << "BedlamDB!" << std::endl;
        std::cout << "Tip: Open the manual by entering the 'manual' command" << std::endl;
        while (true) {
                std::cout << prompt;
                std::getline(cin, menu);
                size_t space_index = menu.find(" ");
                string command;
                string option = "";

                if (space_index != string::npos) {
                        command = menu.substr(0, space_index);
                        option = menu.substr(menu.find(" ") + 1);
                }
                else {
                        command = menu;
                }

                if (command == keywords[0]) {
                        if (option != "") {
                                open_db(option);
                        }
                        else {
                                std::cout << "No database name specified, try again" << std::endl;
                        }
                }
                else if (command == keywords[1]) {
                        string db_path;
                        for (auto& p : fs::directory_iterator(path))
                                db_path = p.path().u8string();
                        db_path = db_path.substr(db_path.find("\\") + 1);
                        db_path = db_path.substr(0, db_path.find("."));
                        std::cout << db_path << std::endl;
                }
                else if (command == keywords[2]) {
                        string db_path = path;
                        db_path += "/";
                        db_path += option;
                        db_path += extension;
                        int result = remove(db_path.c_str());
                        if (result != 0) {
                                std::cerr << "Error deleting database " << db_path;
                        }
                        else {
                                std::cout << "Database " << option << " deleted!" << std::endl;
                        }
                }
                else if (command == keywords[3]) {
                        std::cout << "Bye!";
                        return 0;
                }
                else if (command == keywords[4]) {
                        std::cout << manual_text << endl;
                }
                else {
                        std::cout << "Not a valid option" << endl;
                }
        }
}

int main()
{
        menu();
        return 0;
}
