#include "entries.h"

User::User(int id, QString login,
     QString password, UserType role,
     int id_student, int id_teacher,
     QString name_student, QString name_teacher
    )
    : id(id)
    , login(login)
    , password(password)
    , role(role)
    , id_student(id_student)
    , id_teacher(id_teacher)
    , student(name_student)
    , teacher(name_teacher)
{}

UserType roleFromString(QString s) {

    if (s == "Администратор")
        return UserType::Administrator;

    if (s == "Модератор")
        return UserType::Moderator;

    if (s == "Учитель")
        return UserType::Teacher;

    if (s == "Студент")
        return UserType::Student;

    return UserType::Rejected;
}

Student::Student(int id, QString name, QString surname,
        QString second_name, int id_group, QString name_group)
    : id(id)
    , name(name)
    , surname(surname)
    , second_name(second_name)
    , id_group(id_group)
    , name_group(name_group)
{
    full_name = surname + " " + name + " " + second_name;
}

Teacher::Teacher(int id, QString name, QString surname,
        QString second_name, QString position)
    : id(id)
    , name(name)
    , surname(surname)
    , second_name(second_name)
    , position(position)
{
    full_name = surname + " " + name + " " + second_name;
}

Group::Group(int id, QString name)
    : id(id)
    , name(name)
{}

Audience::Audience(int id, int number, QString building)
    : id(id)
    , number(number)
    , building(building)
{}

Subject::Subject(int id, QString name)
    : id(id)
    , name(name)
{}

Timetable::Timetable(int id, int semester,
        QString day, QString time, int id_audience,
        int id_group, int id_teacher,
        int id_subject, QString audience, QString group,
        QString teacher, QString subject)
    : id(id)
    , semester(semester)
    , day(day)
    , time(time)
    , id_audience(id_audience)
    , id_group(id_group)
    , id_teacher(id_teacher)
    , id_subject(id_subject)
    , audience(audience)
    , group(group)
    , teacher(teacher)
    , subject(subject)
{}
