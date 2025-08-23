#ifndef GITMANAGER_H
#define GITMANAGER_H

#include <qobject.h>
#include <QProcess>
class GitManager : public QObject
{
    Q_OBJECT
public:
    explicit GitManager(QObject *parent = nullptr);
    bool setRepository(const QString &path);
    bool stageFile(const QString &filename);
    bool commit(const QString &message);
    bool deleteCommit(const QString &commitHash);
    QStringList getBranches();
    bool createBranch(const QString &name);
    bool deleteBranch(const QString &name);

signals:
    void commandFinished(bool success, const QString &output);
    void commandError(const QString &error);

private slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessError(QProcess::ProcessError error);

private:
    QString executeGitCommand(const QStringList &arguments);
    void executeGitCommandAsync(const QStringList &arguments);

    QString m_repositoryPath;
    QProcess *m_currentProcess;
};

#endif // GITMANAGER_H
