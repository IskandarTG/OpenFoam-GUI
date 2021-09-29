#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Next_Button_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
}

void MainWindow::on_Previous_Button_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
}


void MainWindow::on_CheckProjectDir_Button_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Your current Project Directory is:");
    msgBox.setInformativeText(QDir::currentPath());
    msgBox.exec();
}

void MainWindow::on_SetProjectDir_Button_clicked()
{
    QDir::setCurrent(ui->ProjectDir->text());
}


void MainWindow::on_Mesh_Button_clicked()
{
    /*
    QProcess Mesh_Process;
    ui->Mesh_Output->clear();
    Mesh_Process.setCurrentReadChannel(QProcess::StandardOutput);
    Mesh_Process.start("blockMesh");
    //ui->Mesh_Output->append(Mesh_Process.readAllStandardOutput());
    //QProcess* process = qobject_cast<QProcess*>(sender());
    //   if (process)
    //       ui->Mesh_Output->append(process->readAllStandardOutput());
    Mesh_Process.waitForFinished(-1);
    */
    ui->Mesh_Output->clear();
    ui->Mesh_Error->clear();
    QStringList args;
    args << "-case" << QDir::currentPath();
    QProcess *meshProcess = new QProcess();
    meshProcess->setCurrentReadChannel(QProcess::StandardError);
    meshProcess->start("blockMesh",args);
    meshProcess->waitForFinished();
    QString output(meshProcess->readAllStandardOutput());
    QString error(meshProcess->readAllStandardError());
    if(error == "")
        error = "No errors!";
    ui->Mesh_Output->append(output);
    ui->Mesh_Error->append(error);
}

void MainWindow::on_CheckBleDir_Button_clicked()
{
    QFile file("Blender_Directory.txt");
    if(!file.exists())
    {
        qCritical() << "Directory not found, set a directory first";
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
    }
    QTextStream stream(&file);
    QMessageBox msgBox;
    msgBox.setText("Your current Blender Directory is:");
    msgBox.setInformativeText(stream.readAll());
    msgBox.exec();
}


void MainWindow::on_SetBleDir_Button_clicked()
{
    QFile file("Blender_Directory.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << file.errorString();
    }
    QTextStream stream(&file);
    stream << ui->BleDir->text();
    file.close();
}

