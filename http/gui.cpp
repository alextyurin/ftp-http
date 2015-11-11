#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "gui.hpp"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::Gui)
{
    m_ui->setupUi(this);
    m_ui->centralWidget->setLayout(m_ui->main);
    connect(m_ui->button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
}

Gui::~Gui()
{

}

void Gui::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
         m_ui->view->clear();
         m_ui->statusBar->showMessage(reply->errorString());
    }
    else
    {
        m_ui->view->setPlainText(reply->readAll());
        m_ui->statusBar->showMessage(QString("HTTP reply recieved!"));
    }
}

void Gui::buttonClicked()
{

    const auto url = QUrl("http://" + m_ui->edit->text());
    m_manager->get(QNetworkRequest(url));
    m_ui->statusBar->showMessage(QString("Sending HTTP request..."));

}
