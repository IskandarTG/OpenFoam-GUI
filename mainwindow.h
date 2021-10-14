#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QKeyEvent>
#include "helpwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QDir projectPath;
    bool isHelpWindowOpen=false;

private slots:
    void on_Next_Button_clicked();
    void on_Previous_Button_clicked();
    void on_CheckProjectDir_Button_clicked();
    void on_SetProjectDir_Button_clicked();
    void on_BlockMesh_Button_clicked();
    void on_CheckBleDir_Button_clicked();
    void on_SetBleDir_Button_clicked();
    void on_HelpWindow_Button_clicked();
    void on_HelpWindow_closed();

private:
    Ui::MainWindow *ui;
    HelpWindow *helpWindow;
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
