#include <glibmm.h>
#include <locale>
#include "MainWindow.h"

void on_app_activate(Glib::RefPtr<Gtk::Application>& app) {
  auto refBuilder = Gtk::Builder::create();
  try {
     refBuilder->add_from_resource(GLADE_FILE);
  } catch(const Gtk::BuilderError& ex) {
    std::cout << "Error: " << ex.what() << std::endl;
    return;
  }
  
  auto toplevel = Gtk::Builder::get_widget_derived<ytdlp4mm::MyMainWindow>(refBuilder, "toplevel", app);
  app->signal_shutdown().connect([toplevel](){
    delete toplevel;
    std::cout << "Toplevel deleted" << std::endl;
  });
  app->add_window(*toplevel);
  toplevel->present();
}

int main(int argc, char* argv[]) {
  Glib::setenv("GTK_CSD", PROGRAM_GTK_CSD, TRUE);
#ifdef WITH_CAIRO
  Glib::setenv("GSK_RENDERER", "CAIRO", TRUE); // optimal
#else
  Glib::unsetenv("GSK_RENDERER");
#endif
  
  Glib::ustring directorio = Glib::path_get_dirname(argv[0]);
  Glib::ustring locale = Glib::build_filename(directorio, "locale");
#ifdef G_OS_WIN32  
  Glib::set_init_to_users_preferred_locale(false);
#else
  Glib::set_init_to_users_preferred_locale(true);
#endif
  bindtextdomain(PROGRAM_NAME, locale.c_str());
  bind_textdomain_codeset(PROGRAM_NAME, "UTF-8");
  textdomain(PROGRAM_NAME);
  
  auto app = Gtk::Application::create(PROGRAM_ID);
  
  app->signal_activate().connect([&app](){
    on_app_activate(app);
  });
  
  return app->run(argc, argv);
}