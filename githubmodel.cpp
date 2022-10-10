// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "githubmodel.h"

#include <QtCore>
#include <QtNetwork>

GitHubModel::GitHubModel(const QString &clientId) :
    githubWrapper(clientId)
{
    grant();
}

void GitHubModel::grant()
{
    connect(&githubWrapper, &GitHubWrapper::authenticated, this, &GitHubModel::update);
    githubWrapper.grant();
}

void GitHubModel::update()
{
    auto reply = githubWrapper.getUserProjects();

    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            emit error(reply->errorString());
            return;
        }
        const auto json = reply->readAll();
        qDebug() << json;
    });
}
