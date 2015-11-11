#pragma once
#include <memory>
#include <QMainWindow>

class QNetworkReply;
class QNetworkAccessManager;

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    
private slots:
    void on_button_clicked();
    void replyFinished(QNetworkReply *);

private:
    std::unique_ptr<Ui::Gui> m_ui;
    std::unique_ptr<QNetworkAccessManager> m_manager;
};

