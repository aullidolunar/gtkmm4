#include <gdkmm/display.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/grid.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/popovermenubar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/signallistitemfactory.h>
#include <gtkmm/switch.h>
#include <gtkmm/entry.h>
#include <gtkmm/separator.h>
#include <gtkmm/frame.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/editablelabel.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "MainWindow.h"

MyAppWindow::MyWindow::MyWindow(Glib::RefPtr<Gtk::Application>& _app) :
  m_app(_app) {
  auto icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  set_default_icon_name(PROGRAM_NAME);
  set_title(PROGRAM_NAME);
  
  auto grid1 = Gtk::make_managed<Gtk::Grid>(); 
// actions
  _app->add_action("close", sigc::bind(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_action_close), "close"));
  add_action("add", sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_action_add_item));
  add_action("edit", sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_action_edit_item));
  add_action("remove", sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_action_remove_item));
  _app->set_accel_for_action("app.close", "<Primary>c");
  _app->set_accel_for_action("win.remove", "<Primary>r");
  _app->set_accel_for_action("win.add", "<Primary>a");
  _app->set_accel_for_action("win.edit", "<Primary>e");
  
// menu
  auto menu_model = Gio::Menu::create();
  
  auto submenu_file = Gio::Menu::create();
  submenu_file->append(_("_Add"), "win.add");
  submenu_file->append(_("_Edit"), "win.edit");
  submenu_file->append(_("_Remove"), "win.remove");
  auto submenu_file_sec1 = Gio::Menu::create();
  submenu_file_sec1->append(_("_Close"), "app.close");
  submenu_file->append_section(submenu_file_sec1);
  auto menu_file =  Gio::MenuItem::create(_("_List"), submenu_file);
  menu_model->append_item(menu_file);
  
  auto popovermenubar = Gtk::make_managed<Gtk::PopoverMenuBar>(menu_model);

// ColumnView
  m_ListStore = Gio::ListStore<MyListStore::MyStore>::create();
  auto model_selection = Gtk::SingleSelection::create(m_ListStore);
  
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_setup_switch));
  factory->signal_bind().connect(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_bind_switch));
  auto col_jman = Gtk::ColumnViewColumn::create(_("Jman"), factory);
  
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_setup_label));
  factory->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_bind_label), MyListStore::ColName::COL_TITLE));
  auto col_title = Gtk::ColumnViewColumn::create(_("Title"), factory);
  col_title->set_resizable();
  
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_setup_label));
  factory->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_bind_label), MyListStore::ColName::COL_AUTHOR));
  auto col_author = Gtk::ColumnViewColumn::create(_("Author"), factory);
  col_author->set_resizable();
  
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_setup_label));
  factory->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &MyAppWindow::MyWindow::on_bind_label), MyListStore::ColName::COL_LINK));
  auto col_link = Gtk::ColumnViewColumn::create(_("Link"), factory);
  col_link->set_expand();
  
  m_column_view.set_model(model_selection);
  m_column_view.append_column(col_jman);
  m_column_view.append_column(col_title);
  m_column_view.append_column(col_author);
  m_column_view.append_column(col_link);
  
// scrolledwindow
  auto scrolledwindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  scrolledwindow->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  scrolledwindow->set_expand();
  scrolledwindow->set_child(m_column_view);
  
  signal_close_request().connect([this]() -> bool {
    auto singlesel = std::dynamic_pointer_cast<Gtk::SingleSelection>(m_column_view.get_model());
    auto liststore = std::dynamic_pointer_cast< Gio::ListStore<MyListStore::MyStore> >(singlesel->get_model());
    int listsize = liststore->get_n_items();
    if (listsize) {
      auto msgbox = Gtk::make_managed<MyAppWindow::MyMessageBox>(*this, _("Exiting the application"), _("There are items on list. Do you wish to continue exit the application?"), MyAppWindow::MessageBoxType::QUESTION, MyAppWindow::MessageBoxButtons::OKCANCEL);
      msgbox->present();
      return true;
    }
    return false;
  }, false);
  
  grid1->attach(*popovermenubar, 0, 0);
  grid1->attach(*scrolledwindow, 0, 1);
  set_child(*grid1);
}

