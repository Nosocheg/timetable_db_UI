#ifndef SUBJECT_EDIT_WIDGET_H
#define SUBJECT_EDIT_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class SubjectEditWidget;
}

class SubjectEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectEditWidget(Database* database, QWidget *parent = nullptr);
    ~SubjectEditWidget();

private:
    Ui::SubjectEditWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
    void updateAddPushButton();
};

#endif // SUBJECT_EDIT_WIDGET_H
