#ifndef MYLISTSTORE_H_INC
#define MYLISTSTORE_H_INC

#include <glibmm.h>
#include <giomm.h>
#include <gtkmm/listitem.h>

namespace MyListStore {
  enum ColName {
    COL_JMAN = 0,
    COL_TITLE,
    COL_AUTHOR,
    COL_LINK
  };

  class MyStore : public Glib::Object {
  private:
    Glib::Property<bool> prop_jman;
    Glib::Property<Glib::ustring> prop_title;
    Glib::Property<Glib::ustring> prop_author;
    Glib::Property<Glib::ustring> prop_link;
  public:
    static Glib::RefPtr<MyListStore::MyStore> create(bool, const Glib::ustring&, const Glib::ustring&, const Glib::ustring&);
    Glib::PropertyProxy<bool> property_jman();
    Glib::PropertyProxy<Glib::ustring> property_title();
    Glib::PropertyProxy<Glib::ustring> property_author();
    Glib::PropertyProxy<Glib::ustring> property_link();
  protected:
    MyStore(bool, const Glib::ustring&, const Glib::ustring&, const Glib::ustring&);
  };
};
#endif