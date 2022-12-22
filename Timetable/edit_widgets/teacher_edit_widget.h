#ifndef TEACHER_EDIT_WIDGET_H
#define TEACHER_EDIT_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class TeacherEditWidget;
}

class TeacherEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherEditWidget(Database* database, QWidget *parent = nullptr);
    ~TeacherEditWidget();

private:
    Ui::TeacherEditWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
    void updateAddPushButton();
};

#endif // TEACHER_EDIT_WIDGET_H
