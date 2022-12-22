#include "timetable_widget.h"
#include "ui_timetable_widget.h"

TimetableWidget::TimetableWidget(Database* database, QWidget *parent)
    : QWidget(parent)
    , EntryWidget(database)
    , ui(new Ui::TimetableWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                << "Семестр" << "День" << "Пара"
                << "Аудитория" << "Группа"
                << "Преподаватель" << "Предмет"
                );

    setWindowTitle("Расписание");

    TimetableWidget::updateTable();
    TimetableWidget::loadVariants();

    setHeaders(ui->tableWidget);

    connect(ui->filterPushButton, SIGNAL(clicked(bool)), this, SLOT(filter()));
}

void TimetableWidget::loadVariants() {
    auto timetables = database->timetables();

    QSet<QString> groups, audiences, subjects, teachers,
            days, times, semesters;


    for (int i = 0; i < timetables.size(); ++i) {

        QString day = timetables[i].day;
        days.insert(day);

        QString time = timetables[i].time;
        times.insert(time);

        QString semester = QString::number(timetables[i].semester);
        semesters.insert(semester);

        QString group = timetables[i].group;
        groups.insert(group);

        QString audience = timetables[i].audience;
        audiences.insert(audience);

        QString subject = timetables[i].subject;
        subjects.insert(subject);

        QString teacher = timetables[i].teacher;
        teachers.insert(teacher);
    }

    QList<QString> sortedGroups(groups.begin(), groups.end()),
        sortedAudiences(audiences.begin(), audiences.end()),
        sortedDays(days.begin(), days.end()),
        sortedTimes(times.begin(), times.end()),
        sortedSemesters(semesters.begin(), semesters.end()),
        sortedSubjects(subjects.begin(), subjects.end()),
        sortedTeachers(teachers.begin(), teachers.end());

    sortedGroups.sort();
    sortedAudiences.sort();
    sortedDays.sort();
    sortedTimes.sort();
    sortedSemesters.sort();
    sortedSubjects.sort();
    sortedTeachers.sort();

    createModel(sortedGroups, ui->groupComboBox);
    createModel(sortedAudiences, ui->audienceComboBox);
    createModel(sortedDays, ui->dayComboBox);
    createModel(sortedTimes, ui->timeComboBox);
    createModel(sortedSemesters, ui->semesterComboBox);
    createModel(sortedSubjects, ui->subjectComboBox);
    createModel(sortedTeachers, ui->teacherComboBox);
}

void TimetableWidget::updateTable() {
    auto timetables = database->timetables();

    for (auto& timetable : timetables) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(timetable.semester)));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(timetable.day));
        ui->tableWidget->setItem(index, 2, new QTableWidgetItem(timetable.time));
        ui->tableWidget->setItem(index, 3, new QTableWidgetItem(timetable.audience));
        ui->tableWidget->setItem(index, 4, new QTableWidgetItem(timetable.group));
        ui->tableWidget->setItem(index, 5, new QTableWidgetItem(timetable.teacher));
        ui->tableWidget->setItem(index, 6, new QTableWidgetItem(timetable.subject));
    }
}

void TimetableWidget::filter() {

    QList<QString> groups = checkedItems(ui->groupComboBox);
    QList<QString> audiences = checkedItems(ui->audienceComboBox);
    QList<QString> subjects = checkedItems(ui->subjectComboBox);
    QList<QString> teachers = checkedItems(ui->teacherComboBox);
    QList<QString> days = checkedItems(ui->dayComboBox);
    QList<QString> times = checkedItems(ui->timeComboBox);
    QList<QString> semesters = checkedItems(ui->semesterComboBox);

    if (groups.isEmpty() || audiences.isEmpty() || subjects.isEmpty() || teachers.isEmpty() ||
            days.isEmpty() || times.isEmpty() || semesters.isEmpty())
        return;

    auto timetables = database->filterTimetables(semesters, days, times, groups, audiences, teachers, subjects);

    ui->tableWidget->setRowCount(0);

    for (auto& timetable : timetables) {
        int index = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(timetable.semester)));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(timetable.day));
        ui->tableWidget->setItem(index, 2, new QTableWidgetItem(timetable.time));
        ui->tableWidget->setItem(index, 3, new QTableWidgetItem(timetable.audience));
        ui->tableWidget->setItem(index, 4, new QTableWidgetItem(timetable.group));
        ui->tableWidget->setItem(index, 5, new QTableWidgetItem(timetable.teacher));
        ui->tableWidget->setItem(index, 6, new QTableWidgetItem(timetable.subject));
    }
}

TimetableWidget::~TimetableWidget()
{
    delete ui;
}
