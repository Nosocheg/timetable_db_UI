#include "database.h"

Database::Database(QString databaseName, QObject *parent)
    : QObject(parent) {

    table = QSqlDatabase::addDatabase("QMYSQL", databaseName);
    table.setDatabaseName(databaseName);

    table.setHostName("DESKTOP-B31JHI0");
    table.setDatabaseName("timetable_db");
    table.setUserName("Nosocheg");
    table.setPassword("s3291639");

    if (!table.open()){
        qDebug() << table.lastError();
        return;
    }
    mQuery = new QSqlQuery(table);
}

QString Database::qs(QString str) {
    return "'" + str + "'";
}

void Database::exec(QString str) {
    if (!mQuery->exec(str))
        return;
}

void Database::createTables() {
//   return;
//    exec("DROP TABLE groups");
//    exec("DROP TABLE students");
//    exec("DROP TABLE audiences");
//    exec("DROP TABLE teachers");
//    exec("DROP TABLE subjects");
//    exec("DROP TABLE users");
//    exec("DROP TABLE timetables");

    if (!table.tables().contains("users")) {
      exec("CREATE TABLE users"
           "("
              "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
              "login TEXT NOT NULL, "
              "password TEXT NOT NULL, "
              "user_role TEXT NOT NULL, "
              "id_student INTEGER, "
              "id_teacher INTEGER"
           ");"
      );
    }

    if (!table.tables().contains("students")) {
      exec("CREATE TABLE students"
           "("
               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
               "surname TEXT NOT NULL, "
               "name TEXT NOT NULL, "
               "second_name TEXT NOT NULL, "
               "id_group INTEGER NOT NULL"
          ");"
      );
    }

    if (!table.tables().contains("groups")) {
      exec("CREATE TABLE groups"
           "("
               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
               "name TEXT NOT NULL"
          ");"
      );
    }

    if (!table.tables().contains("teachers")) {
      exec("CREATE TABLE teachers"
           "("
               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
               "surname TEXT NOT NULL, "
               "name TEXT NOT NULL, "
               "second_name TEXT NOT NULL, "
               "position TEXT NOT NULL"
          ");"
      );
    }

    if (!table.tables().contains("timetables")) {
      exec("CREATE TABLE timetables"
           "("
               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
               "semester INTEGER NOT NULL, "
               "day TEXT NOT NULL, "
               "time TEXT NOT NULL, "
               "id_audience INTEGER NOT NULL, "
               "id_group INTEGER NOT NULL, "
               "id_teacher INTEGER NOT NULL, "
               "id_subject INTEGER NOT NULL"
          ");"
      );
    }

    if (!table.tables().contains("audiences")) {
      exec("CREATE TABLE audiences"
           "("
               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
               "number INTEGER NOT NULL, "
               "building TEXT NOT NULL"
          ");"
      );
    }

    if (!table.tables().contains("subjects")) {
      exec("CREATE TABLE subjects"
           "("
               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
               "name TEXT NOT NULL"
          ");"
      );
    }
    exec("INSERT INTO users (login, password, user_role, id_student, id_teacher) "
         "VALUES ('1', '1', 'Администратор', 1, 1)");
/*
    exec("DELETE FROM audiences");

    exec("INSERT INTO audiences (number, building) "
         "VALUES (1, 'Corpus 1')");
    exec("INSERT INTO audiences (number, building) "
         "VALUES (2, 'Corpus 1')");
    exec("INSERT INTO audiences (number, building) "
         "VALUES (1, 'Corpus 2')");
    exec("INSERT INTO audiences (number, building) "
         "VALUES (2, 'Corpus 2')");

    exec("DELETE FROM teachers");

    exec("INSERT INTO teachers (surname, name, second_name, position) "
         "VALUES ('Ivanov', 'Ivan', 'Ivanovich', 'Math teacher')");
    exec("INSERT INTO teachers (surname, name, second_name, position) "
         "VALUES ('Petrov', 'Petr', 'Petrovich', 'Math teacher')");
    exec("INSERT INTO teachers (surname, name, second_name, position) "
         "VALUES ('Alexeev', 'Alexey', 'Alexeevich', 'Computer Science teacher')");

    exec("DELETE FROM students");

    exec("INSERT INTO students (surname, name, second_name, id_group) "
         "VALUES ('Ivanov', 'Ivan', 'Ivanovich', 1)");
    exec("INSERT INTO students (surname, name, second_name, id_group) "
         "VALUES ('Petrov', 'Petr', 'Petrovich', 1)");
    exec("INSERT INTO students (surname, name, second_name, id_group) "
         "VALUES ('Alexeev', 'Alexey', 'Alexeevich', 2)");

    exec("DELETE FROM groups");

    exec("INSERT INTO groups (name) "
         "VALUES ('A-017')");
    exec("INSERT INTO groups (name) "
         "VALUES ('A-015')");

    exec("INSERT INTO subjects (name) "
         "VALUES ('Computer Science')");
    exec("INSERT INTO subjects (name) "
         "VALUES ('Math')");

    exec("DELETE FROM timetables");

    exec("INSERT INTO timetables (semester, day, time, id_audience, id_group, id_teacher, id_subject) "
         "VALUES (2, 'Monday', '12:30', 1, 2, 1, 2)");
    exec("INSERT INTO timetables (semester, day, time, id_audience, id_group, id_teacher, id_subject) "
         "VALUES (2, 'Monday', '14:10', 2, 2, 1, 2)");
    exec("INSERT INTO timetables (semester, day, time, id_audience, id_group, id_teacher, id_subject) "
         "VALUES (1, 'Wednesday', '15:50', 2, 2, 1, 1)");

    exec("INSERT INTO users (login, password, user_role, id_student, id_teacher) "
         "VALUES ('1', '1', 'Администратор', 1, 1)");
    exec("INSERT INTO users (login, password, user_role, id_student, id_teacher) "
         "VALUES ('2', '2', 'Модератор', 1, 1)");
    exec("INSERT INTO users (login, password, user_role, id_student, id_teacher) "
         "VALUES ('3', '3', 'Студент', 1, 1)");
         */
}

