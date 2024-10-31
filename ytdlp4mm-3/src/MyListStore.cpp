#include "MyListStore.h"

Glib::RefPtr<ytdlp4mm::Store> ytdlp4mm::Store::create(
  bool jman,
  const Glib::ustring& title,
  const Glib::ustring& author,
  const Glib::ustring& link
  ) {
  return Glib::make_refptr_for_instance<ytdlp4mm::Store>(
    new ytdlp4mm::Store(jman, title, author, link)
  );
}

ytdlp4mm::Store::Store(
  bool jman,
  const Glib::ustring& title,
  const Glib::ustring& author,
  const Glib::ustring& link
  ) : 
  Glib::ObjectBase(typeid(ytdlp4mm::Store)),
  prop_jman(*this, "jman", jman),
  prop_title(*this, "title", title),
  prop_author(*this, "author", author),
  prop_link(*this, "link", link) {
}

Glib::PropertyProxy<bool> ytdlp4mm::Store::property_jman() {
  return prop_jman.get_proxy();
}

Glib::PropertyProxy<Glib::ustring> ytdlp4mm::Store::property_title() {
  return prop_title.get_proxy();
}

Glib::PropertyProxy<Glib::ustring> ytdlp4mm::Store::property_author() {
  return prop_author.get_proxy();
}

Glib::PropertyProxy<Glib::ustring> ytdlp4mm::Store::property_link() {
  return prop_link.get_proxy();
}

bool ytdlp4mm::Store::update_jman(const std::string& sender, bool new_value) {
  std::cout << sender << ": jman ";
  if (property_jman().get_value() != new_value) {
    property_jman() = new_value;
    std::cout << _("was updated.") << std::endl;
    return true;
  }
  std::cout << _("was skipped.") << std::endl;
  return false;
}

bool ytdlp4mm::Store::update_title(const std::string& sender, const Glib::ustring& new_value) {
  std::cout << sender << ": " << _("title") << " ";
  if (property_title().get_value() != new_value) {
    property_title() = new_value;
    std::cout << _("was updated.") << std::endl;
    return true;
  }
  std::cout << _("was skipped.") << std::endl;
  return false;
}

bool ytdlp4mm::Store::update_author(const std::string& sender, const Glib::ustring& new_value) {
  std::cout << sender << ": " << _("author") << " ";
  if (property_author().get_value() != new_value) {
    property_author() = new_value;
    std::cout << _("was updated.") << std::endl;
    return true;
  }
  std::cout << _("was skipped.") << std::endl;
  return false;
}

bool ytdlp4mm::Store::update_link(const std::string& sender, const Glib::ustring& new_value) {
  std::cout << sender << ": " << _("link") << " ";
  if (property_link().get_value() != new_value) {
    property_link() = new_value;
    std::cout << _("was updated.") << std::endl;
    return true;
  }
  std::cout << _("was skipped.") << std::endl;
  return false;
}