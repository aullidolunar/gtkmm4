#include <gtkmm/application.h>
#include <glibmm.h>
#include "MyAppWindow.h"

int main(int argc, char** argv)
{
	Glib::setenv("GTK_CSD", PROGRAM_GTK_CSD, TRUE);
	Glib::setenv("GSK_RENDERER", PROGRAM_GSK_RENDERER, TRUE);
	
	auto app = Gtk::Application::create(PROGRAM_APPID);
	
	return app->make_window_and_run<MyAppWindow>(argc, argv);
}
