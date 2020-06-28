#ifndef SEVERDIALOG_H
#define SEVERDIALOG_H

#include <QtGui/QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include "ui_severdialog.h"

class SeverDialog : public QDialog
{
	Q_OBJECT

public:
	SeverDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SeverDialog();

private:
	Ui::SeverDialogClass ui;

	QTcpServer *tcp_sever;
	QTcpSocket *tcp_sever_connection;
	qint64 total_bytes;
	qint64 received_bytes;
	qint64 file_name_size;
	QString file_name;
	QFile *local_file;
	QByteArray in_block;

	public slots:
		void start();
		void acceptConnection();
		void updateSeverProgress();
		void displayError(QAbstractSocket::SocketError soket_error);
};

#endif // SEVERDIALOG_H
