#include "MainWindow.h"
#include "MyButton.h"
#include <gdkmm/display.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/grid.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/alertdialog.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/label.h>
#include <vector>

MyAppWindow::MyAppWindow(Glib::RefPtr<Gtk::Application>& _app) :
  m_app(_app) {
  auto icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  set_title(PROGRAM_NAME);
  set_default_icon_name(PROGRAM_NAME);
  
  auto grid1 = Gtk::make_managed<Gtk::Grid>();
  grid1->set_margin(10);
  grid1->set_row_spacing(10);
  grid1->set_column_spacing(10);
  
  auto platform = Gtk::make_managed<Gtk::Image>();
  platform->set_pixel_size(64);
  platform->set_tooltip_text(_("Your platform icon"));
  platform->set_from_resource(PROGRAM_RC_PATH "/platform.png");
  
  auto m_label1 = Gtk::make_managed<Gtk::Label>(_("Write something to show:"));
  
  m_entry1.set_hexpand(true);
  
  auto m_button1 = Gtk::make_managed<MyButton>(_("_OK"), "myenter");
  m_button1->set_tooltip_text(_("Show me some dialog with information"));
  
  auto m_button2 = Gtk::make_managed<MyButton>(_("_Close"), "myclose");
  m_button2->set_tooltip_text(_("Exit the application"));
  
  m_check1.set_label(_("_Show GtkAboutDialog"));
  m_check1.set_use_underline(true);
  m_entry1.set_hexpand(true);
  
  m_button1->signal_clicked().connect([this](){
    if (m_check1.get_active()) {
      showAbout();
    } else {
      showMessage();
    }
  });
  
  m_button2->signal_clicked().connect([this](){
    close();
  });
  
  m_check1.signal_toggled().connect([this](){
    m_entry1.set_sensitive(!m_check1.get_active());
  });
  
  grid1->attach(*platform, 0, 0, 1, 2);
  grid1->attach(*m_label1, 1, 0);
  grid1->attach(m_entry1, 2, 0);
  grid1->attach(*m_button1, 3, 0);
  grid1->attach(*m_button2, 4, 0);
  grid1->attach(m_check1, 1, 1);
  set_child(*grid1);
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
   auto message = m_entry1.get_text();
   ad->set_message(_("This is your text"));
   ad->set_detail(message);
   ad->show(*this);
}
