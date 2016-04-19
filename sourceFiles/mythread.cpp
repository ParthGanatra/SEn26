#include "mythread.h"
#include "backend.h"
#include "database.h"
#include <stdlib.h>
#include <stdio.h>

MyThread::MyThread(QThread *parent)
    : QThread(parent)
{
}


void MyThread::run()
{
//    Backend backend;
//    Database db;
//    db.setUser("user");
//    db.stocklist = backend.stocklist;
//    db.run();

//    backend.addDatabse(&db);
//    QList<QObject*> all_popups_list;
//    backend.addPopupList(&all_popups_list);

//    QList<QObject*> trig_popups_list;
//    backend.trigPopupList(&trig_popups_list);
//    backend.get_all_popup_conditions();

    int start = 1;
    while(1){
//        delay(1000);
        qDebug()<<"ASDF";
        backend->add_data(start);
        start++;
    }

}

void MyThread::set_data(Backend *backen){
    backend = backen;
    backend->get_all_popup_conditions();
}
