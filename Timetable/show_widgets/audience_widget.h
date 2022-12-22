#ifndef AUDIENCE_WIDGET_H
#define AUDIENCE_WIDGET_H

#include <QWidget>

#include "database.h"
#include "entry_widget.h"

namespace Ui {
class AudienceWidget;
}

class AudienceWidget : public QWidget, public EntryWidget
{
    Q_OBJECT

public:
    explicit AudienceWidget(Database* database, QWidget *parent = nullptr);
    ~AudienceWidget();

private:
    Ui::AudienceWidget *ui;
    virtual void updateTable();
    virtual void loadVariants();

private slots:
    virtual void filter();
};

#endif // AUDIENCE_WIDGET_H
