/****************************************************************************
** NXWToolset meta object code from reading C++ file 'nxwtoolset.h'
**
** Created: Sat Apr 26 11:51:02 2003
**      by: The Qt MOC ($Id: moc_nxwtoolset.cpp,v 1.1 2003/04/26 21:18:26 luxornox Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "nxwtoolset.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *NXWToolset::className() const
{
    return "NXWToolset";
}

QMetaObject *NXWToolset::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NXWToolset( "NXWToolset", &NXWToolset::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NXWToolset::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NXWToolset", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NXWToolset::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NXWToolset", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NXWToolset::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"quitToolset", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "para", &static_QUType_int, 0, QUParameter::In },
	{ "pos", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"compCursorChanged", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "sSearch", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"searchLists", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_3 = {"showFuncHelp", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_4 = {"showConstHelp", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_5 = {"addSelectedFunc", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_6 = {"addSelectedConst", 1, param_slot_6 };
    static const QUMethod slot_7 = {"openNewFile", 0, 0 };
    static const QUMethod slot_8 = {"openFileDialog", 0, 0 };
    static const QUMethod slot_9 = {"showAboutDialog", 0, 0 };
    static const QUMethod slot_10 = {"showAboutQtDialog", 0, 0 };
    static const QUMethod slot_11 = {"closeCurrFile", 0, 0 };
    static const QUMethod slot_12 = {"closeAllFiles", 0, 0 };
    static const QUMethod slot_13 = {"saveAsCurrFile", 0, 0 };
    static const QUMethod slot_14 = {"saveCurrFile", 0, 0 };
    static const QUMethod slot_15 = {"saveAllFiles", 0, 0 };
    static const QUParameter param_slot_16[] = {
	{ "tab", &static_QUType_ptr, "QWidget", QUParameter::In }
    };
    static const QUMethod slot_16 = {"changeCaption", 1, param_slot_16 };
    static const QUMethod slot_17 = {"signModified", 0, 0 };
    static const QUMethod slot_18 = {"smallBuild", 0, 0 };
    static const QUMethod slot_19 = {"showSettingsDialog", 0, 0 };
    static const QUParameter param_slot_20[] = {
	{ "para", &static_QUType_int, 0, QUParameter::In },
	{ "pos", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_20 = {"statusCursorPosition", 2, param_slot_20 };
    static const QUMethod slot_21 = {"showGoToLineDialog", 0, 0 };
    static const QUMethod slot_22 = {"findNext", 0, 0 };
    static const QUMethod slot_23 = {"showFindDialog", 0, 0 };
    static const QUMethod slot_24 = {"showFindReplaceDialog", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "quitToolset()", &slot_0, QMetaData::Public },
	{ "compCursorChanged(int,int)", &slot_1, QMetaData::Public },
	{ "searchLists(const QString&)", &slot_2, QMetaData::Public },
	{ "showFuncHelp(QListViewItem*)", &slot_3, QMetaData::Public },
	{ "showConstHelp(QListViewItem*)", &slot_4, QMetaData::Public },
	{ "addSelectedFunc(QListViewItem*)", &slot_5, QMetaData::Public },
	{ "addSelectedConst(QListViewItem*)", &slot_6, QMetaData::Public },
	{ "openNewFile()", &slot_7, QMetaData::Public },
	{ "openFileDialog()", &slot_8, QMetaData::Public },
	{ "showAboutDialog()", &slot_9, QMetaData::Public },
	{ "showAboutQtDialog()", &slot_10, QMetaData::Public },
	{ "closeCurrFile()", &slot_11, QMetaData::Public },
	{ "closeAllFiles()", &slot_12, QMetaData::Public },
	{ "saveAsCurrFile()", &slot_13, QMetaData::Public },
	{ "saveCurrFile()", &slot_14, QMetaData::Public },
	{ "saveAllFiles()", &slot_15, QMetaData::Public },
	{ "changeCaption(QWidget*)", &slot_16, QMetaData::Public },
	{ "signModified()", &slot_17, QMetaData::Public },
	{ "smallBuild()", &slot_18, QMetaData::Public },
	{ "showSettingsDialog()", &slot_19, QMetaData::Public },
	{ "statusCursorPosition(int,int)", &slot_20, QMetaData::Public },
	{ "showGoToLineDialog()", &slot_21, QMetaData::Public },
	{ "findNext()", &slot_22, QMetaData::Public },
	{ "showFindDialog()", &slot_23, QMetaData::Public },
	{ "showFindReplaceDialog()", &slot_24, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"NXWToolset", parentObject,
	slot_tbl, 25,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NXWToolset.setMetaObject( metaObj );
    return metaObj;
}

void* NXWToolset::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NXWToolset" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool NXWToolset::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: quitToolset(); break;
    case 1: compCursorChanged((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: searchLists((const QString&)static_QUType_QString.get(_o+1)); break;
    case 3: showFuncHelp((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 4: showConstHelp((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 5: addSelectedFunc((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 6: addSelectedConst((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 7: openNewFile(); break;
    case 8: openFileDialog(); break;
    case 9: showAboutDialog(); break;
    case 10: showAboutQtDialog(); break;
    case 11: closeCurrFile(); break;
    case 12: closeAllFiles(); break;
    case 13: saveAsCurrFile(); break;
    case 14: saveCurrFile(); break;
    case 15: saveAllFiles(); break;
    case 16: changeCaption((QWidget*)static_QUType_ptr.get(_o+1)); break;
    case 17: signModified(); break;
    case 18: smallBuild(); break;
    case 19: showSettingsDialog(); break;
    case 20: statusCursorPosition((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 21: showGoToLineDialog(); break;
    case 22: findNext(); break;
    case 23: showFindDialog(); break;
    case 24: showFindReplaceDialog(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NXWToolset::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NXWToolset::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool NXWToolset::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *NXWTextEdit::className() const
{
    return "NXWTextEdit";
}

QMetaObject *NXWTextEdit::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NXWTextEdit( "NXWTextEdit", &NXWTextEdit::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NXWTextEdit::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NXWTextEdit", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NXWTextEdit::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NXWTextEdit", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NXWTextEdit::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTextEdit::staticMetaObject();
    static const QUMethod slot_0 = {"indentNewLine", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "indentNewLine()", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"NXWTextEdit", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NXWTextEdit.setMetaObject( metaObj );
    return metaObj;
}

void* NXWTextEdit::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NXWTextEdit" ) )
	return this;
    return QTextEdit::qt_cast( clname );
}

bool NXWTextEdit::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: indentNewLine(); break;
    default:
	return QTextEdit::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NXWTextEdit::qt_emit( int _id, QUObject* _o )
{
    return QTextEdit::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NXWTextEdit::qt_property( int id, int f, QVariant* v)
{
    return QTextEdit::qt_property( id, f, v);
}

bool NXWTextEdit::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *NXWFindReplaceDialog::className() const
{
    return "NXWFindReplaceDialog";
}

QMetaObject *NXWFindReplaceDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NXWFindReplaceDialog( "NXWFindReplaceDialog", &NXWFindReplaceDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NXWFindReplaceDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NXWFindReplaceDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NXWFindReplaceDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NXWFindReplaceDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NXWFindReplaceDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"callReplaceNext", 0, 0 };
    static const QUMethod slot_1 = {"callReplaceAll", 0, 0 };
    static const QUMethod slot_2 = {"callFindNext", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "callReplaceNext()", &slot_0, QMetaData::Public },
	{ "callReplaceAll()", &slot_1, QMetaData::Public },
	{ "callFindNext()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"NXWFindReplaceDialog", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NXWFindReplaceDialog.setMetaObject( metaObj );
    return metaObj;
}

void* NXWFindReplaceDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NXWFindReplaceDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool NXWFindReplaceDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: callReplaceNext(); break;
    case 1: callReplaceAll(); break;
    case 2: callFindNext(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NXWFindReplaceDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NXWFindReplaceDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool NXWFindReplaceDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
