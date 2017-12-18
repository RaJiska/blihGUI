#include "include/RepoInfoWindow.hpp"

RepoInfoWindow::RepoInfoWindow(
	const json &infoData,
	const json &aclsData,
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
	this->lbl_creation.setText(QString::fromStdString(infoData["message"]["creation_time"]));

	/* Infos Form */
	this->gbox_infos.setTitle("Informations");
	this->layout_infos.addRow("UUID: ", &this->lbl_uuid);
	this->layout_infos.addRow("Name: ", &this->lbl_name);
	this->layout_infos.addRow("Description: ", &this->lbl_description);
	this->layout_infos.addRow("Public: ", &this->lbl_public);
	this->layout_infos.addRow("URL: ", &this->lbl_url);
	this->layout_infos.addRow("Creation Date: ", &this->lbl_creation);
	this->gbox_infos.setLayout(&this->layout_infos);

	/* ACLs */
	QStringList columnsList;
	columnsList << "User" << "ACL";
	this->tree_acls.setHeaderLabels(columnsList);
	QStringList rowList;
	for (auto &it : json::iterator_wrapper(aclsData))
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(&this->tree_acls);
		item->setText(0, QString::fromStdString(it.key()));
		item->setText(1, QString::fromStdString(it.value()));
		this->tree_acls.addTopLevelItem(item);
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
	/* TODO: Free TreeWidget */
}