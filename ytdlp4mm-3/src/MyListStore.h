#ifndef MYLISTSTORE_H_INC
#define MYLISTSTORE_H_INC

#include <glibmm.h>
#include <giomm.h>
#include <gtkmm/listitem.h>
#include <glibmm/i18n.h>
#include <iostream>

namespace ytdlp4mm {
  enum ColName {
    COL_JMAN = 0,
    COL_TITLE,
    COL_AUTHOR,
    COL_LINK
  };

  class Store : public Glib::Object {
  private:
    Glib::Property<bool> prop_jman;
    Glib::Property<Glib::ustring> prop_title;
    Glib::Property<Glib::ustring> prop_author;
    Glib::Property<Glib::ustring> prop_link;
  public:
    static Glib::RefPtr<ytdlp4mm::Store> create(bool, const Glib::ustring&, const Glib::ustring&, const Glib::ustring&);
    Glib::PropertyProxy<bool> property_jman();
    Glib::PropertyProxy<Glib::ustring> property_title();
    Glib::PropertyProxy<Glib::ustring> property_author();
    Glib::PropertyProxy<Glib::ustring> property_link();
    bool update_jman(const std::string&, bool);
    bool update_title(const std::string&, const Glib::ustring&);
    bool update_author(const std::string&, const Glib::ustring&);
    bool update_link(const std::string&, const Glib::ustring&);
  protected:
    Store(bool, const Glib::ustring&, const Glib::ustring&, const Glib::ustring&);
  };
};
#endif