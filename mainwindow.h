#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_nextButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_prevButton_clicked();

    void on_openBlenderButton_clicked();

    void on_blenderPath_textChanged(const QString &arg1);

    QString retrievePath(QString pathFile);

    void on_MainWindow_destroyed();

private:
    void saveBlenderPath();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
