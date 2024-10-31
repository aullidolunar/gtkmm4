#include <gdkmm/display.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/singleselection.h>
#include <gtkmm/signallistitemfactory.h>
#include <gtkmm/listitem.h>
#include <gtkmm/switch.h>
#include <gtkmm/editablelabel.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <json/json.h>
#include "MainWindow.h"

ytdlp4mm::MyMainWindow::MyMainWindow(
  BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder,
  Glib::RefPtr<Gtk::Application>& app) :
  Gtk::ApplicationWindow(cobject),
  m_app(app),
  m_liststore(Gio::ListStore<ytdlp4mm::Store>::create()),
  m_refBuilder(refBuilder) {
  
  auto icon_theme = Gtk::IconTheme::get_for_display(Gdk::Display::get_default());
  icon_theme->add_resource_path(PROGRAM_RC_PATH);
  
  app->add_action("exit", sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_close));
  app->set_accel_for_action("app.exit", "<Primary>x");
  
  add_action("add", sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_editor), ytdlp4mm::ItemEditorDlgType::ADD));
  app->set_accel_for_action("win.add", "<Primary>a");
  
  add_action("edit", sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_editor), ytdlp4mm::ItemEditorDlgType::EDIT));
  app->set_accel_for_action("win.edit", "<Primary>e");
  
  add_action("remove", sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_delete), false));
  app->set_accel_for_action("win.remove", "<Primary>r");
  
  add_action("clear", sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_delete), true));
  app->set_accel_for_action("win.clear", "<Primary>c");
  
  add_action("save", sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_json), false));
  app->set_accel_for_action("win.save", "<Primary>s");
  
  add_action("open", sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_action_json), true));
  app->set_accel_for_action("win.open", "<Primary>o");
  
  set_default_icon_name(PROGRAM_NAME);
  set_title(PROGRAM_NAME);
  
  auto singleselection = refBuilder->get_object<Gtk::SingleSelection>("singselmodel");
  singleselection->set_model(m_liststore);
  
  auto factory_switch = refBuilder->get_object<Gtk::SignalListItemFactory>("col_jman_factory");
  factory_switch->signal_setup().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_setup_listitem), ytdlp4mm::ListItem::GTK_SWITCH));
  factory_switch->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_bind_listitem), ytdlp4mm::ListCol::JMAN));
  
  auto factory_title = refBuilder->get_object<Gtk::SignalListItemFactory>("col_title_factory");
  factory_title->signal_setup().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_setup_listitem), ytdlp4mm::ListItem::GTK_EDITABLE));
  factory_title->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_bind_listitem), ytdlp4mm::ListCol::TITLE));
  
  auto factory_author = refBuilder->get_object<Gtk::SignalListItemFactory>("col_author_factory");
  factory_author->signal_setup().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_setup_listitem), ytdlp4mm::ListItem::GTK_EDITABLE));
  factory_author->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_bind_listitem), ytdlp4mm::ListCol::AUTHOR));
  
  auto factory_link = refBuilder->get_object<Gtk::SignalListItemFactory>("col_link_factory");
  factory_link->signal_setup().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_setup_listitem), ytdlp4mm::ListItem::GTK_EDITABLE));
  factory_link->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_bind_listitem), ytdlp4mm::ListCol::LINK));
  
}

void ytdlp4mm::MyMainWindow::on_editor_response(ytdlp4mm::ItemEditorDlgButtons resp) {
  if (resp == ytdlp4mm::ItemEditorDlgButtons::OK) {
    if (m_ItemEditorDlg->get_type_dlg() == ytdlp4mm::ItemEditorDlgType::ADD) {
      m_liststore->append(ytdlp4mm::Store::create(
        m_ItemEditorDlg->get_jman(),
        m_ItemEditorDlg->get_title(),
        m_ItemEditorDlg->get_author(),
        m_ItemEditorDlg->get_link()
      ));
    } else {
      auto selection = std::dynamic_pointer_cast<Gtk::SingleSelection>(m_ItemEditorDlg->get_view()->get_model());
      auto row = std::dynamic_pointer_cast<ytdlp4mm::Store>(selection->get_selected_item());
      row->update_jman("m_ItemEditorDlg", m_ItemEditorDlg->get_jman());
      row->update_title("m_ItemEditorDlg", m_ItemEditorDlg->get_title());
      row->update_author("m_ItemEditorDlg", m_ItemEditorDlg->get_author());
      row->update_link("m_ItemEditorDlg", m_ItemEditorDlg->get_link());
    }
  }
  m_ItemEditorDlg->close();
}

void ytdlp4mm::MyMainWindow::on_action_editor(ytdlp4mm::ItemEditorDlgType type) {
  if (!m_ItemEditorDlg) {
    m_ItemEditorDlg.reset(Gtk::Builder::get_widget_derived<ytdlp4mm::ItemEditorDlg>(m_refBuilder, "ItemEditorDlg"));
    m_ItemEditorDlg->signal_hide().connect([]() {
      std::cout << "ItemEditorDlg hide" << std::endl;
    });
    m_ItemEditorDlg->buttons_clicked_connect(sigc::mem_fun(*this, &ytdlp4mm::MyMainWindow::on_editor_response));
  }
  m_ItemEditorDlg->set_title_from_type(type);
  m_ItemEditorDlg->set_initials();
  m_ItemEditorDlg->present();
}