QList<Student> Database::students() {
    QList<Student> students;

    QString query = tr("SELECT id, surname, name, second_name, id_group FROM students ");
    exec(query);

    while (mQuery->next()) {
        Student student;
        student.id = mQuery->value(0).toInt();
        student.surname = mQuery->value(1).toString();
        student.name = mQuery->value(2).toString();
        student.second_name = mQuery->value(3).toString();

        student.full_name = student.surname + " " + student.name + " " + student.second_name;

        student.id_group = mQuery->value(4).toInt();

        students.push_back(student);
    }

    for (Student& student : students) {

        exec(tr("SELECT name FROM groups WHERE id = ")
             + QString::number(student.id_group));

        mQuery->next();

        student.name_group = mQuery->value(0).toString();
    }

    return students;
}

QList<Teacher> Database::teachers() {
    QList<Teacher> teachers;

    QString query = tr("SELECT id, surname, name, second_name, position FROM teachers ");
    exec(query);

    while (mQuery->next()) {
        Teacher teacher;
        teacher.id = mQuery->value(0).toInt();
        teacher.surname = mQuery->value(1).toString();
        teacher.name = mQuery->value(2).toString();
        teacher.second_name = mQuery->value(3).toString();
        teacher.full_name = teacher.surname + " " + teacher.name + " " + teacher.second_name;
        teacher.position = mQuery->value(4).toString();

        teachers.push_back(teacher);
    }

    return teachers;
}

