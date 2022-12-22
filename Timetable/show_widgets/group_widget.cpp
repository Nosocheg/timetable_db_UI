#include "group_widget.h"
#include "ui_group_widget.h"

GroupWidget::GroupWidget(Database* database, QWidget *parent)
    : QWidget(parent)
    , EntryWidget(database)
    , ui(new Ui::GroupWidget)
{
    ui->setupUi(this);

    resize(QSize(600, 400));

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               "Название");

    setWindowTitle("Группы");

    GroupWidget::updateTable();

    setHeaders(ui->tableWidget);
}


void GroupWidget::updateTable() {
    auto groups = database->groups();

    for (auto& group : groups) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(group.name));
    }
}

GroupWidget::~GroupWidget()
{
    delete ui;
}
