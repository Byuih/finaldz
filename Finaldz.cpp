#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

class ServerWindow : public QWidget
{
	Q_OBJECT

public:
	ServerWindow(QWidget* parent = nullptr) : QWidget(parent)
	{
		// �������� ��������
		messagesView = new QTextEdit(this);
		usersView = new QListView(this);
		userListModel = new QStandardItemModel(this);
		disconnectButton = new QPushButton("���������", this);
		banButton = new QPushButton("��������", this);

		// ��������� ������
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(messagesView);
		layout->addWidget(usersView);
		layout->addWidget(disconnectButton);
		layout->addWidget(banButton);
		setLayout(layout);

		// ��������� ������ ������ �������������
		usersView->setModel(userListModel);

		// ����������� �������� � ������
		connect(disconnectButton, &QPushButton::clicked, this, &ServerWindow::onDisconnectButtonClicked);
		connect(banButton, &QPushButton::clicked, this, &ServerWindow::onBanButtonClicked);
	}

public slots:
	// ���� ��� ���������� ��������� � ������ � �����������
	void addMessage(const QString& message)
	{
		messagesView->append(message);
	}

	// ���� ��� ���������� ������ �������������
	void updateUserList(const QStringList& users)
	{
		userListModel->clear();
		for (const QString& user : users) {
			QListWidgetItem* item = new QListWidgetItem(user, userListModel);
			userListModel->appendRow(item);
		}
	}

private slots:
	// ���� ��� ��������� ������� �� ������ "���������"
	void onDisconnectButtonClicked()
	{
		QModelIndex selectedIndex = usersView->currentIndex();
		if (selectedIndex.isValid()) {
			QString user = selectedIndex.data().toString();
			// ��� ��� ���������� ������������ �� ��� �����
			// ...
		}
		else {
			QMessageBox::warning(this, "������", "������������ �� ������");
		}
	}

	// ���� ��� ��������� ������� �� ������ "��������"
	void onBanButtonClicked()
	{
		bool ok;
		QString reason = QInputDialog::getText(this, "��� ������������", "������� ������� ����:", QLineEdit::Normal, "", &ok);
		if (ok && !reason.isEmpty()) {
			QModelIndex selectedIndex = usersView->currentIndex();
			if (selectedIndex.isValid()) {
				QString user = selectedIndex.data().toString();
				// ��� ��� ���� ������������ �� ��� ����� � ��������� �������
				// ...
			}
			else {
				QMessageBox::warning(this, "������", "������������ �� ������");
			}
		}
		else {
			QMessageBox::warning(this, "������", "������� ���� �� �������");
		}
	}

private:
	QTextEdit* messagesView;
	QListView* usersView;
	QStandardItemModel* userListModel;
	QPushButton* disconnectButton;
	QPushButton* banButton;
};

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	ServerWindow w;
	w.show();
	return a.exec();
}