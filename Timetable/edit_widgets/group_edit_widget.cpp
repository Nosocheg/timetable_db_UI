#include "group_edit_widget.h"
#include "ui_group_edit_widget.h"

#include <QSqlTableModel>

GroupEditWidget::GroupEditWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupEditWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("groups");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));

    ui->tableView->setModel(model);
    setWindowTitle("Группы");
    resize(QSize(800, 600));

    ui->tableView->resizeColumnsToContents();

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalHeader(header);

    ui->tableView->verticalHeader()->hide();

    ui->addPushButton->setDisabled(true);

    connect(ui->applyPushButton, SIGNAL(clicked(bool)), model, SLOT(submitAll()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(insertEntry()));
    connect(ui->removePushButton, SIGNAL(clicked(bool)), this, SLOT(removeEntry()));


    connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->show();
}

GroupEditWidget::~GroupEditWidget()
{
    delete ui;
}

void GroupEditWidget::insertEntry() {

    QString name = ui->nameLineEdit->text();

    database->insertGroup(name);

    model->submitAll();

    ui->nameLineEdit->clear();
}

void GroupEditWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}

void GroupEditWidget::updateAddPushButton() {
    if (ui->nameLineEdit->text().isEmpty())
        ui->addPushButton->setDisabled(true);
    else
        ui->addPushButton->setDisabled(false);
}
