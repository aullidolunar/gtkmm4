#include "MainWindow.h"
#include <gdkmm/display.h>
#include <gtkmm/window.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/alertdialog.h>
#include <gtkmm/aboutdialog.h>
#include <vector>

void showAbout(Gtk::Window *parent) {
  auto ad = Gtk::manage(new Gtk::AboutDialog());
  std::vector<Glib::ustring> authors = {"aullidolunar"};
  ad->set_program_name(PROGRAM_NAME);
  ad->set_version(PROGRAM_VERSION);
  ad->set_comments(_(PROGRAM_DESC));
  ad->set_logo_icon_name("platform");
  ad->set_authors(authors);
  ad->set_transient_for(*parent);
  ad->present();
}

void on_app_activate(Glib::RefPtr<Gtk::Application> app) {

  auto icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  auto refBuilder = Gtk::Builder::create_from_resource(GLADE_FILE);
  auto window1 = refBuilder->get_widget<Gtk::Window>("window1");
  auto button1 = refBuilder->get_widget<Gtk::Button>("button1");
  auto button2 = refBuilder->get_widget<Gtk::Button>("button2");
  auto entry1 = refBuilder->get_widget<Gtk::Entry>("entry1");
  auto check1 = refBuilder->get_widget<Gtk::CheckButton>("check1");
  
  window1->set_application(app);
  window1->set_title(PROGRAM_NAME);
  window1->set_default_icon_name(PROGRAM_NAME);
  
  button1->signal_clicked().connect([window1, check1, entry1](){
    if (check1->get_active()) {
      showAbout(window1);
    } else {
      auto ad = Gtk::AlertDialog::create();
      auto message = entry1->get_text();
      ad->set_message(_("This is your text"));
      ad->set_detail(message);
      ad->show(*window1);
   }
  });
  
  button2->signal_clicked().connect([window1](){
    window1->destroy();
  });
  
  app->signal_shutdown().connect([=](){
    std::cout << _(PROGRAM_DESC) << " " << _("has close") << std::endl;
    delete check1;
    delete entry1;
    delete button2;
    delete button1;
    delete window1;
  });
  window1->present();
}
