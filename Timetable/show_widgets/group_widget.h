#ifndef GROUP_WIDGET_H
#define GROUP_WIDGET_H

#include <QWidget>

#include "database.h"
#include "entry_widget.h"

namespace Ui {
class GroupWidget;
}

class GroupWidget : public QWidget, public EntryWidget
{
    Q_OBJECT

public:
    explicit GroupWidget(Database* database, QWidget *parent = nullptr);
    ~GroupWidget();

private:
    Ui::GroupWidget *ui;
    virtual void updateTable();
};

#endif // GROUP_WIDGET_H
