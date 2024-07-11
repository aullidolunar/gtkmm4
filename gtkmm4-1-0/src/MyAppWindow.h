#ifndef _MYAPPWINDOW_H_INC_
#define _MYAPPWINDOW_H_INC_

#include <gtkmm/applicationwindow.h>

class MyAppWindow : public Gtk::ApplicationWindow
{
private:

public:
	MyAppWindow();
	~MyAppWindow() override;

protected:
};

#endif
