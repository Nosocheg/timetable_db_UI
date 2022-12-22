#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "login_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    LoginDialog* loginDlg;

private:
    Ui::MainWindow *ui;

    Database* database;

    UserType userType;
    int id;

    void createReductionMenu();
    void createUsersMenu();

private slots:
    void showLoginDialog();

    void timetablesTable();
    void studentsTable();
    void teachersTable();
    void groupsTable();
    void audiencesTable();
    void subjectsTable();

    void timetablesReductionTable();
    void studentsReductionTable();
    void teachersReductionTable();
    void groupsReductionTable();
    void audiencesReductionTable();
    void subjectsReductionTable();

    void usersTable();
};
#endif // MAINWINDOW_H
