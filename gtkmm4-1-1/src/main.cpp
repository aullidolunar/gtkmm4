#include "MainWindow.h"
#include <gtkmm/application.h>
#include <glibmm.h>

int main(int argc, char* argv[]) {
  Glib::setenv("GTK_CSD", PROGRAM_GTK_CSD, TRUE);
  auto app = Gtk::Application::create(PROGRAM_ID);
  return app->make_window_and_run<MainWindow>(argc, argv);
}