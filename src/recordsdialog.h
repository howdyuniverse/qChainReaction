#ifndef RECORDSDIALOG_H
#define RECORDSDIALOG_H

#include <QDialog>

class QTableWidget;

class RecordsDialog : public QDialog
{
		Q_OBJECT

public:
		RecordsDialog(int *rec, QWidget *parent = 0);

private:
		QTableWidget *tableWidget;
		QPushButton *closeButton;
};

#endif
