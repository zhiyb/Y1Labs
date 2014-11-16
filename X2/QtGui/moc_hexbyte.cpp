/****************************************************************************
** BinButton meta object code from reading C++ file 'hexbyte.h'
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

#include "hexbyte.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *BinButton::className() const
{
    return "BinButton";
}

QMetaObject *BinButton::metaObj = 0;

#ifdef QWS
static class BinButton_metaObj_Unloader {
public:
    ~BinButton_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "BinButton" );
    }
} BinButton_metaObj_unloader;
#endif

void BinButton::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QPushButton::className(), "QPushButton") != 0 )
	badSuperclassWarning("BinButton","QPushButton");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString BinButton::tr(const char* s)
{
    return qApp->translate( "BinButton", s, 0 );
}

QString BinButton::tr(const char* s, const char * c)
{
    return qApp->translate( "BinButton", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* BinButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QPushButton::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (BinButton::*m1_t0)(bool);
    typedef void (QObject::*om1_t0)(bool);
    m1_t0 v1_0 = &BinButton::toggle;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "toggle(bool)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    typedef void (BinButton::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    m2_t0 v2_0 = &BinButton::changed;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "changed()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"BinButton", "QPushButton",
	slot_tbl, 1,
	signal_tbl, 1,
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

// SIGNAL changed
void BinButton::changed()
{
    activate_signal( "changed()" );
}


const char *HexByte::className() const
{
    return "HexByte";
}

QMetaObject *HexByte::metaObj = 0;

#ifdef QWS
static class HexByte_metaObj_Unloader {
public:
    ~HexByte_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "HexByte" );
    }
} HexByte_metaObj_unloader;
#endif

void HexByte::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("HexByte","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString HexByte::tr(const char* s)
{
    return qApp->translate( "HexByte", s, 0 );
}

QString HexByte::tr(const char* s, const char * c)
{
    return qApp->translate( "HexByte", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* HexByte::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (HexByte::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &HexByte::update;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "update()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"HexByte", "QWidget",
	slot_tbl, 1,
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
