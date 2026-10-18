#ifndef GITADDFILESFORM_H
#define GITADDFILESFORM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class GitAddFilesForm;
}
QT_END_NAMESPACE

class GitAddFilesForm : public QWidget
{
    Q_OBJECT

public:
    GitAddFilesForm(QWidget *parent = nullptr);
    ~GitAddFilesForm();
};

#endif // GITADDFILESFORM_H
