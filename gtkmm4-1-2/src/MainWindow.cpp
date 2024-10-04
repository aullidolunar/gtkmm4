#include "MainWindow.h"
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gdkmm/display.h>
#include <gtkmm/icontheme.h>

MainWindow::MainWindow() {

  Glib::RefPtr<Gtk::IconTheme> icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  set_title(PROGRAM_TITLE);
  set_default_icon_name(PROGRAM_NAME);
  
  auto boxer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  boxer->set_margin(10);
  
  auto button1 = Gtk::make_managed<Gtk::Button>();
  auto child = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  auto button_label = Gtk::make_managed<Gtk::Label>(_("_Quit"), true);
  auto button_image = Gtk::make_managed<Gtk::Image>();
  button_image->set_from_icon_name("myclose");
  
  auto label = Gtk::make_managed<Gtk::Label>(_(PROGRAM_DESC));
  
  child->append(*button_image);
  child->append(*button_label);
  button1->set_child(*child);
  
  button1->signal_clicked().connect([this]{
    close();
  });
  
  boxer->append(*label);
  boxer->append(*button1);
  set_child(*boxer);
}

MainWindow::~MainWindow() {
}