QList<User> Database::users() {
    QList<User> users;

    QString query = tr("SELECT id, login, password, user_role, id_student, id_teacher FROM users ");
    exec(query);

    while (mQuery->next()) {
        User user;
        user.id = mQuery->value(0).toInt();
        user.login = mQuery->value(1).toString();
        user.password = mQuery->value(2).toString();
        user.role = roleFromString(mQuery->value(3).toString());
        user.id_student = mQuery->value(4).toInt();
        user.id_teacher = mQuery->value(5).toInt();

        exec(tr("SELECT surname, name, second_name FROM students WHERE id = ")
             + qs(QString::number(user.id_student)));

        mQuery->next();

        user.student = mQuery->value(0).toString();
        user.student += ' ' + mQuery->value(1).toString();
        user.student += ' ' + mQuery->value(2).toString();


        exec(tr("SELECT surname, name, second_name FROM teachers WHERE id = ")
             + qs(QString::number(user.id_teacher)));

        mQuery->next();

        user.teacher = mQuery->value(0).toString();
        user.teacher += ' ' + mQuery->value(1).toString();
        user.teacher += ' ' + mQuery->value(2).toString();

        users.push_back(user);
    }

    return users;
}

QList<Audience> Database::audiences() {
    QList<Audience> audiences;

    QString query = tr("SELECT id, number, building FROM audiences ");
    exec(query);

    while (mQuery->next()) {
        Audience audience;
        audience.id = mQuery->value(0).toInt();
        audience.number = mQuery->value(1).toInt();
        audience.building = mQuery->value(2).toString();

        audiences.push_back(audience);
    }

    return audiences;
}

QList<Subject> Database::subjects() {
    QList<Subject> subjects;

    QString query = tr("SELECT id, name FROM subjects ");
    exec(query);

    while (mQuery->next()) {
        Subject subject;
        subject.id = mQuery->value(0).toInt();
        subject.name = mQuery->value(1).toString();

        subjects.push_back(subject);
    }

    return subjects;
}

QList<Group> Database::groups() {
    QList<Group> groups;

    QString query = tr("SELECT id, name FROM groups ");
    exec(query);

    while (mQuery->next()) {
        Group group;
        group.id = mQuery->value(0).toInt();
        group.name = mQuery->value(1).toString();

        groups.push_back(group);
    }

    return groups;
}

QList<Timetable> Database::timetables() {

    QString query = tr("SELECT id, semester, day, time, id_audience, id_group, id_teacher, id_subject FROM timetables ");
    exec(query);

    QList<Timetable> timetables;

    while (mQuery->next()) {
        Timetable timetable;
        timetable.id = mQuery->value(0).toInt();
        timetable.semester = mQuery->value(1).toInt();
        timetable.day = mQuery->value(2).toString();
        timetable.time = mQuery->value(3).toString();
        timetable.id_audience = mQuery->value(4).toInt();
        timetable.id_group = mQuery->value(5).toInt();
        timetable.id_teacher = mQuery->value(6).toInt();
        timetable.id_subject = mQuery->value(7).toInt();

        timetables.push_back(timetable);
    }

    for (auto& timetable: timetables) {

        exec(tr("SELECT number, building FROM audiences WHERE id = ")
             + QString::number(timetable.id_audience));

        mQuery->next();

        timetable.audience = QString::number(mQuery->value(0).toInt()) + ", " +
                mQuery->value(1).toString();

        exec(tr("SELECT name FROM groups WHERE id = ")
             + QString::number(timetable.id_group));

        mQuery->next();

        timetable.group = mQuery->value(0).toString();

        exec(tr("SELECT name FROM subjects WHERE id = ")
             + QString::number(timetable.id_subject));

        mQuery->next();

        timetable.subject = mQuery->value(0).toString();

        exec(tr("SELECT surname, name, second_name FROM teachers WHERE id = ")
             + QString::number(timetable.id_teacher));

        mQuery->next();

        timetable.teacher = mQuery->value(0).toString();
        timetable.teacher += ' ' + mQuery->value(1).toString();
        timetable.teacher += ' ' + mQuery->value(2).toString();

    }

    return timetables;
}

QPair<UserType, int> Database::checkLoginPassword(QString login, QString password) {

    exec(tr("SELECT id_student, id_teacher, user_role FROM users WHERE login = ")
         + qs(login) + " AND password = " + qs(password));

    if (mQuery->next()) {
        int id_student = mQuery->value(0).toInt();
        int id_teacher = mQuery->value(1).toInt();
        UserType role = roleFromString(mQuery->value(2).toString());

        if (id_student != -1)
            return {role, id_student};
        else if (id_teacher != -1)
            return {role, id_teacher};
        return {role, 0};

    } else {
        return {UserType::Rejected, 0};
    }
}


