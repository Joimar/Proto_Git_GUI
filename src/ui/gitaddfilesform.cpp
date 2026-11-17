#include "gitaddfilesform.h"
#include <QProcess>
#include <QDebug>
#include <iostream>
#include <ostream>
#include <QFileDialog>

GitAddFilesForm::GitAddFilesForm(QWidget *parent):QWidget(parent)
{

}

GitAddFilesForm::~GitAddFilesForm()
{
    // Corpo do destruidor (pode ficar vazio se não houver ponteiros manuais para deletar)
}