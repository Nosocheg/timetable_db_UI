#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(Database* database, QWidget *parent = nullptr);
    ~UserWidget();

private:
    Ui::UserWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
    void updateAddPushButton();
};

#endif // USER_WIDGET_H