void ytdlp4mm::MyMainWindow::on_action_close() {
  destroy();
}

void ytdlp4mm::MyMainWindow::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& item, ytdlp4mm::ListItem type) {
  if (type == ytdlp4mm::ListItem::GTK_SWITCH) {
    item->set_child(*Gtk::make_managed<Gtk::Switch>());
  } else {
    item->set_child(*Gtk::make_managed<Gtk::EditableLabel>());
  }
}

void ytdlp4mm::MyMainWindow::on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& item, ytdlp4mm::ListCol col_id) {
  auto col = std::dynamic_pointer_cast<ytdlp4mm::Store>(item->get_item());
  switch (col_id) {
    case ytdlp4mm::ListCol::JMAN: {
      auto switch_widget = dynamic_cast<Gtk::Switch*>(item->get_child());
      Glib::Binding::bind_property(col->property_jman(), switch_widget->property_active(), Glib::Binding::Flags::SYNC_CREATE|Glib::Binding::Flags::BIDIRECTIONAL);
      col->update_jman("ColumnView::Switch", switch_widget->get_active());
      break;
    }
    case ytdlp4mm::ListCol::TITLE: {
      auto label_widget = dynamic_cast<Gtk::EditableLabel*>(item->get_child());
      Glib::Binding::bind_property(col->property_title(), label_widget->property_text(), Glib::Binding::Flags::SYNC_CREATE);
      label_widget->property_editing().signal_changed().connect([label_widget, col](){
        if (!label_widget->get_editing()) {
          col->update_title("ColumnView::title", label_widget->get_text());
        }
      });
      break;
    }
    case ytdlp4mm::ListCol::AUTHOR: {
      auto label_widget = dynamic_cast<Gtk::EditableLabel*>(item->get_child());
      Glib::Binding::bind_property(col->property_author(), label_widget->property_text(), Glib::Binding::Flags::SYNC_CREATE);
      label_widget->property_editing().signal_changed().connect([label_widget, col](){
        if (!label_widget->get_editing()) {
          col->update_author("ColumnView::author", label_widget->get_text());
        }
      });
      break;
    }
    case ytdlp4mm::ListCol::LINK: {
      auto label_widget = dynamic_cast<Gtk::EditableLabel*>(item->get_child());
      Glib::Binding::bind_property(col->property_link(), label_widget->property_text(), Glib::Binding::Flags::SYNC_CREATE);
      label_widget->property_editing().signal_changed().connect([label_widget, col](){
        if (!label_widget->get_editing()) {
          col->update_link("ColumnView::link", label_widget->get_text());
        }
      });
      break;
    }
  }
}

void ytdlp4mm::MyMainWindow::on_action_delete(bool deleteall) {
  guint items_len = m_liststore->get_n_items();
  if (items_len) {
    if (deleteall) {
      m_liststore->remove_all();
    } else {
      Gtk::ColumnView *cv = m_ItemEditorDlg->get_view();
      auto selection = std::dynamic_pointer_cast<Gtk::SingleSelection>(cv->get_model());
      guint selected_index = selection->get_selected();
      if (selected_index != GTK_INVALID_LIST_POSITION) {
         m_liststore->remove(selected_index);  
      }
    }
  }
}

void ytdlp4mm::MyMainWindow::on_action_json(bool reader) {
  auto filechooser = Gtk::FileDialog::create();
  auto filters = Gio::ListStore<Gtk::FileFilter>::create();
  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name(_("JSON files"));
  filter_any->add_pattern("*.json");
  filters->append(filter_any);
  filechooser->set_filters(filters);
  if (reader) {
    filechooser->open(*this, [filechooser,this](const Glib::RefPtr<Gio::AsyncResult>& result){
      try {
        auto gfile = filechooser->open_finish(result);
        std::ifstream file_in(gfile->get_path());
        Json::Value json_obj;
        file_in >> json_obj;
        guint items_len = json_obj.size();
        for (guint pos = 0; pos < items_len; pos++) {
          std::stringstream ss;
          ss << "Song" << pos;
          std::string header = ss.str();
          m_liststore->append(ytdlp4mm::Store::create(
            json_obj[header]["jMan"].asBool(),
            json_obj[header]["Title"].asString(),
            json_obj[header]["Artist"].asString(),
            json_obj[header]["Link"].asString()
          ));
        }
      } catch(...) {
        //
      }
    });
  } else {
    filechooser->save(*this, [filechooser,this](const Glib::RefPtr<Gio::AsyncResult>& result){
      try {
        auto file = filechooser->save_finish(result);
        guint items_len = m_liststore->get_n_items();
        if (items_len) {
          std::ofstream file_out(file->get_path());
          Json::StreamWriterBuilder builder;
          builder.settings_["emitUTF8"] = true;
          Json::Value json_obj;
          for (guint pos = 0; pos < items_len; pos++) {
            auto row = m_liststore->get_item(pos);
            std::stringstream ss;
            ss << "Song" << pos;
            std::string header = ss.str();
            json_obj[header]["Title"] = row->property_title().get_value().raw();
            json_obj[header]["Artist"] = row->property_author().get_value().raw();
            json_obj[header]["Link"] = row->property_link().get_value().raw();
            json_obj[header]["jMan"] = row->property_jman().get_value();
          }
         std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
         writer->write(json_obj, &file_out);
        }
      } catch (...) {
        //
      }
    });
  }
}