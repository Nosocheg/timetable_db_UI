#include "main_window.h"
#include "ui_main_window.h"

#include "login_dialog.h"

#include "show_widgets/audience_widget.h"
#include "show_widgets/teacher_widget.h"
#include "show_widgets/student_widget.h"
#include "show_widgets/group_widget.h"
#include "show_widgets/subject_widget.h"
#include "show_widgets/timetable_widget.h"
#include "edit_widgets/user_widget.h"
#include "edit_widgets/group_edit_widget.h"
#include "edit_widgets/subject_edit_widget.h"
#include "edit_widgets/audience_edit_widget.h"
#include "edit_widgets/teacher_edit_widget.h"
#include "edit_widgets/student_edit_widget.h"
#include "edit_widgets/timetable_edit_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Таблицы");

    ui->label->setScaledContents(true);

    QPixmap pixmap(QPixmap::fromImage(QImage(":/resources/background.png")));
    ui->label->setPixmap(pixmap);

    QFile file(":/resources/coffee.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet = QString::fromLatin1(file.readAll());
    file.close();

    qApp->setStyleSheet(styleSheet);
    qApp->setStyle("Fusion");

    database = new Database(tr("timetable.db"));

    database->createTables();

    connect(ui->timetablesAction, SIGNAL(triggered(bool)), this, SLOT(timetablesTable()));
    connect(ui->studentsAction, SIGNAL(triggered(bool)), this, SLOT(studentsTable()));
    connect(ui->teachersAction, SIGNAL(triggered(bool)), this, SLOT(teachersTable()));
    connect(ui->groupsAction, SIGNAL(triggered(bool)), this, SLOT(groupsTable()));
    connect(ui->audiencesAction, SIGNAL(triggered(bool)), this, SLOT(audiencesTable()));
    connect(ui->subjectsAction, SIGNAL(triggered(bool)), this, SLOT(subjectsTable()));

    QMetaObject::invokeMethod(this, "showLoginDialog", Qt::QueuedConnection);
}

void MainWindow::showLoginDialog() {
    setVisible(false);

    loginDlg = new LoginDialog(database);

    switch (loginDlg->exec()) {
    case QDialog::Accepted:

        userType = loginDlg->type();
        id = loginDlg->id();
        break;

    case QDialog::Rejected:
        // qApp->quit();
        break;
    }

    setVisible(true);

    if (userType == UserType::Moderator || userType == UserType::Administrator)
        createReductionMenu();

    if (userType == UserType::Administrator)
        createUsersMenu();
}

void MainWindow::createReductionMenu() {
    QAction *timetableAction = new QAction("Расписание");
    QAction *studentAction = new QAction("Студенты");
    QAction *teacherAction = new QAction("Преподаватели");
    QAction *groupAction = new QAction("Группы");
    QAction *audienceAction = new QAction("Аудитории");
    QAction *subjectAction = new QAction("Предметы");

    connect(timetableAction, SIGNAL(triggered(bool)), this, SLOT(timetablesReductionTable()));
    connect(studentAction, SIGNAL(triggered(bool)), this, SLOT(studentsReductionTable()));
    connect(teacherAction, SIGNAL(triggered(bool)), this, SLOT(teachersReductionTable()));
    connect(groupAction, SIGNAL(triggered(bool)), this, SLOT(groupsReductionTable()));
    connect(audienceAction, SIGNAL(triggered(bool)), this, SLOT(audiencesReductionTable()));
    connect(subjectAction, SIGNAL(triggered(bool)), this, SLOT(subjectsReductionTable()));

    QMenu* menuReduction = new QMenu("Редактирование", this);

    menuReduction->addAction(timetableAction);
    menuReduction->addAction(studentAction);
    menuReduction->addAction(teacherAction);
    menuReduction->addAction(groupAction);
    menuReduction->addAction(audienceAction);
    menuReduction->addAction(subjectAction);

    ui->menubar->addMenu(menuReduction);
}

void MainWindow::createUsersMenu() {
    QAction *usersAction = new QAction("Пользователи");

    connect(usersAction, SIGNAL(triggered(bool)), this, SLOT(usersTable()));

    QMenu* menuUsers = new QMenu("Администрирование", this);

    menuUsers->addAction(usersAction);

    ui->menubar->addMenu(menuUsers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timetablesTable() {
    TimetableWidget* timetableWidget = new TimetableWidget(database);

    timetableWidget->show();
}

void MainWindow::studentsTable() {
    StudentWidget* studentWidget = new StudentWidget(database);

    studentWidget->show();
}

void MainWindow::teachersTable() {
    TeacherWidget* teacherWidget = new TeacherWidget(database);

    teacherWidget->show();
}

void MainWindow::groupsTable() {
    GroupWidget* groupWidget = new GroupWidget(database);

    groupWidget->show();
}

void MainWindow::audiencesTable() {
    AudienceWidget* audienceWidget = new AudienceWidget(database);

    audienceWidget->show();
}

void MainWindow::subjectsTable() {
    SubjectWidget* subjectWidget = new SubjectWidget(database);

    subjectWidget->show();
}

void MainWindow::usersTable() {
    UserWidget* userWidget = new UserWidget(database);

    userWidget->show();
}

void MainWindow::timetablesReductionTable() {
    TimetableEditWidget* timetableEditWidget = new TimetableEditWidget(database);

    timetableEditWidget->show();
}

void MainWindow::studentsReductionTable() {
    StudentEditWidget* studentEditWidget = new StudentEditWidget(database);

    studentEditWidget->show();
}

void MainWindow::teachersReductionTable() {
    TeacherEditWidget* teacherEditWidget = new TeacherEditWidget(database);

    teacherEditWidget->show();
}

void MainWindow::groupsReductionTable() {
    GroupEditWidget* groupEditWidget = new GroupEditWidget(database);

    groupEditWidget->show();
}

void MainWindow::audiencesReductionTable() {
    AudienceEditWidget* audienceEditWidget = new AudienceEditWidget(database);

    audienceEditWidget->show();
}

void MainWindow::subjectsReductionTable() {
    SubjectEditWidget* subjectEditWidget = new SubjectEditWidget(database);

    subjectEditWidget->show();
}
