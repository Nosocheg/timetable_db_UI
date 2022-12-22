#ifndef TIMETABLE_WIDGET_H
#define TIMETABLE_WIDGET_H

#include <QWidget>

#include "database.h"
#include "entry_widget.h"

namespace Ui {
class TimetableWidget;
}

class TimetableWidget : public QWidget, public EntryWidget
{
    Q_OBJECT

public:
    explicit TimetableWidget(Database* database, QWidget *parent = nullptr);
    ~TimetableWidget();

private:
    Ui::TimetableWidget *ui;
    virtual void updateTable();
    virtual void loadVariants();

private slots:
    virtual void filter();
};

#endif // TIMETABLE_WIDGET_H
