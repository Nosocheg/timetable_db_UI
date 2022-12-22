#include "student_edit_widget.h"
#include "ui_student_edit_widget.h"

#include <QSqlTableModel>

StudentEditWidget::StudentEditWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentEditWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("students");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Отчество"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id группы"));

    ui->tableView->setModel(model);
    setWindowTitle("Студенты");
    resize(QSize(1200, 600));

    ui->tableView->resizeColumnsToContents();

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalHeader(header);

    ui->tableView->verticalHeader()->hide();

    auto groups = database->groups();

    for (auto& group: groups) {
        ui->groupComboBox->addItem(QString::number(group.id));
    }

    ui->addPushButton->setDisabled(true);

    connect(ui->applyPushButton, SIGNAL(clicked(bool)), model, SLOT(submitAll()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(insertEntry()));
    connect(ui->removePushButton, SIGNAL(clicked(bool)), this, SLOT(removeEntry()));

    connect(ui->surnameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));
    connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));
    connect(ui->secondNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->show();
}

StudentEditWidget::~StudentEditWidget()
{
    delete ui;
}

void StudentEditWidget::insertEntry() {

    QString surname = ui->surnameLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString second_name = ui->secondNameLineEdit->text();
    QString id_group = ui->groupComboBox->currentText();

    database->insertStudent(surname, name, second_name, id_group);

    model->submitAll();

    ui->surnameLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->secondNameLineEdit->clear();
}

void StudentEditWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}

void StudentEditWidget::updateAddPushButton() {
    if (ui->surnameLineEdit->text().isEmpty() || ui->nameLineEdit->text().isEmpty() ||
            ui->secondNameLineEdit->text().isEmpty())
        ui->addPushButton->setDisabled(true);
    else
        ui->addPushButton->setDisabled(false);
}
