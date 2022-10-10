// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GitHubWrapper_H
#define GitHubWrapper_H

#include <QtCore>
#include <QtNetwork>

#include <QOAuth2AuthorizationCodeFlow>

class GitHubWrapper : public QObject
{
    Q_OBJECT

public:
    GitHubWrapper(QObject *parent = nullptr);
    GitHubWrapper(const QString &clientIdentifier, QObject *parent = nullptr);

    QNetworkReply *getUserProjects();

    bool isPermanent() const;
    void setPermanent(bool value);

    QAbstractOAuth::ModifyParametersFunction buildModifyParametersFunction();
public slots:
    void grant();
    void subscribeToLiveUpdates();

signals:
    void authenticated();
    void subscribed(const QUrl &url);

private:
    QOAuth2AuthorizationCodeFlow oauth2;
    bool permanent = false;
};

#endif // GitHubWrapper_H
