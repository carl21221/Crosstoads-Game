#include "Menu.h"

Menu::Menu()
{
}

void Menu::SetUp()
{
	menuItems.push_back(MenuItem(200, 100, "Play Game"));
	menuItems.push_back(MenuItem(200, 150, "Options"));
	menuItems.push_back(MenuItem(200, 200, "Exit Game"));
	selectedMenuItem = 0;
	isActive = true;
}

void Menu::AddMenuItem(MenuItem m)
{
	menuItems.push_back(m);
}
void Menu::RemoveMenuItem(int index)
{
	menuItems.erase(menuItems.begin() + index);
}
void Menu::IncrementSelectedMenuItem() 
{ 
	selectedMenuItem++;
	if (selectedMenuItem >= menuItems.size()) selectedMenuItem = 0;
}
void Menu::DecrementSelectedMenuItem() 
{
	selectedMenuItem--; 
	if (selectedMenuItem < 0) selectedMenuItem = menuItems.size() - 1;
}
void Menu::ChangeSelectedMenuItem(int newIndex)
{
	if (newIndex >= 0 && newIndex < menuItems.size())
	{
		selectedMenuItem = newIndex;
	}
}
MenuItem* Menu::GetMenuItemByIndex(int index)
{
	if (index >= 0 && index < menuItems.size()) return &menuItems[index];
	return nullptr;
}
bool Menu::IsActive() { return isActive; }
int Menu::GetSelectedMenuItemIndex() { return selectedMenuItem; }

void Menu::SetActive(bool value)
{
	isActive = value;
}