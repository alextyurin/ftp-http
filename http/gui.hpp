#ifndef GUI_HPP
#define GUI_HPP

#include <QMainWindow>

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    
private:
    Ui::Gui *ui;
};

#endif // GUI_HPP
