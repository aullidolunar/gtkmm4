#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/entry.h>
#include <gtkmm/checkbutton.h>
#include <glibmm/i18n.h>

class MyAppWindow : public Gtk::ApplicationWindow {
private:
  Glib::RefPtr<Gtk::Application>& m_app;
  Gtk::Entry m_entry1;
  Gtk::CheckButton m_check1;
public:
  MyAppWindow(Glib::RefPtr<Gtk::Application>&);
protected:
  void showAbout();
  void showMessage();
};

#endif