#ifndef MYBUTTON_H_INC
#define MYBUTTON_H_INC

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>

class MyButton : public Gtk::Button {
private:
  Gtk::Box m_child;
  Gtk::Label m_label;
  Gtk::Image m_image;
public:
  MyButton(const Glib::ustring&, const Glib::ustring&);
};

#endif