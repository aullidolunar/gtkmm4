#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/singleselection.h>
#include <glibmm/i18n.h>
#include "ItemEditorDlg.h"
#include "MyListStore.h"

ytdlp4mm::ItemEditorDlg::ItemEditorDlg(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder) :
  Gtk::Window(cobject),
  m_refBuilder(refBuilder) {
  
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect([this](guint keyval, guint, Gdk::ModifierType) -> bool {
    if (keyval == GDK_KEY_Escape) {
      close();
      return true;
    }
    return false;
  }, false);
  add_controller(controller);
  
  m_Button_OK = m_refBuilder->get_widget<Gtk::Button>("editor_ok");
  m_Button_Close = refBuilder->get_widget<Gtk::Button>("editor_close");
  m_Switch_jman = m_refBuilder->get_widget<Gtk::Switch>("switch_jman");
  m_Entry_Title = m_refBuilder->get_widget<Gtk::Entry>("entry_title");
  m_Entry_Author = m_refBuilder->get_widget<Gtk::Entry>("entry_author");
  m_Entry_Link = m_refBuilder->get_widget<Gtk::Entry>("entry_link");
  m_ColumnView = m_refBuilder->get_widget<Gtk::ColumnView>("columnview");
}

void ytdlp4mm::ItemEditorDlg::set_title_from_type(ytdlp4mm::ItemEditorDlgType type) {
  std::stringstream ss;    
  ss << (type == ytdlp4mm::ItemEditorDlgType::ADD ? _("Add") : _("Edit")) << " " << _("item");
  set_title(ss.str());
  m_type = type;
}

void ytdlp4mm::ItemEditorDlg::buttons_clicked_connect(const sigc::slot<void(ytdlp4mm::ItemEditorDlgButtons)>& slot) {
  
  m_Button_OK->signal_clicked().connect(sigc::bind(slot, ytdlp4mm::ItemEditorDlgButtons::OK));
  m_Button_Close->signal_clicked().connect(sigc::bind(slot, ytdlp4mm::ItemEditorDlgButtons::CLOSE));
}

void ytdlp4mm::ItemEditorDlg::set_initials() {
  if (m_type == ytdlp4mm::ItemEditorDlgType::EDIT) {
    auto selection = std::dynamic_pointer_cast<Gtk::SingleSelection>(m_ColumnView->get_model());
    auto row = std::dynamic_pointer_cast<ytdlp4mm::Store>(selection->get_selected_item());
    m_Entry_Title->set_text(row->property_title());
    m_Entry_Author->set_text(row->property_author());
    m_Entry_Link->set_text(row->property_link());
    m_Switch_jman->set_active(row->property_jman());
  } else {
    m_Entry_Title->set_text("");
    m_Entry_Author->set_text("");
    m_Entry_Link->set_text("");
    m_Switch_jman->set_active(false);
  }
}

bool ytdlp4mm::ItemEditorDlg::get_jman() { return m_Switch_jman->get_active(); }
const Glib::ustring ytdlp4mm::ItemEditorDlg::get_title() { return m_Entry_Title->get_text(); }
const Glib::ustring ytdlp4mm::ItemEditorDlg::get_author() { return m_Entry_Author->get_text(); }
const Glib::ustring ytdlp4mm::ItemEditorDlg::get_link() { return m_Entry_Link->get_text(); }
int ytdlp4mm::ItemEditorDlg::get_type_dlg() { return m_type; }
Gtk::ColumnView* ytdlp4mm::ItemEditorDlg::get_view() { return m_ColumnView; }
