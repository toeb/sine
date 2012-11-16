#pragma once

#include <core.h>
#include <core.logging.h>
#include <userinterface.qt.controls.h>

#include <QStyledItemDelegate>

namespace nspace{
  class CustomItemDelegate : public QStyledItemDelegate , public virtual Log{
    Q_OBJECT;
  public:
    CustomItemDelegate(QObject * object);
    // QStyledItemDelegate implementation
    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index)const;
    virtual bool editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index);
    virtual void setEditorData( QWidget * editor, const QModelIndex & index ) const;
    virtual void setModelData( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;
  private:    
    Object* objectFromIndex(const QModelIndex & index)const;    
  protected slots:
    void saveAndCloseEditor();
  };

}