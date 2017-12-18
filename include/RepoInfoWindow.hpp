#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMdiArea>
#include <QTextEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <map>
#include <thread>
#include <QFormLayout>
#include <QTreeView>
#include <QTreeWidget>

#include "include/BlihGUI.hpp"

class RepoInfoWindow : public QDialog
{
	public:
	RepoInfoWindow(
		const json &infoData,
		const json &aclsData,
		const QString &repo,
		QWidget *parent);
	~RepoInfoWindow(void);

	private:
	QVBoxLayout layout_main;

	QGroupBox gbox_infos;
	QFormLayout layout_infos;
	QLabel lbl_uuid;
	QLabel lbl_name;
	QLabel lbl_description;
	QLabel lbl_public;
	QLabel lbl_url;
	QLabel lbl_creation;

	QGroupBox gbox_acls;
	QVBoxLayout layout_acls;
	QTreeWidget tree_acls;

	QHBoxLayout layout_close;
	QPushButton btn_close;
};