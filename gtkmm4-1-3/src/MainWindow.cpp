#include "MainWindow.h"
#include <gdkmm/display.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/window.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/builder.h>
#include <memory>

void on_app_activate(Glib::RefPtr<Gtk::Application>& app) {

  auto icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  auto refBuilder = Gtk::Builder::create_from_resource(GLADE_FILE);
  
  auto window1 = refBuilder->get_widget<Gtk::Window>("window1");
  
  window1->set_application(app);
  window1->set_title(PROGRAM_TITLE);
  window1->set_default_icon_name(PROGRAM_NAME);
  
  app->signal_shutdown().connect([window1](){
	  delete window1;
  });
  
  window1->present();
}
