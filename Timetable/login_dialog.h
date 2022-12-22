#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include "database.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(Database* database, QWidget *parent = nullptr);
    ~LoginDialog();

    QString login() const;
    QString password() const;

    UserType type() const;
    int id() const;

private:
    Ui::LoginDialog *ui;
    Database* database;

    UserType userType;
    int _id;

private slots:
    void updatePushButtonState(const QString&);
    void check();
};

#endif // LOGIN_DIALOG_H
