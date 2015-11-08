#pragma once
#include <memory>
#include <QMainWindow>

class QNetworkAccessManager;
class QNetworkReply;

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
    void replyFinished(QNetworkReply *);
    void buttonClicked();

private:
    std::unique_ptr<Ui::Gui> m_ui;
    QNetworkAccessManager *m_manager;
};