QList<Audience> Database::filterAudiences(const QList<QString>& numbers, QList<QString>& buildings) {

    for (auto& building : buildings) {
        building = qs(building);
    }

    QString query = tr("SELECT id, number, building "
                       "FROM audiences "
                       "WHERE ");

    query += "(number in (" + numbers.join(", ") + "))";
    query += " AND ";
    query += "(building in (" + buildings.join(", ") + "))";

    exec(query);

    QList<Audience> audiences;

    while (mQuery->next()) {
        Audience audience;
        audience.id = mQuery->value(0).toInt();
        audience.number = mQuery->value(1).toInt();
        audience.building = mQuery->value(2).toString();

        audiences.push_back(audience);
    }

    return audiences;
}

QList<Teacher> Database::filterTeachers(QList<QString>& positions) {

    for (auto& position : positions) {
        position = qs(position);
    }

    QString query = tr("SELECT surname, name, second_name, position "
                       "FROM teachers "
                       "WHERE ");

    query += "(position in (" + positions.join(", ") + "))";

    exec(query);

    QList<Teacher> teachers;

    while (mQuery->next()) {
        Teacher teacher;
        teacher.surname = mQuery->value(0).toString();
        teacher.name = mQuery->value(1).toString();
        teacher.second_name = mQuery->value(2).toString();
        teacher.position = mQuery->value(3).toString();
        teacher.full_name = teacher.surname + " " + teacher.name + " " + teacher.second_name;

        teachers.push_back(teacher);
    }

    return teachers;
}

QList<Student> Database::filterStudents(QList<QString>& groups) {

    QMap<QString, QString> group_id;
    for (auto& group : groups) {

        QString query = tr("SELECT id FROM groups WHERE name = ") + qs(group);
        exec(query);

        mQuery->next();

        auto id = QString::number(mQuery->value(0).toInt());

        group_id[id] = group;
        group = id;
    }

    QString query = tr("SELECT surname, name, second_name, id_group "
                       "FROM students "
                       "WHERE ");

    query += "(id_group in (" + groups.join(", ") + "))";

    exec(query);

    QList<Student> students;

    while (mQuery->next()) {
        Student student;
        student.surname = mQuery->value(0).toString();
        student.name = mQuery->value(1).toString();
        student.second_name = mQuery->value(2).toString();
        student.name_group = group_id[mQuery->value(3).toString()];
        student.full_name = student.surname + " " + student.name + " " + student.second_name;

        students.push_back(student);
    }

    return students;
}

