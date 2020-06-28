#include "client.h"

Client::Client(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	QTextCodec::setCodecForTr( QTextCodec::codecForName("gb2312"));

	connect(&tcp_socket, SIGNAL(connected()), this, SLOT(startTransfer())) ;
	connect(&tcp_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(updataProgress(qint64))) ;
	connect(&tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError socketError)));

	total_btyes = bytes_written = bytes_to_write = 0;
	load_size = 4 * 1024; //����ÿ�η���4KB��С
	ui.pushButtonSend->setEnabled(false);
}

Client::~Client()
{

}

void Client::start()
{
	ui.pushButtonSend->setEnabled(false);
	QApplication::setOverrideCursor(Qt::WaitCursor) ;
	bytes_written = 0;
	ui.label->setText(tr("������"));
	tcp_socket.connectToHost(QHostAddress::LocalHost, 16689);
}

void Client::startTransfer()
{
	local_file = new QFile(file_name);

	if (!local_file->open(QFile::ReadOnly )) 
	{
		QMessageBox::warning(this, tr("Ӧ�ó���"),
			tr("�޷���ȡ�ļ� %1:\n%2.")
			.arg(file_name)
			.arg(local_file->errorString()));
		return;
	}

	//���������ļ��Ĵ�С�ݴ���total_btyes��
	total_btyes = local_file->size();
	QDataStream out(&out_block, QIODevice::WriteOnly) ;
	out.setVersion(QDataStream::Qt_4_3) ;

	//��һ��Ŀ���ǻ�ȡ�ļ����Ĵ�С������ͨ��currrent_file.size()������ȡ���������ļ�����д��
	QString currrent_file = file_name.right(file_name.size() - file_name.lastIndexOf('/') -1) ;
	out << qint64(0) << qint64(0) << currrent_file;
	total_btyes += out_block.size();

	//��ͷ��ʼ����д
	out.device()->seek(0);
	//д���ܳ��Ⱥ��ļ������� (�ļ����Ѿ���ǰ�汻д��ȥ�ˣ�
	out << total_btyes << qint64((out_block.size()-sizeof(qint64)*2)) ;
	ui.progressBar->setMaximum(total_btyes) ;

	//����Э���ļ�ͷ
	bytes_to_write = total_btyes - tcp_socket.write(out_block);

	ui.label->setText(tr("������")) ;

	out_block.resize(0);
}

void Client::updataProgress(qint64 num_bytes)
{
	bytes_written += (int)num_bytes;

	if(bytes_to_write > 0)
	{
		//����ÿ�η���4kb��load_size)
		out_block = local_file->read(qMin(bytes_to_write, load_size));
		bytes_to_write -= (int)tcp_socket.write(out_block);
		out_block.resize(0) ;
	}
	else
	{
		local_file->close();
		QApplication::restoreOverrideCursor();
	}

	ui.progressBar->setValue(bytes_written);
	ui.label->setText(tr("�ѷ��� %1MB").arg(bytes_written / (1024 * 1024)));
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QTcpSocket::RemoteHostClosedError)
		return;

	QMessageBox::information(this, tr("����"),
		tr("�������´���: %1.")
		.arg(tcp_socket.errorString()));

	tcp_socket.close();
	ui.progressBar->reset();
	ui.label->setText(tr("�ͻ��˾���"));
	ui.pushButtonSend->setEnabled(true);
	QApplication::restoreOverrideCursor();
}

void Client::openFile()
{
	file_name = QFileDialog::getOpenFileName(this);
	if(!file_name.isEmpty())
		ui.pushButtonSend->setEnabled(true);
}

