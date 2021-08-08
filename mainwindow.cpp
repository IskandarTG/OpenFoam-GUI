#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QFileSystemModel>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Load Text into the Path labels
    ui->blenderPath->setText(retrievePath(bPath));
    ui->projectPath->setText(retrievePath(pPath));


    //Setups File Tree View with Saved Project Path
    changeTreeViewRoot(pPath);
}

MainWindow::~MainWindow()
{
    //Call Saving Functions before deleting the ui
    on_saveBlenderPath_clicked();
    on_saveProjectPath_clicked();

    delete ui;
}

QString MainWindow::retrievePath(QString pathFile)
{
    QString res;
    QFile file(pathFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        res = stream.readLine();
        file.close();
    }
    return res;
}

void MainWindow::saveBlenderPath()
{
    QLineEdit* blenderPath = MainWindow::centralWidget()->findChild<QLineEdit*>("blenderPath");
    QDir dir(QCoreApplication::applicationDirPath());
    QString fileLoc = dir.relativeFilePath(bPath);
    QString pathString = blenderPath->text();
    QFile file(fileLoc);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << pathString;
        file.close();
    }

    allowSaveButton(ui->saveProjectPath,ui->blenderPath,bPath);
}

void MainWindow::on_nextButton_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{

}


void MainWindow::on_prevButton_clicked()
{
     ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
}


void MainWindow::on_openBlenderButton_clicked()
{
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::Directory);
  QString dirName = dialog.getExistingDirectory(this,"","/home/");
  ui->blenderPath->setText(dirName);
}

void MainWindow::on_openProjectButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString dirName = dialog.getExistingDirectory(this,"","/home/");
    ui->projectPath->setText(dirName);
}


void MainWindow::on_blenderPath_textChanged(const QString &arg1)
{
    allowSaveButton(ui->saveProjectPath,ui->blenderPath,bPath);
}


void MainWindow::on_projectPath_textChanged(const QString &arg1)
{
    allowSaveButton(ui->saveProjectPath,ui->projectPath,pPath);
}

void MainWindow::on_saveBlenderPath_clicked()
{
    /*
    * Saves the Blenderpath in the QLineEdit blenderpath to the file bPath.conf
    */

    QFile file(bPath);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
            file.write(ui->blenderPath->text().toUtf8());
            file.close();
    }
    allowSaveButton(ui->saveProjectPath,ui->blenderPath,bPath);
}

void MainWindow::on_saveProjectPath_clicked()
{
    QFile file(pPath);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
            file.write(ui->projectPath->text().toUtf8());
            file.close();
    }
    allowSaveButton(ui->saveProjectPath,ui->projectPath,pPath);
    changeTreeViewRoot(pPath);
}

void MainWindow::allowSaveButton(QPushButton *button,QLineEdit *lineEdit,QString _file)
{
    QFile file(_file);
    if(file.open(QIODevice::ReadWrite))
    {
        QString temp;
        QTextStream stream(&file);
        temp = stream.readLine();
        if(temp.compare(lineEdit->text())==0)
        {
            button->setEnabled(false);
        }
        else
        {
            button->setEnabled(true);
        }
        file.close();
    }
}

void MainWindow::changeTreeViewRoot(QString _file)
{
    QFile file(_file);
    QString temp;
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);

        temp = stream.readLine();
    }
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(temp);
    ui->condition_explorer->setModel(model);
    ui->condition_explorer->setRootIndex(model->index(temp));
}
