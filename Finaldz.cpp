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
		// Создание виджетов
		messagesView = new QTextEdit(this);
		usersView = new QListView(this);
		userListModel = new QStandardItemModel(this);
		disconnectButton = new QPushButton("Отключить", this);
		banButton = new QPushButton("Забанить", this);

		// Установка макета
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(messagesView);
		layout->addWidget(usersView);
		layout->addWidget(disconnectButton);
		layout->addWidget(banButton);
		setLayout(layout);

		// Установка модели списка пользователей
		usersView->setModel(userListModel);

		// Подключение сигналов к слотам
		connect(disconnectButton, &QPushButton::clicked, this, &ServerWindow::onDisconnectButtonClicked);
		connect(banButton, &QPushButton::clicked, this, &ServerWindow::onBanButtonClicked);
	}

public slots:
	// Слот для добавления сообщения в виджет с сообщениями
	void addMessage(const QString& message)
	{
		messagesView->append(message);
	}

	// Слот для обновления списка пользователей
	void updateUserList(const QStringList& users)
	{
		userListModel->clear();
		for (const QString& user : users) {
			QListWidgetItem* item = new QListWidgetItem(user, userListModel);
			userListModel->appendRow(item);
		}
	}

private slots:
	// Слот для обработки нажатия на кнопку "Отключить"
	void onDisconnectButtonClicked()
	{
		QModelIndex selectedIndex = usersView->currentIndex();
		if (selectedIndex.isValid()) {
			QString user = selectedIndex.data().toString();
			// Код для отключения пользователя по его имени
			// ...
		}
		else {
			QMessageBox::warning(this, "Ошибка", "Пользователь не выбран");
		}
	}

	// Слот для обработки нажатия на кнопку "Забанить"
	void onBanButtonClicked()
	{
		bool ok;
		QString reason = QInputDialog::getText(this, "Бан пользователя", "Введите причину бана:", QLineEdit::Normal, "", &ok);
		if (ok && !reason.isEmpty()) {
			QModelIndex selectedIndex = usersView->currentIndex();
			if (selectedIndex.isValid()) {
				QString user = selectedIndex.data().toString();
				// Код для бана пользователя по его имени с указанием причины
				// ...
			}
			else {
				QMessageBox::warning(this, "Ошибка", "Пользователь не выбран");
			}
		}
		else {
			QMessageBox::warning(this, "Ошибка", "Причина бана не указана");
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