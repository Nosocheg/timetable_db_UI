#include "user_widget.h"
#include "ui_user_widget.h"

#include <QSqlTableModel>

UserWidget::UserWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("users");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Логин"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Пароль"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Роль"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id студента"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id преподавателя"));

    ui->tableView->setModel(model);
    setWindowTitle("Пользователи");
    resize(QSize(1200, 600));

    ui->tableView->resizeColumnsToContents();

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalHeader(header);

    ui->tableView->verticalHeader()->hide();

    ui->idSpinBox->setMinimum(1);

    ui->roleComboBox->addItems(QStringList() << "Студент" << "Преподаватель" << "Модератор" << "Администратор");

    ui->addPushButton->setDisabled(true);

    connect(ui->applyPushButton, SIGNAL(clicked(bool)), model, SLOT(submitAll()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(insertEntry()));
    connect(ui->removePushButton, SIGNAL(clicked(bool)), this, SLOT(removeEntry()));


    connect(ui->loginLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));
    connect(ui->passwordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->show();
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::insertEntry() {

    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString role = ui->roleComboBox->currentText();
    QString id = ui->idSpinBox->text();

    database->insertUser(login, password, role, id);

    model->submitAll();

    ui->loginLineEdit->clear();
    ui->passwordLineEdit->clear();
}

void UserWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}

void UserWidget::updateAddPushButton() {
    if (ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty())
        ui->addPushButton->setDisabled(true);
    else
        ui->addPushButton->setDisabled(false);
}
