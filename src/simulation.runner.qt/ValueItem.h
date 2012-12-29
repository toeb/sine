#pragma once

#include <sstream>

#include <QStandardItem>
#include <QTimer>
#include <QItemDelegate>

#include <simulation.access/IValue.h>
namespace nspace{
  class ValueItem : public QObject, public QStandardItem, public QObjectUserData
  {
    Q_OBJECT
  private:
    bool _refresh;

  public:
    static QTimer * refreshTimer;
    void setRefresh(bool flag){
      _refresh = flag;
    }
    ValueItem():QObject(0),_refresh(true){
      setEditable(true);
      if(refreshTimer){
        connect(refreshTimer,SIGNAL(timeout()),this, SLOT(refresh()));
      }
    }
    virtual QVariant data(int role = Qt::UserRole + 1 ) const{
      if(role==Qt::DisplayRole||role ==Qt::EditRole){
        std::stringstream ss;
        get(ss);
        return QString::fromStdString(ss.str());
      }

      return QStandardItem::data(role);
    }
    virtual void setData(const QVariant &value, int role = Qt::UserRole + 1 ){
      if(role == Qt::EditRole){
        auto qstr = value.toString();
        const QByteArray asc = qstr.toAscii();
        std::string str(asc.constData(), asc.length());

        std::stringstream ss(str);
        set(ss);
        emitDataChanged();
        QStandardItem::setData(value,role);
        return;
      }
      QStandardItem::setData(value,role);
    }
    public slots:
      void refresh(){
        if(!_refresh)return;
        emitDataChanged();
      }
  protected:
    virtual void set(std::istream & is)=0;
    virtual void get(std::ostream & os)const=0;
  };
}