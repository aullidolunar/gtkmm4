#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/filedialog.h>
#include <gtkmm/builder.h>
#include "ItemEditorDlg.h"
#include "MyListStore.h"

namespace ytdlp4mm {

  enum ListItem {
    GTK_SWITCH = 0,
    GTK_EDITABLE
  };
  
  enum ListCol {
    JMAN = 0,
    TITLE,
    AUTHOR,
    LINK
  };
   
  class MyMainWindow : public Gtk::ApplicationWindow {
  private:
    Glib::RefPtr<Gtk::Application>& m_app;
    Glib::RefPtr< Gio::ListStore<ytdlp4mm::Store> > m_liststore;
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    std::unique_ptr<ytdlp4mm::ItemEditorDlg> m_ItemEditorDlg;
  public:
    MyMainWindow(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&, Glib::RefPtr<Gtk::Application>&);
  protected:
    void on_action_editor(ytdlp4mm::ItemEditorDlgType);
    void on_editor_response(ytdlp4mm::ItemEditorDlgButtons);
    void on_action_close();
    void on_action_delete(bool);
    void on_action_json(bool);
    void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>&, ytdlp4mm::ListItem);
    void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>&, ytdlp4mm::ListCol);
  };

};
#endif