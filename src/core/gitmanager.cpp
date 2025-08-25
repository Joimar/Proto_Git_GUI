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

QStringList GitManager::getStatus()
{
    QString output = executeGitCommand({"status", "--porcelain"});
    return output.split('\n', Qt::SkipEmptyParts);
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

    // Clean format (* current, remotes/origins/...)
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
    if (!m_currentProcess) return;

    QString output = m_currentProcess->readAllStandardOutput();
    QString error = m_currentProcess->readAllStandardError();

    bool success = (exitCode == 0 && exitStatus == QProcess::NormalExit);

    if(success)
    {
        emit commandFinished(true, output);
    }else
    {
        emit commandFinished(false, error);
    }

    // Clean process
    m_currentProcess->deleteLater();
    m_currentProcess = nullptr;
}

void GitManager::onProcessError(QProcess::ProcessError error)
{
    QString errorString;
    switch (error)
    {   // Replace these strings to ts calls later
        case QProcess::FailedToStart:
            errorString = "Git not found or failed to start";
            break;
        case QProcess::Crashed:
            errorString = "Git process crashed";
            break;
        case QProcess::Timedout:
            errorString = "Git process timed out";
            break;
        default:
            errorString = "Unknown error occured";
    }

        emit commandError(errorString);

    if (m_currentProcess)
    {
        m_currentProcess->deleteLater();
        m_currentProcess = nullptr;
    }
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

void GitManager::executeGitCommandAsync(const QStringList &arguments)
{
    if (m_currentProcess && m_currentProcess->state() != QProcess::NotRunning)
    {
        m_currentProcess->kill();
        m_currentProcess->waitForFinished(1000);
    }

    // Creates new process
    m_currentProcess = new QProcess(this);
    m_currentProcess->setWorkingDirectory(m_repositoryPath);

    // Connects signals
    connect(m_currentProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &GitManager::onProcessFinished);
    connect(m_currentProcess, &QProcess::errorOccurred, this, &GitManager::onProcessError);

    // Executes command
    m_currentProcess->start("git", arguments);
}
//_____________________________________________________
