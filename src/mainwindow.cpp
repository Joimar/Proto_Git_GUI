#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <iostream>
#include <ostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_gitManager(new GitManager(this))
{
    TestQProcess();
    ui->setupUi(this);
    setWindowTitle("Proto Git GUI");

    connect(ui->gitStatusButton, &QPushButton::clicked, this, &MainWindow::on_statusButton_clicked);
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

void MainWindow::on_statusButton_clicked()
{
    // This code will execute when the pushButton is clicked
    std::cout << "Button clicked!" << std::endl;
    // Add your desired actions here
    QStringList output = m_gitManager->getStatus();

    for(const QString &str:output)
    {
        std::cout << str.toStdString() << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
