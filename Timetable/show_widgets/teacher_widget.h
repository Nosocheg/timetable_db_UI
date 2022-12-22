#ifndef TEACHER_WIDGET_H
#define TEACHER_WIDGET_H

#include <QWidget>

#include "database.h"
#include "entry_widget.h"

namespace Ui {
class TeacherWidget;
}

class TeacherWidget : public QWidget, public EntryWidget
{
    Q_OBJECT

public:
    explicit TeacherWidget(Database* database, QWidget *parent = nullptr);
    ~TeacherWidget();

private:
    Ui::TeacherWidget *ui;
    virtual void updateTable();
    virtual void loadVariants();

private slots:
    virtual void filter();
};

#endif // TEACHER_WIDGET_H
