#pragma once
#include "MenuItem.h"
#include <vector>

class Menu
{
public:
	Menu();
	//Getters
	bool IsActive();
	MenuItem* GetMenuItemByIndex(int index);
	int GetSelectedMenuItemIndex();

	//Mutators
	void SetUp();
	void SetActive(bool value);
	void AddMenuItem(MenuItem m);
	void RemoveMenuItem(int index);

	void IncrementSelectedMenuItem();
	void DecrementSelectedMenuItem();
	void ChangeSelectedMenuItem(int newIndex);


private:
	vector<MenuItem> menuItems;
	int selectedMenuItem = 0;
	bool isActive = false;
};

