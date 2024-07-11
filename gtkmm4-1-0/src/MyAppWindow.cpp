#include "MyAppWindow.h"
#include <gtkmm/button.h>
#include <iostream>

MyAppWindow::MyAppWindow()
{
	set_title(PROGRAM_TITLE);
}

MyAppWindow::~MyAppWindow()
{
	std::cout << "Done here";
}