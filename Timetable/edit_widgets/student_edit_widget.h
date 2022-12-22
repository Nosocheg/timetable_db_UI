#ifndef STUDENT_EDIT_WIDGET_H
#define STUDENT_EDIT_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class StudentEditWidget;
}

class StudentEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentEditWidget(Database* database, QWidget *parent = nullptr);
    ~StudentEditWidget();

private:
    Ui::StudentEditWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
    void updateAddPushButton();
};

#endif // STUDENT_EDIT_WIDGET_H
