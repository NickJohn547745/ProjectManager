#ifndef GITHUBMODEL_H
#define GITHUBMODEL_H

#include "githubwrapper.h"

#include <QtCore>

QT_FORWARD_DECLARE_CLASS(QNetworkReply)

class GitHubModel : public QObject
{
    Q_OBJECT

public:
    GitHubModel(const QString &clientId);

    void grant();

signals:
    void error(const QString &errorString);

private slots:
    void update();

private:
    GitHubWrapper githubWrapper;
    QPointer<QNetworkReply> liveThreadReply;
    QList<QJsonObject> threads;
};

#endif // GitHubModel_H
