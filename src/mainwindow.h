#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model/gitmanager.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_statusButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void TestQProcess();

private:
    Ui::MainWindow *ui;
    GitManager *m_gitManager;
};
#endif // MAINWINDOW_H
