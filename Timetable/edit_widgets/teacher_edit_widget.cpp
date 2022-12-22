#include "teacher_edit_widget.h"
#include "ui_teacher_edit_widget.h"

#include <QSqlTableModel>

TeacherEditWidget::TeacherEditWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherEditWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("teachers");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Отчество"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Должность"));

    ui->tableView->setModel(model);
    setWindowTitle("Преподаватели");
    resize(QSize(1200, 600));

    ui->tableView->resizeColumnsToContents();

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalHeader(header);

    ui->tableView->verticalHeader()->hide();

    ui->addPushButton->setDisabled(true);

    connect(ui->applyPushButton, SIGNAL(clicked(bool)), model, SLOT(submitAll()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(insertEntry()));
    connect(ui->removePushButton, SIGNAL(clicked(bool)), this, SLOT(removeEntry()));

    connect(ui->surnameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));
    connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));
    connect(ui->secondNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));
    connect(ui->positionLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->show();
}

TeacherEditWidget::~TeacherEditWidget()
{
    delete ui;
}

void TeacherEditWidget::insertEntry() {

    QString surname = ui->surnameLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString second_name = ui->secondNameLineEdit->text();
    QString position = ui->positionLineEdit->text();

    database->insertTeacher(surname, name, second_name, position);

    model->submitAll();

    ui->surnameLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->secondNameLineEdit->clear();
    ui->positionLineEdit->clear();
}

void TeacherEditWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}

void TeacherEditWidget::updateAddPushButton() {
    if (ui->surnameLineEdit->text().isEmpty() || ui->nameLineEdit->text().isEmpty() ||
            ui->secondNameLineEdit->text().isEmpty() || ui->positionLineEdit->text().isEmpty())
        ui->addPushButton->setDisabled(true);
    else
        ui->addPushButton->setDisabled(false);
}
