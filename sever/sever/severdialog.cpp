#include "severdialog.h"

SeverDialog::SeverDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	tcp_sever = new QTcpServer(this);
	total_bytes = received_bytes = file_name_size = 0;

	connect(tcp_sever, SIGNAL(newConnection()), this, SLOT(acceptConnection())) ;

	setFixedSize( this->width(),this->height ());
}

SeverDialog::~SeverDialog()
{

}

void SeverDialog::start()
{
	ui.ButtonRecive->setEnabled(false) ;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	received_bytes = 0;

	while(!tcp_sever->isListening() && !tcp_sever->listen(QHostAddress::Any, 16689))
	{
		QMessageBox::StandardButton ret = QMessageBox::critical(this, tr("�ػ�"), 
			tr("�޷���ʼ���ԣ� %1.").arg(tcp_sever->errorString()), 
			QMessageBox::Retry | QMessageBox::Cancel);

		if(ret == QMessageBox::Cancel)
			return ;
	}

	ui.label->setText(tr("���ڼ���"));
}

void SeverDialog::acceptConnection()
{
	//ȡ���׽���
	tcp_sever_connection = tcp_sever->nextPendingConnection() ;
	//�յ���Ϣ����readyRead �ź� 
	connect(tcp_sever_connection, SIGNAL(readyRead()), this, SLOT(updateSeverProgress()));
	//������error�ź�
	connect(tcp_sever_connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));


	ui.label->setText(tr("��������"));
	tcp_sever->close();
}

void SeverDialog::updateSeverProgress()
{
	//in�����׽��֣�ÿд��һ������ tcp_sever_connection��bytesAvailable() ����һ������
	QDataStream in(tcp_sever_connection);
	in.setVersion(QDataStream::Qt_4_3);

	// �����û��д �ܳ��Ⱥ��ļ�������
	if(received_bytes <= sizeof(qint64)*2)
	{
		//д �ܳ��� �� �ļ�������
		if( (tcp_sever_connection->bytesAvailable() >= sizeof(qint64)*2 ) && file_name_size == 0)
		{
			in >> total_bytes >> file_name_size;
			received_bytes += sizeof(qint64)*2 ;
		}

		//received_bytes == sizeof(qint64)*2ʱ  д���ļ���
		if(tcp_sever_connection->bytesAvailable() >= file_name_size && file_name_size != 0)
		{
			in >> file_name;
			received_bytes += file_name_size;
			local_file = new QFile(file_name);

			if(!local_file->open(QFile::WriteOnly))
			{
				QMessageBox::warning(this, tr("Ӧ�ó���"),
					tr("�޷���ȡ�ļ� %1:\n%2.")
					.arg(file_name)
					.arg(local_file->errorString()));
				return ;
			}
		}
		else
			return ;
	}
	
	//д���ļ�����
	if(received_bytes < total_bytes)
	{
		received_bytes += tcp_sever_connection->bytesAvailable();
		in_block = tcp_sever_connection->readAll() ;
		local_file->write(in_block);
		in_block.resize(0);
	}

	//���½�����
	ui.progressBar->setMaximum(total_bytes);
	ui.progressBar->setValue(received_bytes);
	ui.label->setText(tr("%1 %").arg(QString::number(received_bytes / total_bytes *100))) ;

	//�����������
	if(received_bytes == total_bytes)
	{
		tcp_sever_connection->close();
		ui.ButtonRecive->setEnabled(true);
		QApplication::restoreOverrideCursor();
	}

}

void SeverDialog::displayError(QAbstractSocket::SocketError soket_error)
{
	if(soket_error == QTcpSocket::RemoteHostClosedError)
		return ;

	QMessageBox::information(this, tr("�������"),
		tr("�������´���: %1.")
		.arg(tcp_sever_connection->errorString()));

	tcp_sever_connection->close();
	ui.progressBar->reset();
	ui.label->setText(tr("����˾���"));
	ui.ButtonRecive->setEnabled(true);
	QApplication::restoreOverrideCursor();
}


