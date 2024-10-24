#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/singleselection.h>
#include <gtkmm/columnview.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <glibmm/i18n.h>
#include "MyListStore.h"

namespace MyAppWindow {
  
  enum DialogMode {
    ADD_ITEM = 0,
    EDIT_ITEM
  };
  
  enum MessageBoxType {
    INFO = 0,
    QUESTION
  };
  
  enum MessageBoxButtons {
    OK = 0,
    OKCANCEL
  };
  
  class MyLabel : public Gtk::Label {
    public:
      MyLabel(const Glib::ustring&, Gtk::Align);
  };
  
  class MyButton : public Gtk::Button {
    private:
      Gtk::Box m_child;
      Gtk::Label m_label;
      Gtk::Image m_image;
    public:
      MyButton(const Glib::ustring&, const Glib::ustring&);
    };

  class MyDialog : public Gtk::Window {
    public:
      MyDialog(Gtk::Window&, int, Glib::RefPtr<Gtk::SingleSelection>&);
  };
  
  class MyMessageBox : public Gtk::Window {
    public:
      MyMessageBox(Gtk::Window&, const Glib::ustring&, const Glib::ustring&, MyAppWindow::MessageBoxType, MyAppWindow::MessageBoxButtons);
  };

  class MyWindow : public Gtk::ApplicationWindow {
  private:
    Glib::RefPtr<Gtk::Application>& m_app;
    Glib::RefPtr<Gio::ListStore<MyListStore::MyStore>> m_ListStore;
    Gtk::ColumnView m_column_view;
  public:
    MyWindow(Glib::RefPtr<Gtk::Application>&);
  protected:
    void on_action_close(const Glib::ustring&);
    void on_action_add_item();
    void on_action_edit_item();
    void on_action_remove_item();
    void on_setup_label(const Glib::RefPtr<Gtk::ListItem>&);
    void on_bind_label(const Glib::RefPtr<Gtk::ListItem>&, int);
    void on_bind_switch(const Glib::RefPtr<Gtk::ListItem>&);
    void on_setup_switch(const Glib::RefPtr<Gtk::ListItem>&);
    
  };

};
#endif