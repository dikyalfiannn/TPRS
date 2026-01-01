#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

struct MenuStack {
    string menuList[20];
    int top;
};

void initStack(MenuStack &s) {
    s.top = -1;
}

bool isEmpty(MenuStack s) {
    return s.top == -1;
}

bool isFull(MenuStack s) {
    return s.top == 19;
}

void push(MenuStack &s, string namaMenu) {
    if(!isFull(s)) {
        s.top++;
        s.menuList[s.top] = namaMenu;
    }
}

string pop(MenuStack &s) {
    if(!isEmpty(s)) {
        string menu = s.menuList[s.top];
        s.top--;
        return menu;
    }
    return "";
}

string peek(MenuStack s) {
    if(!isEmpty(s)) {
        return s.menuList[s.top];
    }
    return "";
}

#endif
