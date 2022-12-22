#include "subject_widget.h"
#include "ui_subject_widget.h"

SubjectWidget::SubjectWidget(Database* database, QWidget *parent)
    : QWidget(parent)
    , EntryWidget(database)
    , ui(new Ui::SubjectWidget)
{
    ui->setupUi(this);

    resize(QSize(600, 400));

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               "Название");

    setWindowTitle("Предметы");

    SubjectWidget::updateTable();

    setHeaders(ui->tableWidget);
}


void SubjectWidget::updateTable() {
    auto subjects = database->subjects();

    for (auto& subject : subjects) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(subject.name));
    }
}

SubjectWidget::~SubjectWidget()
{
    delete ui;
}
