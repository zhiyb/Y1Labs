/****************************************************************************
** Program meta object code from reading C++ file 'prog.h'
**
** Created: Tue Oct 29 04:08:00 2013
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.10   edited 2005-01-24 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "prog.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *Program::className() const
{
    return "Program";
}

QMetaObject *Program::metaObj = 0;

#ifdef QWS
static class Program_metaObj_Unloader {
public:
    ~Program_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "Program" );
    }
} Program_metaObj_unloader;
#endif

void Program::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("Program","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Program::tr(const char* s)
{
    return qApp->translate( "Program", s, 0 );
}

QString Program::tr(const char* s, const char * c)
{
    return qApp->translate( "Program", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Program::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"Program", "QObject",
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
