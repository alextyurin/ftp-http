#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "gui.hpp"
#include "ui_gui.h"

namespace
{
const auto block_size = 65536;
}

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::Gui),
    m_manager(new QNetworkAccessManager())
{
    m_ui->setupUi(this);
    m_ui->centralWidget->setLayout(m_ui->main);
    m_ui->filepath->setText(QDir::homePath());
    connect(m_manager.get(), SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    connect(m_ui->browse_button, SIGNAL(clicked()), this, SLOT(browse()));
}

Gui::~Gui()
{

}

void Gui::replyFinished(QNetworkReply *reply)
{
    QString filename = m_ui->edit->text().split("/").back();
    QFile file(m_ui->filepath->text() + filename);
    file.remove();
    if (!file.open(QIODevice::Append))
    {
        m_ui->statusBar->showMessage(QString("Can't write to file!"));
        return;
    }
    auto bytes = 0;
    while (bytes = reply->bytesAvailable())
    {
        const auto size = (bytes > block_size) ? block_size : bytes;
        file.write(reply->read(size), size);
    }
    file.close();
    m_ui->statusBar->showMessage(QString("FTP reply recieved!"));
}

void Gui::on_button_clicked()
{
    qDebug() << "ftp://" + m_ui->edit->text();
    m_manager->get(QNetworkRequest(QUrl("ftp://" + m_ui->edit->text())));
    m_ui->statusBar->showMessage(QString("Sending FTP request..."));
}

void Gui::browse()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    m_ui->filepath->setText(dialog.getExistingDirectory(this, "Choose Directory", m_ui->filepath->text()));
}