void MyAppWindow::MyWindow::on_action_close(const Glib::ustring& param) {
  if (!param.empty()) {
    std::cout << _("Sender: ") << param << std::endl;
  } else {
    std::cout << _("No arguments") << std::endl;
  }
  close();
}

void MyAppWindow::MyWindow::on_action_remove_item() {
  auto singlesel = std::dynamic_pointer_cast<Gtk::SingleSelection>(m_column_view.get_model());
  guint pos = singlesel->get_selected();
  if (pos != GTK_INVALID_LIST_POSITION) {
    auto liststore = std::dynamic_pointer_cast< Gio::ListStore<MyListStore::MyStore> >(singlesel->get_model());
    liststore->remove(pos);
  }
}

void MyAppWindow::MyWindow::on_action_add_item() {
  auto singlesel = std::dynamic_pointer_cast<Gtk::SingleSelection>(m_column_view.get_model());
  auto dialog = Gtk::make_managed<MyAppWindow::MyDialog>(*this, MyAppWindow::DialogMode::ADD_ITEM, singlesel);
  dialog->present();
}

void MyAppWindow::MyWindow::on_action_edit_item() {
  auto singlesel = std::dynamic_pointer_cast<Gtk::SingleSelection>(m_column_view.get_model());
  if (singlesel && singlesel->get_selected_item()) {
    auto dialog = Gtk::make_managed<MyAppWindow::MyDialog>(*this, MyAppWindow::DialogMode::EDIT_ITEM, singlesel);
    dialog->present();
  } else {
    auto msgbox = Gtk::make_managed<MyAppWindow::MyMessageBox>(*this, _("Information"), _("No items are selected"), MyAppWindow::MessageBoxType::INFO, MyAppWindow::MessageBoxButtons::OK);
    msgbox->present();
  }
}

void MyAppWindow::MyWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item) {
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  list_item->set_child(*label);
  
}

void MyAppWindow::MyWindow::on_bind_label(const Glib::RefPtr<Gtk::ListItem>& list_item, int col_id) {
  auto col = std::dynamic_pointer_cast<MyListStore::MyStore>(list_item->get_item());
  if (col) {
    auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
    if (label) {
      switch (col_id) {
        case MyListStore::ColName::COL_TITLE:
          Glib::Binding::bind_property(col->property_title(), label->property_text(), Glib::Binding::Flags::SYNC_CREATE);
          label->property_editing().signal_changed().connect([label, col](){
            if (!label->get_editing()) {
              col->property_title() = label->get_text();
            }
          });
          break;
        case MyListStore::ColName::COL_AUTHOR:
          Glib::Binding::bind_property(col->property_author(), label->property_text(), Glib::Binding::Flags::SYNC_CREATE);
          label->property_editing().signal_changed().connect([label, col](){
            if (!label->get_editing()) {
              col->property_author() = label->get_text();
            }
          });
          break;
        case MyListStore::ColName::COL_LINK:
          Glib::Binding::bind_property(col->property_link(), label->property_text(), Glib::Binding::Flags::SYNC_CREATE);
          label->property_editing().signal_changed().connect([label, col](){
            if (!label->get_editing()) {
              col->property_link() = label->get_text();
            }
          });
          break;
      }      
    }
  }
}

void MyAppWindow::MyWindow::on_setup_switch(const Glib::RefPtr<Gtk::ListItem>& list_item) {
  list_item->set_child(*Gtk::make_managed<Gtk::Switch>());
}

void MyAppWindow::MyWindow::on_bind_switch(const Glib::RefPtr<Gtk::ListItem>& list_item) {
  auto col = std::dynamic_pointer_cast<MyListStore::MyStore>(list_item->get_item());
  if (col) {
    auto switch_widget = dynamic_cast<Gtk::Switch*>(list_item->get_child());
    if (switch_widget) {
      Glib::Binding::bind_property(col->property_jman(), switch_widget->property_active(), Glib::Binding::Flags::SYNC_CREATE|Glib::Binding::Flags::BIDIRECTIONAL);
    }
  }
}