QList<Timetable> Database::filterTimetables(QList<QString>& semesters, QList<QString>& days, QList<QString>& times,
                                  QList<QString>& groups, QList<QString>& audiences, QList<QString>& teachers,
                                  QList<QString>& subjects) {

    for (auto& day: days)
        day = qs(day);

    for (auto& time: times)
        time = qs(time);

    QMap<QString, QString> group_id;
    for (auto& group : groups) {
        QString query = tr("SELECT id FROM groups WHERE name = ") + qs(group);
        exec(query);
        mQuery->next();
        auto id = QString::number(mQuery->value(0).toInt());
        group_id[id] = group;
        group = id;
    }

    QMap<QString, QString> subject_id;
    for (auto& subject : subjects) {
        QString query = tr("SELECT id FROM subjects WHERE name = ") + qs(subject);
        exec(query);
        mQuery->next();
        auto id = QString::number(mQuery->value(0).toInt());
        subject_id[id] = subject;
        subject = id;
    }

    QMap<QString, QString> audience_id;
    for (auto& audience : audiences) {
        auto list = audience.split(", ");
        QString number = list[0];
        QString building = list[1];
        QString query = tr("SELECT id FROM audiences WHERE number = ") + qs(number)
                + " AND building = " + qs(building);

        exec(query);
        mQuery->next();
        auto id = QString::number(mQuery->value(0).toInt());
        audience_id[id] = audience;
        audience = id;
    }

    QMap<QString, QString> teacher_id;
    for (auto& teacher : teachers) {
        auto list = teacher.split(" ");
        QString surname = list[0];
        QString name = list[1];
        QString second_name = list[2];
        QString query = tr("SELECT id FROM teachers WHERE surname = ") + qs(surname)
                + " AND name = " + qs(name)
                + " AND second_name = " + qs(second_name);

        exec(query);
        mQuery->next();
        auto id = QString::number(mQuery->value(0).toInt());
        teacher_id[id] = teacher;
        teacher = id;
    }

    QString query = tr("SELECT semester, day, time, id_audience, id_group, id_teacher, id_subject "
                       "FROM timetables "
                       "WHERE ");

    query += "(semester in (" + semesters.join(", ") + ")) AND";
    query += "(day in (" + days.join(", ") + ")) AND";
    query += "(time in (" + times.join(", ") + ")) AND";
    query += "(id_audience in (" + audiences.join(", ") + ")) AND";
    query += "(id_group in (" + groups.join(", ") + ")) AND";
    query += "(id_teacher in (" + teachers.join(", ") + ")) AND";
    query += "(id_subject in (" + subjects.join(", ") + "))";

    exec(query);

    QList<Timetable> timetables;

    while (mQuery->next()) {
        Timetable timetable;
        timetable.semester = mQuery->value(0).toInt();
        timetable.day = mQuery->value(1).toString();
        timetable.time = mQuery->value(2).toString();
        timetable.audience = audience_id[mQuery->value(3).toString()];
        timetable.group = group_id[mQuery->value(4).toString()];
        timetable.teacher = teacher_id[mQuery->value(5).toString()];
        timetable.subject = subject_id[mQuery->value(6).toString()];

        timetables.push_back(timetable);
    }

    return timetables;
}

void Database::insertUser(QString login, QString password, QString role, QString id) {

    QString query = "INSERT INTO users (login, password, user_role, id_student, id_teacher) "
            "VALUES (" + qs(login) + ", " + qs(password) + ", " + qs(role) + ", ";

    if (role == "Студент")
        query += id + ", ";
    else
        query += "-1, ";

    if (role == "Преподаватель")
        query += id + ")";
    else
        query += "-1)";

    exec(query);
}

void Database::insertGroup(QString name) {
    QString query = "INSERT INTO groups (name) "
            "VALUES (" + qs(name) + ")";

    exec(query);
}

void Database::insertSubject(QString name) {
    QString query = "INSERT INTO subjects (name) "
            "VALUES (" + qs(name) + ")";

    exec(query);
}

void Database::insertAudience(QString number, QString building) {

    QString query = "INSERT INTO audiences (number, building) "
            "VALUES (" + number + ", " + qs(building) + ")";

    exec(query);
}

void Database::insertTeacher(QString surname, QString name, QString second_name, QString position) {

    QString query = "INSERT INTO teachers (surname, name, second_name, position) "
            "VALUES (" + qs(surname) + ", " + qs(name)
                + ", " + qs(second_name) + ", " + qs(position) + ")";

    exec(query);
}

void Database::insertStudent(QString surname, QString name,
                             QString second_name, QString id_group) {

    QString query = "INSERT INTO students (surname, name, second_name, id_group) "
            "VALUES (" + qs(surname) + ", " + qs(name)
                + ", " + qs(second_name) + ", " + id_group + ")";

    exec(query);
}

void Database::insertTimetable(QString semester, QString day, QString time, QString id_audience,
                               QString id_group, QString id_teacher, QString id_subject) {

    QString query = "INSERT INTO timetables (semester, day, time, id_audience, id_group, id_teacher, id_subject) "
            "VALUES (" + semester + ", " + qs(day)
                + ", " + qs(time) + ", " + id_audience
                + ", " + id_group + ", " + id_teacher + ", " + id_subject + ")";

    exec(query);
}

