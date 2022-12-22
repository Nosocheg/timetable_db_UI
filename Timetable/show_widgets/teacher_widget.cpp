#include "teacher_widget.h"
#include "ui_teacher_widget.h"

TeacherWidget::TeacherWidget(Database* database, QWidget *parent)
    : QWidget(parent)
    , EntryWidget(database)
    , ui(new Ui::TeacherWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               "Фамилия Имя Отчество" << "Должность");

    setWindowTitle("Преподаватели");

    TeacherWidget::updateTable();
    TeacherWidget::loadVariants();

    setHeaders(ui->tableWidget);

    connect(ui->filterPushButton, SIGNAL(clicked(bool)), this, SLOT(filter()));
}

void TeacherWidget::loadVariants() {
    auto teachers = database->teachers();

    QSet<QString> positions;

    for (int i = 0; i < teachers.size(); ++i) {
        QString position = teachers[i].position;
        positions.insert(position);
    }

    QList<QString> sortedPositions(positions.begin(), positions.end());

    sortedPositions.sort();

    createModel(sortedPositions, ui->positionComboBox);
}

void TeacherWidget::updateTable() {
    auto teachers = database->teachers();

    for (auto& teacher : teachers) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(teacher.full_name));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(teacher.position));
    }
}

void TeacherWidget::filter() {

    QList<QString> positions = checkedItems(ui->positionComboBox);

    if (positions.isEmpty())
        return;

    auto teachers = database->filterTeachers(positions);

    ui->tableWidget->setRowCount(0);

    for (auto& teacher : teachers) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(teacher.full_name));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(teacher.position));
    }
}

TeacherWidget::~TeacherWidget()
{
    delete ui;
}
