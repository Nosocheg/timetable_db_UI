#ifndef SUBJECT_WIDGET_H
#define SUBJECT_WIDGET_H

#include <QWidget>

#include "database.h"
#include "entry_widget.h"

namespace Ui {
class SubjectWidget;
}

class SubjectWidget : public QWidget, public EntryWidget
{
    Q_OBJECT

public:
    explicit SubjectWidget(Database* database, QWidget *parent = nullptr);
    ~SubjectWidget();

private:
    Ui::SubjectWidget *ui;
    virtual void updateTable();
};

#include <QWidget>

#endif // SUBJECT_WIDGET_H
