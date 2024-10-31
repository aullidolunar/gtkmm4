#ifndef _ITEMEDITORDLG_H_INCLUDED
#define _ITEMEDITORDLG_H_INCLUDED

#include <gtkmm/applicationwindow.h>
#include <gtkmm/window.h>
#include <gtkmm/columnview.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/switch.h>

namespace ytdlp4mm {

  enum ItemEditorDlgType {
    ADD = 0,
    EDIT
  };
  
  enum ItemEditorDlgButtons {
    OK = 0,
    CLOSE,
  };
  
  class ItemEditorDlg : public Gtk::Window {
    private:
      Glib::RefPtr<Gtk::Builder> m_refBuilder;
      Gtk::Button *m_Button_OK;
      Gtk::Button *m_Button_Close;
      Gtk::Switch *m_Switch_jman;
      Gtk::Entry *m_Entry_Title;
      Gtk::Entry *m_Entry_Author;
      Gtk::Entry *m_Entry_Link;
      Gtk::ColumnView *m_ColumnView;
      int m_type;
    public:
      ItemEditorDlg(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
      void set_title_from_type(ytdlp4mm::ItemEditorDlgType);
      void set_initials();
      int get_type_dlg();
      bool get_jman();
      const Glib::ustring get_title();
      const Glib::ustring get_author();
      const Glib::ustring get_link();
      Gtk::ColumnView* get_view();
      void buttons_clicked_connect(const sigc::slot<void(ytdlp4mm::ItemEditorDlgButtons)>&);
  };
  
};

#endif