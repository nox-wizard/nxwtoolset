/***************************************************************************
                          nxwtoolset.h  -  description
                             -------------------
    begin                : Wed Dec 25 15:37:44 CET 2002
    copyright            : (C) 2002 by Fabrizio Montesi
    email                : luxor@eos-software.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef NXWTOOLSET_H
#define NXWTOOLSET_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define APPNAME "NXW Toolset"
#define APPVERSION "0.3"
#define NEWFILENAME "Untitled"
#define NXWFILEOUT "nxwtoolset.out"
#define ERR_PERMISSIONS "An error occured opening the file,\ncheck your file permissions."

#include <qapplication.h>
#include <qmainwindow.h>
#include <qwidget.h>
#include <qsyntaxhighlighter.h>
#include <qtextedit.h>
#include <qtabwidget.h>
#include <qfile.h>
#include <qpopupmenu.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qfileinfo.h>
#include <qtoolbutton.h>
#include <qdockarea.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qstringlist.h>
#include <qstatusbar.h>
#include <qinputdialog.h>
#include <qregexp.h>
#include <qtextbrowser.h>
#include <qdir.h>
#include <qcolor.h>


extern QTextEdit *g_compEdit;
int compiler_main(int argc, char **argv);

/** NXWToolset is the base class of the project */
class NXWToolset : public QMainWindow
{
Q_OBJECT
public:
        NXWToolset(QApplication* parent=0, const char *name=0);
        ~NXWToolset();
        void replaceNext(QString sFind, QString sReplace);
        void replaceAll(QString sFind, QString sReplace);
        void findNext(QString sFind);
private:
        void initBars();
        void initGUI();
        void parseIncludeFile(QString sFilename, QString sFilter = NULL);
        QString m_sFind;
        QString m_sReplace;
        QApplication *m_application;
        QTabWidget *m_mainTab;
        QTabWidget *m_bottomTab;
        QTextEdit *m_helpEdit;
        QListView *m_funcList;
        QListView *m_constList;
        QMap<QString, bool> *m_saveMap;
        QMap<QString, QStringList> *m_funcMap;
        QMap<QString, QString> *m_constMap;
public slots:
        void quitToolset();
        void compCursorChanged(int para, int pos);
        void searchLists(const QString& sSearch);
        void showFuncHelp(QListViewItem *item);
        void showConstHelp(QListViewItem *item);
        void addSelectedFunc(QListViewItem *item);
        void addSelectedConst(QListViewItem *item);
        void openNewFile();
        void openFileDialog();
        void showAboutDialog();
        void showAboutQtDialog();
        void closeCurrFile();
        void closeAllFiles();
        void saveAsCurrFile();
        void saveCurrFile();
        void saveAllFiles();
        void changeCaption(QWidget* tab);
        void signModified();
        void smallBuild();
        void showSettingsDialog();
        void statusCursorPosition(int para, int pos);
        void showGoToLineDialog();
        void findNext();
        void showFindDialog();
        void showFindReplaceDialog();
        void loadData(QString sFilter = NULL);
};

/** NXWTextEdit is the widget loaded to show an opened file, it's inserted into the main tab widget */
class NXWTextEdit : public QTextEdit
{
Q_OBJECT
public:
        NXWTextEdit(QWidget* parent, const char* name);
public slots:
        void indentNewLine();
};

class NXWSyntaxHighlighter : public QSyntaxHighlighter
{
public:
        NXWSyntaxHighlighter(QTextEdit* textEdit);
        virtual int highlightParagraph(const QString& sText, int nLastState);
};

class NXWAboutDialog : public QDialog
{
public:
        NXWAboutDialog(QWidget* parent, const char* name);
};

class NXWFindReplaceDialog : public QDialog
{
Q_OBJECT
public:
        NXWFindReplaceDialog(NXWToolset* parent, const char* name);
private:
        NXWToolset *m_parent;
        QLineEdit *m_findEdit;
        QLineEdit *m_replaceEdit;
public slots:
        void callReplaceNext();
        void callReplaceAll();
        void callFindNext();
};

#endif
