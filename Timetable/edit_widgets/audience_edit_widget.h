#ifndef AUDIENCE_EDIT_WIDGET_H
#define AUDIENCE_EDIT_WIDGET_H

#include <QWidget>

#include "database.h"

namespace Ui {
class AudienceEditWidget;
}

class AudienceEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudienceEditWidget(Database* database, QWidget *parent = nullptr);
    ~AudienceEditWidget();

private:
    Ui::AudienceEditWidget *ui;
    QSqlTableModel* model;
    Database* database;
private slots:
    void insertEntry();
    void removeEntry();
    void updateAddPushButton();
};

#endif // AUDIENCE_EDIT_WIDGET_H
