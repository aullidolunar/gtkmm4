#include "MyListStore.h"

Glib::RefPtr<MyListStore::MyStore> MyListStore::MyStore::create(
  bool jman,
  const Glib::ustring& title,
  const Glib::ustring& author,
  const Glib::ustring& link
  ) {
  return Glib::make_refptr_for_instance<MyListStore::MyStore>(
    new MyListStore::MyStore(jman, title, author, link)
  );
}

MyListStore::MyStore::MyStore(
  bool jman,
  const Glib::ustring& title,
  const Glib::ustring& author,
  const Glib::ustring& link
  ) : 
  Glib::ObjectBase(typeid(MyListStore::MyStore)),
  prop_jman(*this, "jman", jman),
  prop_title(*this, "title", title),
  prop_author(*this, "author", author),
  prop_link(*this, "link", link) {
}

Glib::PropertyProxy<bool> MyListStore::MyStore::property_jman() {
  return prop_jman.get_proxy();
}

Glib::PropertyProxy<Glib::ustring> MyListStore::MyStore::property_title() {
  return prop_title.get_proxy();
}

Glib::PropertyProxy<Glib::ustring> MyListStore::MyStore::property_author() {
  return prop_author.get_proxy();
}

Glib::PropertyProxy<Glib::ustring> MyListStore::MyStore::property_link() {
  return prop_link.get_proxy();
}
