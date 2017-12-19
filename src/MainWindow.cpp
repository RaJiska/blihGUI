#include "include/MainWindow.hpp"
 
 /* TODO: API Calls in thread */

MainWindow::MainWindow(void)
{
	this->resize(800, 700);

	/* Fusion for Linux, fixes QGroupBox Border */
	QApplication::setStyle("Fusion");

	/* Login */
	this->gbox_connection.setTitle("Connection");
	this->lbl_conlogin.setText("Login: ");
	this->lbl_conpassword.setText("Password: ");
	this->btn_conconnection.setText("Connection");
	this->chk_conremember.setText("Remember");
	this->le_conpassword.setEchoMode(QLineEdit::Password);
	this->layout_connection.addWidget(&this->lbl_conlogin);
	this->layout_connection.addWidget(&this->le_conlogin);
	this->layout_connection.addWidget(&this->lbl_conpassword);
	this->layout_connection.addWidget(&this->le_conpassword);
	this->layout_connection.addWidget(&this->chk_conremember);
	this->layout_connection.addWidget(&this->btn_conconnection);
	this->btn_conconnection.setDisabled(true);
	this->le_conlogin.setDisabled(true);
	this->le_conpassword.setDisabled(true);
	this->chk_conremember.setDisabled(true);
	this->gbox_connection.setLayout(&this->layout_connection);
	
	/* Repositories list */
	this->gbox_repositories.setTitle("Repositories");
	this->btn_repoadd.setText("Add");
	this->btn_repodel.setText("Delete");
	this->btn_reposetacl.setText("Set ACLs");
	this->btn_repoinfo.setText("Infos");
	this->btn_repoadd.setDisabled(true);
	this->btn_repodel.setDisabled(true);
	this->btn_reposetacl.setDisabled(true);
	this->btn_repoinfo.setDisabled(true);
	this->layout_repolw.addWidget(&this->lw_repositories);
	this->layout_repobtns.addWidget(&this->btn_repoadd);
	this->layout_repobtns.addWidget(&this->btn_repodel);
	this->layout_repobtns.addWidget(&this->btn_reposetacl);
	this->layout_repobtns.addWidget(&this->btn_repoinfo);
	this->layout_repositories.addLayout(&this->layout_repolw);
	this->layout_repositories.addLayout(&this->layout_repobtns);
	this->gbox_repositories.setLayout(&this->layout_repositories);

	layout_main.addWidget(&this->gbox_connection);
	layout_main.addWidget(&this->gbox_repositories);

	this->widget_central.setLayout(&layout_main);
	this->setCentralWidget(&this->widget_central);

	/* Misc */
	this->cachedCredentialsAreValid();
	QObject::connect(&this->btn_conconnection, SIGNAL(clicked()), this, SLOT(connectToBlih()));
	QObject::connect(&this->btn_repoadd, SIGNAL(clicked()), this, SLOT(repositoryAdd()));
	QObject::connect(&this->btn_repodel, SIGNAL(clicked()), this, SLOT(repositoryDelete()));
	QObject::connect(&this->btn_reposetacl, SIGNAL(clicked()), this, SLOT(repositorySetAcl()));
	QObject::connect(&this->btn_repoinfo, SIGNAL(clicked()), this, SLOT(repositoryInfo()));
	QObject::connect(&this->lw_repositories, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(repositoryInfo()));
	QObject::connect(&this->lw_repositories, SIGNAL(itemSelectionChanged()), this, SLOT(repositoryItemSelected()));
}

MainWindow::~MainWindow(void)
{

}

/* --------------- PUBLIC --------------- */


/* --------------- PUBLIC SLOTS --------------- */

void MainWindow::loginChanged(QString login)
{
	bool is_same;

	is_same = (!this->cached_login.trimmed().isEmpty() && login == this->cached_login);
	this->le_conpassword.setDisabled(is_same);
	this->chk_conremember.setDisabled(is_same);
	this->chk_conremember.setChecked(is_same);
}

void MainWindow::connectToBlih(void)
{
	json response;
	Credentials crd = this->blih.getCredentials();

	this->lw_repositories.clear();
	this->le_conlogin.setDisabled(true);
	this->le_conpassword.setDisabled(true);
	this->chk_conremember.setDisabled(true);
	this->btn_conconnection.setDisabled(true);
	if (this->cached_login != this->le_conlogin.text())
	{
		crd.setLogin(this->le_conlogin.text().toUtf8().constData());
		crd.setPassword(this->le_conpassword.text().toUtf8().constData());
		this->blih.setCredentials(crd);
	}
	response = blih.repositoryList();
	if (!this->handleBlihError(response))
	{
		if (this->chk_conremember.isChecked())
			crd.writeToConfig();
		else
			crd.readFromConfig();
		this->actionRepositoryList(response);
		this->btn_repoadd.setDisabled(false);
	}
	else
	{
		this->btn_repoadd.setDisabled(true);
		crd.readFromConfig();
		this->blih.setCredentials(crd);
	}
	this->le_conlogin.setDisabled(false);
	this->le_conpassword.setDisabled(false);
	this->chk_conremember.setDisabled(false);
	this->btn_conconnection.setDisabled(false);
	this->loginChanged(this->le_conlogin.text());
}

