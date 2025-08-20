#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"
#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    TestQProcess();
    ui->setupUi(this);
    setWindowTitle("Proto Git GUI");
}

void MainWindow::TestQProcess()
{
    QProcess process;

    // Definy work directory
    process.setWorkingDirectory("/home/joimar/PROJETOS PESSOAIS/Repositorios/Proto_Git_GUI");

    process.start("git", QStringList() << "status");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();
    QProcess gitVersion;

    gitVersion.start("git", {"--version"});
    qDebug() << "Git version" << gitVersion.readAllStandardOutput().trimmed();
    qDebug() << "Git available" << (gitVersion.exitCode() == 0);

    qDebug() << "Output: " << output;
    qDebug() << "Error: " << error;
    qDebug() << "Exit code: " << process.exitCode();


}

MainWindow::~MainWindow()
{
    delete ui;
}
