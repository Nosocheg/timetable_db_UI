#include "login_dialog.h"
#include "ui_login_dialog.h"

LoginDialog::LoginDialog(Database* database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    , database(database)
{
    ui->setupUi(this);

    setWindowTitle("Вход в систему");

    ui->loginPushButton->setDisabled(true);

    connect(ui->loginPushButton, SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->exitPushButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(ui->loginLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updatePushButtonState(QString)));
    connect(ui->passwordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updatePushButtonState(QString)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::updatePushButtonState(const QString&) {

    if (ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty())
        ui->loginPushButton->setDisabled(true);
    else
        ui->loginPushButton->setDisabled(false);
}

QString LoginDialog::login() const {
    return ui->loginLineEdit->text();
}

QString LoginDialog::password() const {
    return ui->passwordLineEdit->text();
}

UserType LoginDialog::type() const {
    return userType;
}

int LoginDialog::id() const {
    return _id;
}

void LoginDialog::check() {

    QPair<UserType, int> info = database->checkLoginPassword(login(), password());
    userType = info.first;
    _id = info.second;

    if (userType == UserType::Rejected) {
        QMessageBox::critical(this, "Доступ не разрешён", "Данная комбинация логина и пароля недействительна!");
        return;
    }

    accept();
}
