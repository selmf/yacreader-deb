#ifndef HELP_ABOUT_DIALOG_H
#define HELP_ABOUT_DIALOG_H

#include <QDialog>

class QTabWidget;
class QTextBrowser;

class HelpAboutDialog : public QDialog
{
Q_OBJECT
public:
	HelpAboutDialog(QWidget * parent=0);
	HelpAboutDialog(const QString & pathAbout,const QString & pathHelp,QWidget * parent =0);
	~HelpAboutDialog();
public slots:
	void loadAboutInformation(const QString & path);
	void loadHelp(const QString & path);

private:
	QTabWidget *tabWidget;
	QTextBrowser *aboutText;
	QTextBrowser *helpText;
	QString fileToString(const QString & path);
};


#endif // HELP_ABOUT_DIALOG_H