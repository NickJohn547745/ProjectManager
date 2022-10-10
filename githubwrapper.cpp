#include "githubwrapper.h"

#include <QtGui>
#include <QtCore>
#include <QtNetworkAuth>

const QUrl projectUrl("https://api.github.com/users/NickJohn547745/projects");

GitHubWrapper::GitHubWrapper(QObject *parent) : QObject(parent)
{
    auto replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    oauth2.setReplyHandler(replyHandler);
    oauth2.setClientIdentifier("a03f73c9d240585dbef3");
    oauth2.setClientIdentifierSharedKey("1aa288e26b98a432b9057485aa38693219d495f5");
    oauth2.setAuthorizationUrl(QUrl("https://github.com/login/oauth/authorize"));
    oauth2.setAccessTokenUrl(QUrl("https://github.com/login/oauth/access_token"));
    oauth2.setScope("repo project user");
    oauth2.setContentType(QAbstractOAuth::ContentType::Json);
    oauth2.setModifyParametersFunction(buildModifyParametersFunction());

    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](
            QAbstractOAuth::Status status) {
        qDebug() << "Successfully authenticated.";
        if (status == QAbstractOAuth::Status::Granted)
            emit authenticated();
    });


    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
            &QDesktopServices::openUrl);
}

GitHubWrapper::GitHubWrapper(const QString &clientIdentifier, QObject *parent) :
    GitHubWrapper(parent)
{
    oauth2.setClientIdentifier(clientIdentifier);
}

QAbstractOAuth::ModifyParametersFunction GitHubWrapper::buildModifyParametersFunction()
{
    const QUrl clientIdentifier = oauth2.clientIdentifier();
    const QUrl clientIdentifierSharedKey = oauth2.clientIdentifierSharedKey();
    return [clientIdentifier,clientIdentifierSharedKey, this]
            (QAbstractOAuth::Stage stage, QVariantMap *parameters){

        if(stage == QAbstractOAuth::Stage::RequestingAuthorization){
            if (isPermanent()) {
                parameters->insert("duration", "permanent");
            }
            parameters->insert("redirect_uri","https://www.google.com");
        }
        qDebug() << parameters->toStdMap();
    };
}

QNetworkReply *GitHubWrapper::getUserProjects()
{
    qDebug() << "Getting user's projects...";
    return oauth2.get(projectUrl);
}

bool GitHubWrapper::isPermanent() const
{
    return permanent;
}

void GitHubWrapper::setPermanent(bool value)
{
    permanent = value;
}

void GitHubWrapper::grant()
{
    oauth2.grant();
    qDebug() << "Granting...";
    getUserProjects();
}

void GitHubWrapper::subscribeToLiveUpdates()
{

}
