#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "gui.hpp"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::Gui),
    m_manager(new QNetworkAccessManager())
{
    m_ui->setupUi(this);
    connect(m_manager.get(), SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
}

Gui::~Gui()
{

}

void Gui::replyFinished(QNetworkReply *reply)
{
    QFile file("/home/alex/file");
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
    m_ui->statusBar->showMessage(QString("FTP reply recieved!"));
}

void Gui::on_button_clicked()
{
    const auto url = QUrl("ftp://" + m_ui->edit->text());
    m_manager->get(QNetworkRequest(url));
    m_ui->statusBar->showMessage(QString("Sending FTP request..."));
}
