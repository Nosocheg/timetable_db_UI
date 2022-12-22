#ifndef STUDENT_WIDGET_H
#define STUDENT_WIDGET_H

#include <QWidget>

#include "database.h"
#include "entry_widget.h"

namespace Ui {
class StudentWidget;
}

class StudentWidget : public QWidget, public EntryWidget
{
    Q_OBJECT

public:
    explicit StudentWidget(Database* database, QWidget *parent = nullptr);
    ~StudentWidget();

private:
    Ui::StudentWidget *ui;
    virtual void updateTable();
    virtual void loadVariants();

private slots:
    virtual void filter();
};

#endif // STUDENT_WIDGET_H
