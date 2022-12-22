#ifndef GROUP_EDIT_WIDGET_H
#define GROUP_EDIT_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class GroupEditWidget;
}

class GroupEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupEditWidget(Database* database, QWidget *parent = nullptr);
    ~GroupEditWidget();

private:
    Ui::GroupEditWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
    void updateAddPushButton();
};

#endif // GROUP_EDIT_WIDGET_H
