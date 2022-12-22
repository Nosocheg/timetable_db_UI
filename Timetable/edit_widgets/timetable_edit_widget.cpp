#include "timetable_edit_widget.h"
#include "ui_timetable_edit_widget.h"

#include <QSqlTableModel>

TimetableEditWidget::TimetableEditWidget(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimetableEditWidget),
    database(database)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, database->table);

    model->setTable("timetables");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Семестр"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("День"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Время"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id аудитории"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id группы"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id преподавателя"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("id предмета"));

    ui->tableView->setModel(model);
    setWindowTitle("Расписание");
    resize(QSize(1400, 600));

    ui->tableView->resizeColumnsToContents();

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalHeader(header);

    ui->tableView->verticalHeader()->hide();

    ui->semesterSpinBox->setMinimum(1);

    ui->dayComboBox->addItems(QStringList()
        << "Понедельник" << "Вторник" << "Среда"
        << "Четверг" << "Пятница" << "Суббота"
        << "Воскресенье");

    ui->timeComboBox->addItems(QStringList()
        << "9:00" << "10:40" << "12:20"
        << "14:00" << "15:40" << "17:20"
        << "19:00");

    auto audiences = database->audiences();

    for (auto& audience: audiences) {
        ui->audienceComboBox->addItem(QString::number(audience.id));
    }

    auto groups = database->groups();

    for (auto& group: groups) {
        ui->groupComboBox->addItem(QString::number(group.id));
    }

    auto teachers = database->teachers();

    for (auto& teacher: teachers) {
        ui->teacherComboBox->addItem(QString::number(teacher.id));
    }

    auto subjects = database->subjects();

    for (auto& subject: subjects) {
        ui->subjectComboBox->addItem(QString::number(subject.id));
    }

    connect(ui->applyPushButton, SIGNAL(clicked(bool)), model, SLOT(submitAll()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(insertEntry()));
    connect(ui->removePushButton, SIGNAL(clicked(bool)), this, SLOT(removeEntry()));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->show();
}

TimetableEditWidget::~TimetableEditWidget()
{
    delete ui;
}

void TimetableEditWidget::insertEntry() {

    QString semester = ui->semesterSpinBox->text();
    QString day = ui->dayComboBox->currentText();
    QString time = ui->timeComboBox->currentText();
    QString id_audience = ui->audienceComboBox->currentText();
    QString id_group = ui->groupComboBox->currentText();
    QString id_teacher = ui->teacherComboBox->currentText();
    QString id_subject = ui->subjectComboBox->currentText();

    database->insertTimetable(semester, day, time, id_audience,
                         id_group, id_teacher, id_subject);

    model->submitAll();
}

void TimetableEditWidget::removeEntry() {

    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); i++) {
        model->removeRows(selectedList.at(i).row(), 1);
    }

    model->submitAll();
}
