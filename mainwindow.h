#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "githubmodel.h"

#include <QMainWindow>
#include <QDebug>
#include <QDesktopServices>

#include <QtNetworkAuth>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QOAuth2AuthorizationCodeFlow oauth2;

    bool permanent = false;
};
#endif // MAINWINDOW_H
