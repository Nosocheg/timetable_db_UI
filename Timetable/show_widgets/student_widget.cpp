#include "student_widget.h"
#include "ui_student_widget.h"

StudentWidget::StudentWidget(Database* database, QWidget *parent)
    : QWidget(parent)
    , EntryWidget(database)
    , ui(new Ui::StudentWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               "Фамилия Имя Отчество" << "Группа");

    setWindowTitle("Студенты");

    StudentWidget::updateTable();
    StudentWidget::loadVariants();

    setHeaders(ui->tableWidget);

    connect(ui->filterPushButton, SIGNAL(clicked(bool)), this, SLOT(filter()));
}

void StudentWidget::loadVariants() {
    auto students = database->students();

    QSet<QString> groups;

    for (int i = 0; i < students.size(); ++i) {
        QString group = students[i].name_group;
        groups.insert(group);
    }

    QList<QString> sortedGroups(groups.begin(), groups.end());

    sortedGroups.sort();

    createModel(sortedGroups, ui->groupComboBox);
}

void StudentWidget::updateTable() {
    auto students = database->students();

    for (auto& student : students) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(student.full_name));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(student.name_group));
    }
}

void StudentWidget::filter() {

    QList<QString> groups = checkedItems(ui->groupComboBox);

    if (groups.isEmpty())
        return;

    auto students = database->filterStudents(groups);

    ui->tableWidget->setRowCount(0);

    for (auto& student : students) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(student.full_name));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(student.name_group));
    }
}

StudentWidget::~StudentWidget()
{
    delete ui;
}