MyAppWindow::MyDialog::MyDialog(Gtk::Window& parent, int dialog_id, Glib::RefPtr<Gtk::SingleSelection>& selection) {
  std::stringstream ss;
  ss << (dialog_id == MyAppWindow::DialogMode::ADD_ITEM ? _("Add") : _("Edit")) << " " << _("item");
  set_title(ss.str());
  set_transient_for(parent);
  set_destroy_with_parent();
  set_modal();
  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  vbox->set_margin(10);
  vbox->set_spacing(10);
  
  auto frame = Gtk::make_managed<Gtk::Frame>();
  auto frame_label = Gtk::make_managed<MyAppWindow::MyLabel>(_("Item information"), Gtk::Align::START);
  frame_label->set_use_markup();
  frame->set_label_widget(*frame_label);
  auto grid = Gtk::make_managed<Gtk::Grid>();
  grid->set_margin(10);
  grid->set_row_spacing(10);
  grid->set_column_spacing(10);
  auto label_title = Gtk::make_managed<MyAppWindow::MyLabel>(_("Title"), Gtk::Align::END);
  auto entry_title = Gtk::make_managed<Gtk::Entry>();
  auto label_author = Gtk::make_managed<MyAppWindow::MyLabel>(_("Author"), Gtk::Align::END);
  auto entry_author = Gtk::make_managed<Gtk::Entry>();
  auto label_link = Gtk::make_managed<MyAppWindow::MyLabel>(_("Link"), Gtk::Align::END);
  auto entry_link = Gtk::make_managed<Gtk::Entry>();
  auto label_jman = Gtk::make_managed<MyAppWindow::MyLabel>(_("For jMan"), Gtk::Align::END);
  auto switch_jman = Gtk::make_managed<Gtk::Switch>();
  auto expander = Gtk::make_managed<Gtk::Box>();
  expander->set_hexpand();
  auto separator = Gtk::make_managed<Gtk::Separator>();
  auto button_box = Gtk::make_managed<Gtk::Box>();
  button_box->set_spacing(10);
  auto button_spacer = Gtk::make_managed<Gtk::Box>();
  button_spacer->set_hexpand();
  auto button_ok = Gtk::make_managed<MyAppWindow::MyButton>(_("_OK"), "myok");
  button_ok->signal_clicked().connect([this, dialog_id, selection, switch_jman, entry_title, entry_author, entry_link](){
    
    if (dialog_id == MyAppWindow::DialogMode::ADD_ITEM) {
      auto liststore = std::dynamic_pointer_cast< Gio::ListStore<MyListStore::MyStore> >(selection->get_model());
      
      liststore->append(MyListStore::MyStore::create(
        switch_jman->get_active(),
        entry_title->get_text(),
        entry_author->get_text(),
        entry_link->get_text()
      ));
    } else {
      auto row = std::dynamic_pointer_cast<MyListStore::MyStore>(selection->get_selected_item());
      
      row->property_jman() = switch_jman->get_active();
      row->property_title() = entry_title->get_text();
      row->property_author() = entry_author->get_text();
      row->property_link() = entry_link->get_text();
    }
    destroy();
    
  });
  auto button_close = Gtk::make_managed<MyAppWindow::MyButton>(_("_Close"), "myclose");
  button_close->signal_clicked().connect([this](){
    destroy();
  });
  
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect([this](guint keyval, guint, Gdk::ModifierType) -> bool {
    if (keyval == GDK_KEY_Escape) {
      destroy();
      return true;
    }
    return false;
  }, false);
  add_controller(controller);
  
  if (dialog_id == MyAppWindow::DialogMode::EDIT_ITEM) {
    auto row = std::dynamic_pointer_cast<MyListStore::MyStore>(selection->get_selected_item());
    
    switch_jman->set_active(row->property_jman());
    entry_title->set_text(row->property_title());
    entry_author->set_text(row->property_author());
    entry_link->set_text(row->property_link());
  }
  
  grid->attach(*label_title, 0, 0);
  grid->attach(*entry_title, 1, 0, 2);
  grid->attach(*label_author, 0, 1);
  grid->attach(*entry_author, 1, 1, 2);
  grid->attach(*label_link, 0, 2);
  grid->attach(*entry_link, 1, 2, 2);
  grid->attach(*label_jman, 0, 3);
  grid->attach(*switch_jman, 1, 3);
  grid->attach(*expander, 2, 3);
  frame->set_child(*grid);
  vbox->append(*frame);
  vbox->append(*separator);
  button_box->append(*button_spacer);
  button_box->append(*button_ok);
  button_box->append(*button_close);
  vbox->append(*button_box);
  set_child(*vbox);
}

