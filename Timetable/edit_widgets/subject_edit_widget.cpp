#include "subject_edit_widget.h"
#include "ui_subject_edit_widget.h"

#include <QSqlTableModel>

SubjectEditWidget::SubjectEditWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectEditWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("subjects");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));

    ui->tableView->setModel(model);
    setWindowTitle("Предметы");
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

SubjectEditWidget::~SubjectEditWidget()
{
    delete ui;
}

void SubjectEditWidget::insertEntry() {

    QString name = ui->nameLineEdit->text();

    database->insertSubject(name);

    model->submitAll();

    ui->nameLineEdit->clear();
}

void SubjectEditWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}

void SubjectEditWidget::updateAddPushButton() {
    if (ui->nameLineEdit->text().isEmpty())
        ui->addPushButton->setDisabled(true);
    else
        ui->addPushButton->setDisabled(false);
}
