#ifndef ENTRYWIDGET_H
#define ENTRYWIDGET_H

#include "database.h"

class EntryWidget {
public:
    EntryWidget(Database* database);

protected:
    Database* database;
    virtual void updateTable() = 0;

    QList<QString> checkedItems(QComboBox*);

    void createModel(const QList<QString>&, QComboBox*);

    void setHeaders(QTableWidget*);
};

#endif // ENTRYWIDGET_H
