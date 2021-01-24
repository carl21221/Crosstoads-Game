#pragma once

#include <string>

using namespace std;

class MenuItem
{
public:
	MenuItem::MenuItem(int newX, int newY, string text);
	int GetX();
	int GetY();
	string GetText();

private:
	int x = 0;
	int y = 0;
	string text = "default_menu_item";
};