MyAppWindow::MyButton::MyButton(const Glib::ustring& label, const Glib::ustring& icon_name) { 
  m_child.set_spacing(10);
  
  m_image.set_from_icon_name(icon_name);
  m_label.set_text_with_mnemonic(label);
  
  m_child.append(m_image);
  m_child.append(m_label);
  set_child(m_child);
}

MyAppWindow::MyLabel::MyLabel(const Glib::ustring& label, Gtk::Align align) {
  std::stringstream ss;
  ss << "<b>" << label << "</b>";
  set_markup(ss.str());
  set_halign(align);
}

MyAppWindow::MyMessageBox::MyMessageBox(Gtk::Window& parent, const Glib::ustring& primary_text, const Glib::ustring& secundary_text, MyAppWindow::MessageBoxType type, MyAppWindow::MessageBoxButtons buttons) {
  set_title(parent.get_title());
  set_transient_for(parent);
  set_destroy_with_parent();
  set_modal();
  
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
  box->set_margin(10);
   
  auto grid2 = Gtk::make_managed<Gtk::Grid>();
  grid2->set_row_spacing(10);
  grid2->set_column_spacing(10);
  
  auto logo = Gtk::make_managed<Gtk::Image>();
  if (type == MyAppWindow::MessageBoxType::INFO)
    logo->set_from_resource(PROGRAM_RC_PATH "/info.png");
  else {
    logo->set_from_resource(PROGRAM_RC_PATH "/question.png");
  }
  logo->set_pixel_size(32);
  auto label_primary = Gtk::make_managed<MyAppWindow::MyLabel>(primary_text, Gtk::Align::START);
  auto label_secundary = Gtk::make_managed<Gtk::Label>(secundary_text, Gtk::Align::START);
  auto sep = Gtk::make_managed<Gtk::Separator>();
  auto button_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  auto box_exp = Gtk::make_managed<Gtk::Box>();
  box_exp->set_hexpand(true);
  auto button_ok = Gtk::make_managed<MyAppWindow::MyButton>(_("_OK"), "myok");
  button_ok->signal_clicked().connect([this, &parent, type](){
    if (type == MyAppWindow::MessageBoxType::INFO) {
      destroy();
    } else {
      parent.get_application()->quit();
    }
  });
  
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect([this](guint keyval, guint, Gdk::ModifierType) -> bool {
    if (keyval == GDK_KEY_Escape) {
      destroy();
      return true;
    }
    return false;
  }, false);
  add_controller(controller);
  
  grid2->attach(*logo, 0, 0, 1, 2);
  grid2->attach(*label_primary, 1, 0);
  grid2->attach(*label_secundary, 1, 1);
  box->append(*grid2);
  box->append(*sep);
  button_box->append(*box_exp);
  button_box->append(*button_ok);
  if (buttons == MyAppWindow::MessageBoxButtons::OKCANCEL) {
    auto button_no = Gtk::make_managed<MyAppWindow::MyButton>(_("_Cancel"), "myclose");
    button_no->signal_clicked().connect([this](){
      destroy();
    });
    button_box->append(*button_no);
  }
  box->append(*button_box);
  set_child(*box);
}