#ifndef ENTRIES_H
#define ENTRIES_H

#include <QString>

enum class UserType {
    Rejected,
    Administrator,
    Moderator,
    Teacher,
    Student
};

UserType roleFromString(QString s);

struct User {
    int id;
    QString login;
    QString password;
    UserType role;
    int id_student;
    int id_teacher;
    QString student;
    QString teacher;


    User(int id = 0, QString login = "",
         QString password = "", UserType role = UserType::Rejected, int id_student = 0,
         int id_teacher = 0, QString name_student = "",
         QString name_teacher = "");
};

struct Student {

    int id;
    QString name;
    QString surname;
    QString second_name;
    int id_group;
    QString name_group;
    QString full_name;

    Student(
            int id = 0,
            QString name = "",
            QString surname = "",
            QString second_name = "",
            int id_group = 0,
            QString name_group = ""
            );
};

struct Teacher {

    int id;
    QString name;
    QString surname;
    QString second_name;
    QString position;
    QString full_name;

    Teacher(
            int id = 0,
            QString name = "",
            QString surname = "",
            QString second_name = "",
            QString position = ""
            );
};

struct Group {

    int id;
    QString name;

    Group(int id = 0, QString name = "");
};

struct Audience {

    int id;
    int number;
    QString building;

    Audience(int id = 0, int number = 0, QString building = "");
};

struct Subject {

    int id;
    QString name;

    Subject(int id = 0, QString name = "");
};

struct Timetable {

    int id;
    int semester;
    QString day;
    QString time;
    int id_audience;
    int id_group;
    int id_teacher;
    int id_subject;

    QString audience;
    QString group;
    QString teacher;
    QString subject;

    Timetable(
            int id = 0,
            int semester = 0,
            QString day = "",
            QString time = "",
            int id_audience = 0,
            int id_group = 0,
            int id_teacher = 0,
            int id_subject = 0,
            QString audience = "",
            QString group = "",
            QString teacher = "",
            QString subject = ""
            );
};

#endif // ENTRIES_H
