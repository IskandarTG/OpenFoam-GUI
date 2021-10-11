#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Mesh_Error->hide();
    ui->MeshError_Label->hide();
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
    msgBox.setInformativeText(projectPath.path());
    msgBox.exec();
}

void MainWindow::on_SetProjectDir_Button_clicked()
{
    QStringList path;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        path = dialog.selectedFiles();
    }
    qCritical() << path;
    if(path.count() != 0)
    {
        projectPath.setPath(path.at(0));
        ui->ProjectDir_LineEdit->setText(projectPath.path());
        QDir meshPath(projectPath.path()+"/constant");
        if(meshPath.exists())
        {
            QFileSystemModel *meshModel = new QFileSystemModel;
            meshModel->setRootPath(meshPath.path());
            ui->PolyMesh_TreeView->setModel(meshModel);
            ui->PolyMesh_TreeView->setRootIndex(meshModel->index(meshPath.path()));
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Your selected path is not a OpenFOAM project");
            msgBox.exec();
        }
    }


}


void MainWindow::on_BlockMesh_Button_clicked()
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
    args << "-case" << projectPath.path();
    QProcess *meshProcess = new QProcess();
    meshProcess->setCurrentReadChannel(QProcess::StandardError);
    meshProcess->start("blockMesh",args);
    meshProcess->waitForFinished();
    QString output(meshProcess->readAllStandardOutput());
    QString error(meshProcess->readAllStandardError());
    if(error == "")
    {
        ui->Mesh_Error->hide();
        ui->MeshError_Label->hide();
    }
    else
    {
        ui->Mesh_Error->show();
        ui->MeshError_Label->show();
    }
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
    stream << ui->BlenderDir_LineEdit->text();
    file.close();
}

