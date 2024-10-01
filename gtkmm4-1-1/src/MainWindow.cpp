#include "MainWindow.h"
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>

MainWindow::MainWindow() {
  
  set_title(PROGRAM_TITLE);
  
  auto boxer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  boxer->set_margin(10);
  
  auto button1 = Gtk::make_managed<Gtk::Button>();
  auto child = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  auto button_label = Gtk::make_managed<Gtk::Label>("_Quit", true);
  auto button_image = Gtk::make_managed<Gtk::Image>();
  button_image->set_from_icon_name("application-exit");
  
  child->append(*button_image);
  child->append(*button_label);
  button1->set_child(*child);
  
  button1->signal_clicked().connect([this]{
    close();
  });
  
  boxer->append(*button1);
  set_child(*boxer);
}

MainWindow::~MainWindow() {
}