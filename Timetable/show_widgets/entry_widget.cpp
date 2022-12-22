#include "entry_widget.h"

EntryWidget::EntryWidget(Database* database)
    : database(database)
{}

void EntryWidget::setHeaders(QTableWidget* tableWidget) {
    tableWidget->resizeColumnsToContents();
    tableWidget->verticalHeader()->hide();

    auto header = tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setHorizontalHeader(header);
}

QList<QString> EntryWidget::checkedItems(QComboBox* box) {
    QList<QString> items;

    QStandardItemModel* model = (QStandardItemModel*)box->model();

    for (int i = 0; i < model->rowCount(); i++) {
        auto item = model->item(i);
        if (item->checkState() == Qt::Checked)
            items.append(item->text());
    }

    return items;
}

void EntryWidget::createModel(const QList<QString>& list, QComboBox* box) {
    QStandardItemModel *model = new QStandardItemModel(list.size(), 1);

    for (int i = 0; i < list.size(); i++) {
        QStandardItem* item = new QStandardItem(list[i]);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        model->setItem(i, 0, item);
    }
    box->setModel(model);
}
