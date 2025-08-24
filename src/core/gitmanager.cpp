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

bool GitManager::stageFile(const QString &fileName)
{
    QString output = executeGitCommand({"add", fileName});
    return !output.isNull();
}

bool GitManager::commit(const QString &message)
{
    QString output = executeGitCommand({"commit", "-m", message});
    return !output.isNull();
}

bool GitManager::deleteCommit(const QString &commitHash)
{
    QString output = executeGitCommand({"reset", "--hard", commitHash});
    return !output.isNull();
}

QStringList GitManager::getBranches()
{
    QString output = executeGitCommand({"branch", "-a"});
    QStringList branches = output.split('\n', Qt::SkipEmptyParts);

    for (QString &branch : branches)
    {
        branch = branch.trimmed();
        if (branch.startsWith("* "))
        {
            branch = branch.mid(2);
        }
    }
    return branches;
}

// Slot Functions___________________________________

void GitManager::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{

}

void GitManager::onProcessError(QProcess::ProcessError)
{

}

//__________________________________________________


// Private Functions________________________________

QString GitManager::executeGitCommand(const QStringList &arguments)
{
    QProcess process;
    process.setWorkingDirectory(m_repositoryPath);

    // Define environment if necessary
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    process.setProcessEnvironment(env);

    // Execute command
    process.start("git", arguments);

    // Waits 30 secs by using timeout
    if(!process.waitForFinished(30000))
    {
        process.kill();
        return QString();
    }

    if(process.exitCode() != 0)
    {
        QString error = process.readAllStandardError();
        emit commandError(error);
        return QString();
    }

    return process.readAllStandardOutput();
}

//_____________________________________________________
