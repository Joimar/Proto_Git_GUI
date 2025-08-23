#include "gitmanager.h"

#include <QDir>

GitManager::GitManager(QObject *parent) : QObject(parent), m_currentProcess(nullptr)
{

}

bool GitManager::setRepository(const QString &path)
{
    QDir dir(path);
    if(!dir.exists() || !dir.exists(".git")) return false;

    m_repositoryPath = path;
    return true;
}

void GitManager::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{

}

void GitManager::onProcessError(QProcess::ProcessError)
{

}
