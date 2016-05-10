/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "foo.h"
#include "QTextStream"
#include <QFile>
#include <QApplication>
#include <QClipboard>

QVector<qint32> nodeIdVector1;
QVector<QString> nodeIdefVector1;

Foo::Foo() {

}

void Foo::helloworld(QByteArray array) {
    QTextStream cout(stdout);

    QString fileText = QString::fromUtf8(array.data());
    for (int index=0; index<fileText.length()-10;index++){

        if (fileText[index] == QChar('<') && fileText[index+1] == QChar('n') && fileText[index+2] == QChar('o')){
            QString com="";
            int dif=index;
            while (QString::compare(com,"</node>")!=0){
                com="";
                for (int i=dif; i<dif+7; i++) com+=fileText[i];
                //поиск узлов
                if (fileText[dif]==QChar('i') && fileText[dif+1]==QChar('d') && fileText[dif+2]==QChar('=')) {
                    int i = dif + 4;
                    QString str="";
                    while (fileText[i]!=QChar('"')){
                        str += fileText[i];
                        i++;
                    }
                    //cout<<str;
                    nodeIdVector1.append(str.toInt());

                }
                // поиск идентификаторов узлов
                if (fileText[dif]==QChar('i') && fileText[dif+1]==QChar('d') && fileText[dif+2]==QChar('t') && fileText[dif+4]==QChar('=')) {
                    int i = dif + 6;
                    QString str="";
                    while (fileText[i]!=QChar('"')){
                        str += fileText[i];
                        i++;
                    }
                    //cout<<str;
                    nodeIdefVector1.append(str);

                }

                dif++;
            }
        }
    }
    writeToFile();
}

void Foo::writeToFile(){
    QTextStream cout(stdout);


        for (int index =0; index<nodeIdefVector1.length(); index++)
            cout<<nodeIdefVector1[index];
        //   QApplication::clipboard()->setText(nodeIdefVector[index]);


}
