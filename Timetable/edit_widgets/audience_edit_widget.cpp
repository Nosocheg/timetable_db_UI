#include "audience_edit_widget.h"
#include "ui_audience_edit_widget.h"

#include <QSqlTableModel>

AudienceEditWidget::AudienceEditWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudienceEditWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("audiences");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Номер"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Корпус"));

    ui->tableView->setModel(model);
    setWindowTitle("Аудитории");
    resize(QSize(1200, 600));

    ui->tableView->resizeColumnsToContents();

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalHeader(header);

    ui->tableView->verticalHeader()->hide();

    ui->numberSpinBox->setMinimum(1);

    ui->addPushButton->setDisabled(true);

    connect(ui->applyPushButton, SIGNAL(clicked(bool)), model, SLOT(submitAll()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(insertEntry()));
    connect(ui->removePushButton, SIGNAL(clicked(bool)), this, SLOT(removeEntry()));


    connect(ui->buildingLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAddPushButton()));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->show();
}

AudienceEditWidget::~AudienceEditWidget()
{
    delete ui;
}

void AudienceEditWidget::insertEntry() {

    QString number = ui->numberSpinBox->text();
    QString building = ui->buildingLineEdit->text();

    database->insertAudience(number, building);

    model->submitAll();

    ui->buildingLineEdit->clear();
}

void AudienceEditWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}

void AudienceEditWidget::updateAddPushButton() {
    if (ui->buildingLineEdit->text().isEmpty())
        ui->addPushButton->setDisabled(true);
    else
        ui->addPushButton->setDisabled(false);
}
