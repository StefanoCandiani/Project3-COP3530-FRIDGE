.0//
// Created by Administrator on 6/14/2024.
//
#include <string>

#ifndef AVLPROJECT_VALIDATIONTEST_H
#define AVLPROJECT_VALIDATIONTEST_H

using namespace std;
class MyParser{

public:
    static bool isValidEntry(string name, string id_str){ //Valid integer, Valid ID, Valid Name
        return (isNumber(id_str) && IsValidID(stoi(id_str)) && IsOnlyAlphabetical(name));
    }
    static void CleanName(string& name){
        name.erase(0, 1);
        name.erase(name.size() - 1, 1);
    }
    static bool isNumber(string id_str) {
        for (char c : id_str) {
            if (!isdigit(c)) {
                return false;
            }
        }

        if(id_str == "") return false;
        return true;
    }
    static bool IsValidID(int ID) {
        string id_str = to_string(ID);
        return id_str.size() == 8;
    }
    static bool IsOnlyAlphabetical(string& name) {
        for (auto i : name) {
            if (!isalpha(i)) {
                if (i != '"' && i != ' ') {
                    return false;
                }
            }
        }
        return true;
    }

};
#endif //AVLPROJECT_VALIDATIONTEST_H
