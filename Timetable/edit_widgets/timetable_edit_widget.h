#ifndef TIMETABLE_EDIT_WIDGET_H
#define TIMETABLE_EDIT_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class TimetableEditWidget;
}

class TimetableEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimetableEditWidget(Database* database, QWidget *parent = nullptr);
    ~TimetableEditWidget();

private:
    Ui::TimetableEditWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
};

#endif // TIMETABLE_EDIT_WIDGET_H
