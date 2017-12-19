#include "include/RepoInfoWindow.hpp"

RepoInfoWindow::RepoInfoWindow(
	const json &infoData,
	const json *aclsData,
	const QString &repo,
	QWidget *parent)
	: QDialog(parent)
{
	/* JSON Parse */
	this->lbl_uuid.setText(QString::fromStdString(infoData["message"]["uuid"]));
	this->lbl_name.setText(repo);
	this->lbl_description.setText(QString::fromStdString(infoData["message"]["description"]));
	this->lbl_public.setText(QString::fromStdString(infoData["message"]["public"]));
	this->lbl_url.setText(QString::fromStdString(infoData["message"]["url"]));
	this->setCreationTime(infoData);

	/* Infos Form */
	this->gbox_infos.setTitle("Informations");
	this->layout_infos.addRow("<b>UUID:</b> ", &this->lbl_uuid);
	this->layout_infos.addRow("<b>Name:</b> ", &this->lbl_name);
	this->layout_infos.addRow("<b>Description:</b> ", &this->lbl_description);
	this->layout_infos.addRow("<b>Public:</b> ", &this->lbl_public);
	this->layout_infos.addRow("<b>URL:</b> ", &this->lbl_url);
	this->layout_infos.addRow("<b>Creation Date:</b> ", &this->lbl_creation);
	this->gbox_infos.setLayout(&this->layout_infos);

	/* ACLs */
	QStringList columnsList;
	columnsList << "User" << "ACL";
	this->tree_acls.setHeaderLabels(columnsList);

	if (aclsData != NULL)
	{
		QStringList rowList;
		for (auto &it : json::iterator_wrapper(*aclsData))
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(&this->tree_acls);
			item->setText(0, QString::fromStdString(it.key()));
			item->setText(1, QString::fromStdString(it.value()));
			this->tree_acls.addTopLevelItem(item);
		}
	}
	this->tree_acls.setRootIsDecorated(false);
	this->tree_acls.setItemsExpandable(false);
	this->tree_acls.setColumnWidth(0, 250);
	this->gbox_acls.setTitle("ACLs");
	this->layout_acls.addWidget(&this->tree_acls);
	this->gbox_acls.setLayout(&this->layout_acls);

	/* Close */
	this->btn_close.setText("Close");
	this->layout_close.addWidget(&this->btn_close);

	this->layout_main.addWidget(&this->gbox_infos);
	this->layout_main.addWidget(&this->gbox_acls);
	this->layout_main.addLayout(&this->layout_close);
	this->setLayout(&this->layout_main);

	/* Misc */
	QObject::connect(&this->btn_close, SIGNAL(clicked()), this, SLOT(close()));
}

RepoInfoWindow::~RepoInfoWindow(void)
{
	QTreeWidgetItem *item;
	unsigned int it;

	for (it = 0; ((item = this->tree_acls.takeTopLevelItem(it)) != 0); it++)
		delete item;
}

/* --------------- PRIVATE --------------- */

void RepoInfoWindow::setCreationTime(const json &infoData)
{
	time_t t = std::stol(infoData["message"]["creation_time"].get<std::string>());
	char *ascTime = std::ctime(&t);
	QString strTime;

	ascTime[strlen(ascTime) - 1] = 0; // asctime appends line return
	strTime = QString::fromLatin1(ascTime);
	this->lbl_creation.setText(strTime);
}