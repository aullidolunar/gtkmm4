#include "MyButton.h"

MyButton::MyButton(const Glib::ustring& label, const Glib::ustring& icon_name) { 
  m_child.set_spacing(10);
  
  m_image.set_from_icon_name(icon_name);
  //m_image.set_pixel_size(64);
  m_label.set_text_with_mnemonic(label);
  
  m_child.append(m_image);
  m_child.append(m_label);
  set_child(m_child);
}