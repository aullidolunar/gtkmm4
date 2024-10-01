#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>

class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow();
  ~MainWindow() override;
};

#endif