#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Retrieve Blender Path from bPath.conf
    QLineEdit* blenderPath = MainWindow::centralWidget()->findChild<QLineEdit*>("blenderPath");
    blenderPath->setText(MainWindow::retrievePath("bPath.conf"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::retrievePath(QString pathFile)
{
    QString res;
    QDir dir(QCoreApplication::applicationDirPath());
    QString fileLoc = dir.relativeFilePath(pathFile);
    QFile file(fileLoc);
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream >> res;
        file.close();
    }
    return res;
}

void MainWindow::on_nextButton_clicked()
{
    QTabWidget* tabwidget = MainWindow::centralWidget()->findChild<QTabWidget*>("tabWidget");
    tabwidget->setCurrentIndex(tabwidget->currentIndex()+1);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{

}


void MainWindow::on_prevButton_clicked()
{
    QTabWidget* tabwidget = MainWindow::centralWidget()->findChild<QTabWidget*>("tabWidget");
    tabwidget->setCurrentIndex(tabwidget->currentIndex()-1);
}


void MainWindow::on_openBlenderButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"),"","");
    QLineEdit* blenderPath = MainWindow::centralWidget()->findChild<QLineEdit*>("blenderPath");
    blenderPath->setText(fileName);
}


void MainWindow::on_blenderPath_textChanged(const QString &arg1)
{
    QDir dir(QCoreApplication::applicationDirPath());
    QString fileLoc = dir.relativeFilePath("bPath.conf");
    QFile file(fileLoc);
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << arg1;
        file.close();
    }
}

