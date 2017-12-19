#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTreeWidget>

#include <ctime>

#include "include/BlihGUI.hpp"

class RepoInfoWindow : public QDialog
{
	public:
	RepoInfoWindow(
		const json &infoData,
		const json *aclsData,
		const QString &repo,
		QWidget *parent);
	~RepoInfoWindow(void);

	private:
	void setCreationTime(const json &infoData);

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