void MainWindow::repositoryItemSelected(void)
{
	bool selected = this->lw_repositories.selectedItems().empty();

	this->btn_repodel.setDisabled(selected);
	this->btn_reposetacl.setDisabled(selected);
	this->btn_repoinfo.setDisabled(selected);
}

void MainWindow::repositoryAdd(void)
{
	json response;
	QString repo_name;
	RepoAddWindow w(&repo_name, this);

	this->btn_repoadd.setDisabled(true);
	w.exec();
	if (!repo_name.trimmed().isEmpty())
	{
		response = this->blih.repositoryCreate(repo_name.toUtf8().constData());
		if (!this->handleBlihError(response))
			this->lw_repositories.addItem(repo_name);
	}
	this->btn_repoadd.setDisabled(false);
}

void MainWindow::repositoryInfo(void)
{
	json infoResponse;
	json aclsResponse;
	json *aclsResponsePtr;
	QList <QListWidgetItem *> list = this->lw_repositories.selectedItems();
	std::string repo = list[0]->text().toUtf8().constData();

	this->btn_repoinfo.setDisabled(true);
	infoResponse = this->blih.repositoryInfo(repo);
	aclsResponse = this->blih.repositoryGetAcl(repo);
	aclsResponsePtr = this->handleBlihError(aclsResponse, true) ? NULL : &aclsResponse;
	if (!this->handleBlihError(infoResponse))
	{
		aclsResponse.erase("_STATUS_CODE"); // GetACL JSON format is different
		RepoInfoWindow w(infoResponse, aclsResponsePtr, QString::fromStdString(repo), this);
		w.exec();
	}
	this->btn_repoinfo.setDisabled(false);
}

void MainWindow::repositoryDelete(void)
{
	QList <QListWidgetItem *> list;
	int msgBoxRes;
	json response;

	list = this->lw_repositories.selectedItems();
	msgBoxRes = QMessageBox::warning(
		this,
		"Repository Deletion",
		"Are you sure you want to DELETE <b>" + list[0]->text() + "</b> ?",
		QMessageBox::No | QMessageBox::Yes
	);
	if (msgBoxRes == QMessageBox::No)
		return;
	response = this->blih.repositoryDelete(list[0]->text().toUtf8().constData());
	if (!this->handleBlihError(response))
		this->actionRepositoryDelete(list[0]->text());
}

void MainWindow::repositorySetAcl(void)
{
	QList <QListWidgetItem *> list;
	QString user;
	QString acl;
	json response;

	this->btn_reposetacl.setDisabled(true);
	RepoSetAclWindow w(user, acl, this);
	w.exec();
	if (!user.trimmed().isEmpty())
	{
		list = this->lw_repositories.selectedItems();
		response = this->blih.repositorySetAcl(
			list[0]->text().toUtf8().constData(),
			user.toUtf8().constData(),
			acl.toUtf8().constData()
		);
		this->handleBlihError(response);
	}
	this->btn_reposetacl.setDisabled(false);
}

/* --------------- PRIVATE --------------- */

/* TODO: Run within a thread */
void MainWindow::cachedCredentialsAreValid(void)
{
	Credentials crd;

	if (!crd.readFromConfig())
	{
		this->le_conlogin.setDisabled(false);
		this->le_conpassword.setDisabled(false);
		this->btn_conconnection.setDisabled(false);
		this->chk_conremember.setDisabled(false);
		this->chk_conremember.setChecked(false);
		return;
	}
	this->blih.setCredentials(crd);
	if (this->blih.checkCredentials())
	{
		this->cached_login = QString::fromStdString(this->blih.getCredentials().getLogin());
		this->le_conlogin.setText(this->cached_login);
		this->chk_conremember.setChecked(true);
		this->chk_conremember.setDisabled(true);
		QObject::connect(&this->le_conlogin, SIGNAL(textChanged(QString)), this, SLOT(loginChanged(QString)));
	}
	else
	{
		this->le_conpassword.setDisabled(false);
		this->chk_conremember.setDisabled(false);
	}
	this->le_conlogin.setDisabled(false);
	this->btn_conconnection.setDisabled(false);
}

bool MainWindow::handleBlihError(const json &response, bool quiet)
{
	QString str;

	if (quiet)
		return (response == nullptr || response["_STATUS_CODE"] != "200");
	if (response == nullptr)
		str = "Could not retrieve response from the remote server.";
	else if (response["_STATUS_CODE"] != "200")
	{
		str = "Error Code: " + QString::fromStdString(response["_STATUS_CODE"]) +
			"\nMessage: " + QString::fromStdString(response["error"]);
	}
	else
		return false;
	QMessageBox::critical(this, "BLIH Error", str);
	return true;
}

void MainWindow::actionRepositoryList(const json &response)
{
	this->lw_repositories.clear();
	this->repositoryItemSelected();
	for (auto &it : json::iterator_wrapper(response["repositories"]))
		this->lw_repositories.addItem(QString::fromStdString(it.key()));
}

void MainWindow::actionRepositoryDelete(const QString &name)
{
	QList <QListWidgetItem *> list;

	list = this->lw_repositories.findItems(name, Qt::MatchExactly);
	this->lw_repositories.takeItem(this->lw_repositories.row(list[0]));
}