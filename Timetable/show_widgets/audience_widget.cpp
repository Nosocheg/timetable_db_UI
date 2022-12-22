#include "audience_widget.h"
#include "ui_audience_widget.h"

AudienceWidget::AudienceWidget(Database* database, QWidget *parent)
    : QWidget(parent)
    , EntryWidget(database)
    , ui(new Ui::AudienceWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               "Номер аудитории" << "Корпус");

    setWindowTitle("Аудитории");

    AudienceWidget::updateTable();
    AudienceWidget::loadVariants();

    setHeaders(ui->tableWidget);

    connect(ui->filterPushButton, SIGNAL(clicked(bool)), this, SLOT(filter()));
}

void AudienceWidget::loadVariants() {
    auto audiences = database->audiences();

    QSet<QString> numbers, buildings;

    for (int i = 0; i < audiences.size(); ++i) {
        QString number = QString::number(audiences[i].number);
        QString building = audiences[i].building;

        numbers.insert(number);
        buildings.insert(building);
    }

    QList<QString> sortedNumbers(numbers.begin(), numbers.end()),
                   sortedBuildings(buildings.begin(), buildings.end());

    sortedNumbers.sort();
    sortedBuildings.sort();

    createModel(sortedNumbers, ui->numberComboBox);
    createModel(sortedBuildings, ui->buildingComboBox);
}

void AudienceWidget::updateTable() {
    auto audiences = database->audiences();

    for (auto& audience : audiences) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(audience.number)));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(audience.building));
    }
}

void AudienceWidget::filter() {

    QList<QString> numbers = checkedItems(ui->numberComboBox);
    QList<QString> buildings = checkedItems(ui->buildingComboBox);

    if (numbers.isEmpty() || buildings.isEmpty())
        return;

    auto audiences = database->filterAudiences(numbers, buildings);

    ui->tableWidget->setRowCount(0);

    for (auto& audience : audiences) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(audience.number)));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(audience.building));
    }
}

AudienceWidget::~AudienceWidget()
{
    delete ui;
}
