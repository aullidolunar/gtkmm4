#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <glibmm/i18n.h>
#include <iostream>

class MyAppWindow : public Gtk::ApplicationWindow {
private:
  Glib::RefPtr<Gtk::Application> app;
  Gtk::Entry *m_entry;
public:
  MyAppWindow(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&, Glib::RefPtr<Gtk::Application>&);
  virtual ~MyAppWindow();
protected:
  void showAbout();
  void showMessage();
};

#endif