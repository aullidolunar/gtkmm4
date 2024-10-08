#include "MainWindow.h"
#include <gdkmm/display.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/alertdialog.h>
#include <gtkmm/aboutdialog.h>
#include <vector>

MyAppWindow::MyAppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder, Glib::RefPtr<Gtk::Application>& _app) :
  Gtk::ApplicationWindow(cobject), app(_app) {
  auto icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  set_application(_app);
  set_title(PROGRAM_NAME);
  set_default_icon_name(PROGRAM_NAME);
  
  auto button1 = refBuilder->get_widget<Gtk::Button>("button1");
  auto button2 = refBuilder->get_widget<Gtk::Button>("button2");
  m_entry = refBuilder->get_widget<Gtk::Entry>("entry1");
  auto check1 = refBuilder->get_widget<Gtk::CheckButton>("check1");
    
  button1->signal_clicked().connect([this, check1](){
    if (check1->get_active()) {
      showAbout();
    } else {
     showMessage();
   }
  });
  
  button2->signal_clicked().connect([this](){
    destroy();
  });
  
}

MyAppWindow::~MyAppWindow() {
  //
}

void MyAppWindow::showAbout() {
  auto ad = Gtk::make_managed<Gtk::AboutDialog>();
  std::vector<Glib::ustring> authors = {"aullidolunar"};
  ad->set_program_name(PROGRAM_NAME);
  ad->set_version(PROGRAM_VERSION);
  ad->set_comments(_(PROGRAM_DESC));
  ad->set_logo_icon_name("platform");
  ad->set_authors(authors);
  ad->set_transient_for(*this);
  ad->present();
}

void MyAppWindow::showMessage() {
   auto ad = Gtk::AlertDialog::create();
   auto message = m_entry->get_text();
   ad->set_message(_("This is your text"));
   ad->set_detail(message);
   ad->show(*this);
}