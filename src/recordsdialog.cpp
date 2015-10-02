#include <QtGui>
#include <QColor>

#include "recordsdialog.h"

RecordsDialog::RecordsDialog(int *rec, QWidget *parent)
        : QDialog(parent)
{
        tableWidget = new QTableWidget(0, 2);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setHorizontalHeaderLabels(
                        QStringList() << tr("Хаос") << tr("По прямій"));

        for (int r = 0; r < 5; ++r) {
                int r1 = rec[r];
                int r2 = rec[r+5];

                // add row
                int row = tableWidget->rowCount();

                tableWidget->insertRow(row);

                QTableWidgetItem *item0 = new QTableWidgetItem;
                QTableWidgetItem *item1 = new QTableWidgetItem;

                item0->setTextAlignment(Qt::AlignCenter);
                item1->setTextAlignment(Qt::AlignCenter);

                tableWidget->setItem(row, 0, item0);
                tableWidget->setItem(row, 1, item1);

                // end add row

                tableWidget->item(r, 0)->setText(QString::number( r1 ));
                tableWidget->item(r, 1)->setText(QString::number( r2 ));
        }

        closeButton = new QPushButton(tr("Добре"));
        connect(closeButton, SIGNAL(clicked()),
                        this, SLOT(close()));

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(tableWidget);
        mainLayout->addWidget(closeButton);
        setLayout(mainLayout);

        setWindowTitle(tr("Кращі результати гри"));
        setFixedSize(242, 250);
}
