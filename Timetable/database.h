#ifndef DATABASE_H
#define DATABASE_H

#include <QtWidgets>
#include <QtSql>

#include "entries.h"

class Database : public QObject
{
    Q_OBJECT
public:
    Database(QString databaseName, QObject *parent = NULL);

    void createTables();

    QList<Student> students();
    QList<Teacher> teachers();
    QList<User> users();
    QList<Audience> audiences();
    QList<Subject> subjects();
    QList<Group> groups();
    QList<Timetable> timetables();

    QPair<UserType, int> checkLoginPassword(QString, QString);

    QList<Audience> filterAudiences(const QList<QString>&, QList<QString>&);
    QList<Teacher> filterTeachers(QList<QString>&);
    QList<Student> filterStudents(QList<QString>&);
    QList<Timetable> filterTimetables(QList<QString>&, QList<QString>&, QList<QString>&,
                                      QList<QString>&, QList<QString>&, QList<QString>&,
                                      QList<QString>&);

    void insertUser(QString login, QString password, QString role, QString id);
    void insertGroup(QString name);
    void insertSubject(QString name);
    void insertAudience(QString number, QString building);
    void insertTeacher(QString surname, QString name, QString second_name, QString position);
    void insertStudent(QString surname, QString name, QString second_name, QString id_group);
    void insertTimetable(QString semester, QString day, QString time, QString id_audience,
                         QString id_group, QString id_teacher, QString id_subject);

    QSqlDatabase table;
private:
    QSqlQuery* mQuery;


    void exec(QString);
    QString qs(QString);
};

#endif // DATABASE_H
