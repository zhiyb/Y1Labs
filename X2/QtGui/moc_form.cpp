/****************************************************************************
** Form meta object code from reading C++ file 'form.h'
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

#include "form.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *Form::className() const
{
    return "Form";
}

QMetaObject *Form::metaObj = 0;

#ifdef QWS
static class Form_metaObj_Unloader {
public:
    ~Form_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "Form" );
    }
} Form_metaObj_unloader;
#endif

void Form::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("Form","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Form::tr(const char* s)
{
    return qApp->translate( "Form", s, 0 );
}

QString Form::tr(const char* s, const char * c)
{
    return qApp->translate( "Form", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Form::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (Form::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    typedef void (Form::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (Form::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (Form::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (Form::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (Form::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (Form::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (Form::*m1_t7)();
    typedef void (QObject::*om1_t7)();
    typedef void (Form::*m1_t8)();
    typedef void (QObject::*om1_t8)();
    typedef void (Form::*m1_t9)();
    typedef void (QObject::*om1_t9)();
    m1_t0 v1_0 = &Form::read;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &Form::make;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &Form::uart;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &Form::jtag;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &Form::console;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &Form::flash;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &Form::readFuse;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &Form::writeFuse;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &Form::readEEPROM;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &Form::writeEEPROM;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    QMetaData *slot_tbl = QMetaObject::new_metadata(10);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(10);
    slot_tbl[0].name = "read(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "make()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "uart()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "jtag()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Private;
    slot_tbl[4].name = "console()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Private;
    slot_tbl[5].name = "flash()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Private;
    slot_tbl[6].name = "readFuse()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Private;
    slot_tbl[7].name = "writeFuse()";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Private;
    slot_tbl[8].name = "readEEPROM()";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Private;
    slot_tbl[9].name = "writeEEPROM()";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"Form", "QWidget",
	slot_tbl, 10,
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
